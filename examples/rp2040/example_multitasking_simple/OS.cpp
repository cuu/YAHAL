// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
// This file implements a very simple multitasking
// kernel.

#include <OS.h>
#include <cstdint>
#include <RP2040.h>

// The structure of a task control block (TCB).
// It stores the stack pointer of the task.
// Additionally it has a pointer to the next
// TCB (single linked list).
struct TCB {
    uint32_t *  sp_base;    // base address of stack (for new and delete)
    uint32_t *  sp;         // current SP of this task
    TCB *       next;       // pointer to next TCB
};

// TCBs are organized as a single linked list.
// This list has a head and a tail. At startup,
// both pointers are null.
TCB * head    = nullptr;
TCB * tail    = nullptr;

// pointer to the running task
TCB * run_ptr = nullptr;

// This method gets called when the method of a
// task ends. The running task is linked out of
// the TCB list, and the stack and TCB memory is
// freed. After that, we let the processor sleep
// until a new interrupt occurs. After the next
// sysTick interrupt, this code will not get any
// more time slices, and will therefore not be
// executed!
void task_exit() {
    __disable_irq();
    // Find previous TCB (we have to search for
    // this TCB, because we have no double-linked list)
    TCB * prev = head;
    while (prev->next != run_ptr) {
        prev = prev->next;
    }
    // Link out the running TCB and free TCB
    prev->next = run_ptr->next;
    delete run_ptr->sp_base; // free stack memory
    delete run_ptr;          // free TCB memory
    __enable_irq();
    // Infinite wait for new interrupt. This loop
    // will not get any more time slices...
    while(true) __WFE();
}

// This method allocates a new stack area, and sets up
// a stack frame at the top of this area (stacks grow
// downward to lower addresses). The PC and LR registers
// will be loaded with the task method address and exit
// routine address respectively.
// The TCB entries dealing with stack entries will be set
// (stack base and current stack value pointing to the last
// 'pushed' value).
void setup_stack(void(*func)(void), int stack_size, TCB *tcb ) {
    uint32_t * sp = new uint32_t[stack_size];
    // Initialize the new stack frame
    sp[stack_size -  1] = 0x01000000;   // PSR with thumb bit
    sp[stack_size -  2] = (uint32_t)func;      // R15 (PC)
    sp[stack_size -  3] = (uint32_t)task_exit; // R14 (LR)
    sp[stack_size -  4] = 0x12121212;   // R12
    sp[stack_size -  5] = 0x03030303;   // R3
    sp[stack_size -  6] = 0x02020202;   // R2
    sp[stack_size -  7] = 0x01010101;   // R1
    sp[stack_size -  8] = 0x00000000;   // R0
    sp[stack_size -  9] = 0x11111111;   // R11
    sp[stack_size - 10] = 0x10101010;   // R10
    sp[stack_size - 11] = 0x09090909;   // R9
    sp[stack_size - 12] = 0x08080808;   // R8
    sp[stack_size - 13] = 0x07070707;   // R7
    sp[stack_size - 14] = 0x06060606;   // R6
    sp[stack_size - 15] = 0x05050505;   // R5
    sp[stack_size - 16] = 0x04040404;   // R4

    tcb->sp_base =  sp;
    tcb->sp      = &sp[stack_size - 16];
}

// This method allocates a new TCB, allocates a
// new stack area and sets the stack pointer values
// (see above). Finally it links in the TCB in the
// linked list so it is executed by the scheduler.
// During modifications of the linked list, the
// interrupts are disabled so the process is not
// disturbed by a sysTick or other interrupt.
void OS_add_task( void(*func)(void), int stack_size) {
    // create a new TCB
    TCB * tcb = new TCB;
    setup_stack( func, stack_size, tcb );

    // Link in the TCB into our list
    __disable_irq();
    if (head == nullptr) {
        // Insert the first TCB
        head = tcb;
        tail = tcb;
        tcb->next = tcb;
    } else {
        // append TCB to end of linked list
        tail->next = tcb;
        tcb->next  = head;
        tail = tcb;
    }
    __enable_irq();
}

// This method starts the scheduling process.
// The run_ptr is set to the first task, and
// the systick-Timer is started. Before the
// first systick interrupt occurs, the first
// task is started by popping all registers
// from the stack. The exit routine is loaded
// into LR, and the PC value is loaded into R4
// and (at the end) an indirect  branch to R4
// is performed so the first task is started!
void OS_start_scheduler(int Hz) {
    // Start with first task
    run_ptr = head;

    // Start the systick timer
    SysTick_Config(125000000 / Hz);

    // Set the stack pointer of the first task and run that task
//    register uint32_t * __attribute__((unused)) sp asm("sp");
//    sp = run_ptr->sp;
//   asm volatile("pop     {r4-r11}");  // restore R4-R11
//    asm volatile("pop     {r0-r3} ");  // restore R0-R3
//    asm volatile("pop     {r12}   ");  // restore R12
//    asm volatile("pop     {lr}    ");  // load LR (the task_exit routine)
//    asm volatile("pop     {r0}    ");  // load PC (entry point) in R0
//    asm volatile("pop     {r1}    ");  // load PSR in R1 (is discarded)
//    asm volatile("cpsie   i       ");  // run task with interrupts enabled
//    asm volatile("bx      r0      ");  // branch to entry point

    // Alternative implementation: Do not load values from stack,
    // but simply set stack pointer to original location (before
    // the register save operations), get function pointer and start
    // first task.

    // Set the stack pointer of the first task and run that task
    register uint32_t * __attribute__((unused)) sp asm("sp");
    sp = run_ptr->sp + 16;
    void (*task)(void) = (void(*)(void))sp[-2];
    task();
}


// The systick interrupt service routine is
// defined in the file startup_msp432p401r_gcc.c
// The following method overrides the handler
// definition in the startup file, and must
// have C-linkage.
extern "C" {

// The interrupt handler is 'naked', which means that
// the compiler will not generate any push/pop
// operations at the beginning and the end of the
// method. The user has to make sure that all
// registers are saved as needed.
void SysTick_Handler(void) __attribute__((naked));

// When entering the interrupt handler, the processor
// has already saved the PSR, PC, LR, R12, R3..R0 on
// the stack (caller saved registers). The handler
// saves the remaining registers (callee saved registers),
// and stores the final SP value in the corresponding
// TCB entry.
// After that the handler (which is our 'scheduler')
// looks for the next task to run by simply stepping
// to the next TCB in the linked list. The SP of the
// new task is loaded, and all registers are restored.
// The final 'bx lr' will behave as a 'return from
// interrupt', because upon entering the interrupt
// handler, there is a magic value in the LR to denote
// that caller saved registers should be restored by
// this instruction.
void SysTick_Handler(void) {
    asm volatile("cpsid   i       ");  // disable interrupts
    // PSR,PC,LR,R12,R3-R0 are already pushed on the stack
    asm volatile("push    {r4-r7}");  // store R4-R11
    asm volatile("mov     r4, r8 ");
    asm volatile("mov     r5, r9 ");
    asm volatile("mov     r6, r10");
    asm volatile("mov     r7, r11");
    asm volatile("push    {r4-r7}");  // store R4-R11

    // Store the stack pointer of the interrupted task.
    // asm("sp") tells the compiler to use CPU register SP
    // for the variable called 'sp'.
    register uint32_t * sp asm("sp");
    run_ptr->sp = sp;

    // Step to next task in list
    // (simple round robin scheduling)
    run_ptr = run_ptr->next;

    // Set the new stack pointer
    sp = run_ptr->sp;

    asm volatile("pop     {r4-r7}");  // restore R4-R11 from new stack
    asm volatile("mov     r8, r4 ");
    asm volatile("mov     r9, r5 ");
    asm volatile("mov     r10, r6");
    asm volatile("mov     r11, r7");
    asm volatile("pop     {r4-r7}");  // restore R4-R11 from new stack
    asm volatile("cpsie   i       ");  // enable interrupts
    asm volatile("bx      lr      ");  // return from interrupt
                                       // (restore R0-R3,R12,LR,PC,PSR)
}

} // extern "C"
