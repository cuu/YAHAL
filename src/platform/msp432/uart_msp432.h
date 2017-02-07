
#include <stdint.h>
#include "stdin_interface.h"
#include "stdout_interface.h"
#include "msp.h"

extern "C" {
void EUSCIA0_IRQHandler(void);
void EUSCIA1_IRQHandler(void);
void EUSCIA2_IRQHandler(void);
void EUSCIA3_IRQHandler(void);
}

enum UART_BITS   { _7_BITS, _8_BITS };
enum UART_PARITY { _NO_PARITY, _EVEN_PARITY, _ODD_PARITY };
enum UART_STOP   { _1_STOPBIT, _2_STOPBITS };

class uart_msp432 : public stdin_interface, public stdout_interface {
public:
	uart_msp432(EUSCI_A_Type *	mod  = EUSCI_A0, // default: backport UART
				uint32_t    	baud = 115200,
				UART_BITS   	bits = _8_BITS,
				UART_PARITY 	par  = _NO_PARITY,
				UART_STOP   	stop = _1_STOPBIT);
	virtual ~uart_msp432();

	// Basic read/write operations on a UART
	void putc(char c);
	int  puts(const char *s);
	char getc();
	bool available();
	void setBaudrate(uint32_t);

	void attachRxIrq( void (*)(char) );

	friend void EUSCIA0_IRQHandler(void);
	friend void EUSCIA1_IRQHandler(void);
	friend void EUSCIA2_IRQHandler(void);
	friend void EUSCIA3_IRQHandler(void);

private:
    bool _init;
    void init();

    static void handleIrq(EUSCI_A_Type *);
    static void (*_intHandler[4])(char);

	EUSCI_A_Type  * _EUSCI;
    uint32_t        _baud;
    UART_BITS       _bits;
    UART_PARITY     _par;
    UART_STOP       _stop;
	uint8_t         _port;
	uint8_t         _rx_pin;
	uint8_t         _tx_pin;
};

