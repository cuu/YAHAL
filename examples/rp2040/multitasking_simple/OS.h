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
// This is the API of a very simple multitasking
// kernel. It only has 2 methods ...

#ifndef OS_H
#define OS_H

// Add a new task. The first parameter
// is the function to run, and the second
// parameter the stack size in uint32_t word.
// Default stack size is 256*4 = 1024 bytes.
void OS_add_task( void(*func)(void), int stack_size=256);

// Start the scheduler with time slices
// of size T = 1 / Hz. The default value
// is 1000Hz (T=1ms)
void OS_start_scheduler(int Hz = 1000);

#endif /* OS_H */

