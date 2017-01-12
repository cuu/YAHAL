
#include <stdint.h>
#include "msp.h"
#include "gpio_msp432.h"
#include "stdin_interface.h"
#include "stdout_interface.h"

enum UART_BITS   { _7_BITS, _8_BITS };
enum UART_PARITY { _NO_PARITY, _EVEN_PARITY, _ODD_PARITY };
enum UART_STOP   { _1_STOPBIT, _2_STOPBITS };

class uart_msp432 : public stdin_interface, public stdout_interface {
public:
	uart_msp432(EUSCI_A_Type *	mod  = EUSCI_A0, // default: backport UART
				uint32_t    	baud = 9600,
				UART_BITS   	bits = _8_BITS,
				UART_PARITY 	par  = _NO_PARITY,
				UART_STOP   	stop = _1_STOPBIT);
	~uart_msp432();

	// Basic read/write operations on a UART
	void putc(char c);
	int  puts(const char *s);
	char getc();
	bool available();

private:
	bool _config_complete;

	EUSCI_A_Type  * _EUSCI;
	gpio_msp432_pin	_rx;
	gpio_msp432_pin	_tx;
};

