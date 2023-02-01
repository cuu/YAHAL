#include <stdint.h>

uint8_t rp2040_rom_version(void) {
    return 3;
}

void __attribute__((noreturn)) panic(char *s) {
    (void)s;
    while(1) ;
}
