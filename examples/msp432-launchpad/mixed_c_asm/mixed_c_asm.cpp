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
// This program shows how to mix C/C++ and assembly code.

#include <cstdio>
#include "uart_msp432.h"
#include "posix_io.h"

// Standard version of a simple add function.
int add1(int a, int b) {
    return a + b;
}

// First assembly version of add function.
// Reading the ARM calling conventions we know
// that the two parameters a and b are passed in
// as registers R0 and R1. The return value has
// to be in R0, so we simply add R1 to R0.
// We return a because we know that a maps to
// register R0, which now contains the result.
// This version is dangerous because the compiler
// does not know which registers are changed ...
int add2(int a, int b) {
    (void)(a);    // eliminate warnings
    (void)(b);
    asm("add.w  r0, r0, r1");
    return a;
}

// Second assembly version of add function.
// The registers in the assembler statement are
// substituted with placeholders, and we let the
// compiler decide which registers to use for
// variable a and b. "=r" means the register
// will have a output (result) value, "r" means
// the register will have a input value. Using
// this syntax, the compiler is aware which registers
// are modified and used.
int add3(int a, int b) {
    //    ----code---       : -output- : -input-
    asm("add.w  %0, %0, %1" : "=r" (a) : "r" (b) );
    return a;
}

// Third assembly version of add function.
// Here we use a local variable and show how
// to access this variable in a inline assembly
// statement. C variables can simply be referenced
// just like the parameter variables. In this special
// case, the compiler will notice that variable 'result'
// can be mapped to R0, and optimize this variable away...
int add4(int a, int b) {
    int result;
    //    ----code---       :    -output-   :     -input-
    asm("add.w  %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) );
    return result;
}

int main(void)
{
    uart_msp432 uart; // default is backchannel UART!
    posix_io::inst.register_stdin ( uart );
    posix_io::inst.register_stdout( uart );

    int i = 78;
    int j = 102;
    int result;

    // Add two integers and show result
    result = add1(i, j);
    printf("%d\n", result);

    result = add2(i, j);
    printf("%d\n", result);

    result = add3(i, j);
    printf("%d\n", result);

    result = add4(i, j);
    printf("%d\n", result);
}
