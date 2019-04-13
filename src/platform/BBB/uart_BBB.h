#ifndef _UART_BBB_H_
#define _UART_BBB_H_

#include "uart_interface.h"
#include <termios.h>

class uart_BBB : public uart_interface {
  public:

    uart_BBB(const char *dev);
   ~uart_BBB();
 
    int16_t write(uint8_t *txbuf, uint8_t len);

    int16_t read (uint8_t *rxbuf, uint8_t len);
  
    unsigned switch_baud(unsigned);
    
    void flush();
    
    void setBytesToRead(unsigned bytes);
    
    void setReadTimeout(unsigned timeout);
            
  private:
    void setattributes();
  	
    int _fd;
    struct termios config;

};

#endif
