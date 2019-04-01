#ifndef _IRQ_DISPATCHER_H_
#define _IRQ_DISPATCHER_H_

// dummy handler for bad function calls,
// when using std::functional
namespace std {
    void __throw_bad_function_call();
}

extern "C" {
    void Default_EUSCI_Handler(void);

    void EUSCIA0_IRQHandler(void);
    void EUSCIA1_IRQHandler(void);
    void EUSCIA2_IRQHandler(void);
    void EUSCIA3_IRQHandler(void);
    void EUSCIB0_IRQHandler(void);
    void EUSCIB1_IRQHandler(void);
    void EUSCIB2_IRQHandler(void);
    void EUSCIB3_IRQHandler(void);
}

class irq_dispatcher {
public:

    // The linker would ignore this object file, so by
    // calling this dummy method we can make sure that
    // the code in irq_dispatcher.cpp is linked in!
    static void link_in();
};

#endif // _IRQ_DISPATCHER_H_

