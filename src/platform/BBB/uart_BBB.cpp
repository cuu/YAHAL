#include <unistd.h> 	// sleep, close
#include <fcntl.h>	// O_RDWR
#include <string.h>	// memset

#include "uart_BBB.h"
#include "yahal_assert.h"
#include "stdio.h"

#define PARITYON 0
#define PARITY 0
#define STOP 0
#define HWFLOW 0

#define BAUDRATE B9600

uart_BBB::uart_BBB(const char *dev){
  //memset(&config, 0, sizeof(config));
	
 _fd=open(dev, O_RDWR | O_NOCTTY);
  yahal_assert(_fd > 0);
	
  int ret=isatty(_fd);
  yahal_assert(ret > 0);
	
  ret=tcgetattr(_fd, &config);
  yahal_assert(ret == 0);
		 
  config.c_cflag = B9600 | HWFLOW | CS8 | STOP | PARITYON | PARITY | CLOCAL | CREAD;
  
  config.c_iflag = IGNBRK | IGNCR;
  config.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off SW-FlowControl
  
  config.c_oflag = 0;
  config.c_lflag = 0;       //ICANON;
  
 	//Anzahl zu lesender Bytes
  config.c_cc[VMIN]=4;
  
  //Timeout zw 2 Bytes in Zehntel-Sekunden
  config.c_cc[VTIME]=0;
  
  cfsetospeed (&config, BAUDRATE);
	cfsetispeed (&config, BAUDRATE);
  
  tcflush(_fd, TCIFLUSH);
  
  tcsetattr(_fd,TCSANOW, &config);	

}

uart_BBB::~uart_BBB(){
  int ret = close( _fd );
  yahal_assert(ret != -1); 
}
 
int16_t uart_BBB::write(uint8_t *txbuf, uint8_t len){
  return ::write(_fd, txbuf, len);
}

int16_t uart_BBB::read (uint8_t *rxbuf, uint8_t len){
  return ::read(_fd, rxbuf, len);
}
  
unsigned uart_BBB::switch_baud(unsigned baud){	
  cfsetospeed (&config, baud);
  cfsetispeed (&config, baud);
		
  return baud;
}

void uart_BBB::flush(){
	tcflush(_fd, TCIOFLUSH);
}

void uart_BBB::setattributes(){
	tcsetattr(_fd,TCSANOW, &config);
}

void uart_BBB::setBytesToRead(unsigned bytes){
	config.c_cc[VMIN]=bytes;
	setattributes();
}

void uart_BBB::setReadTimeout(unsigned timeout){
    config.c_cc[VTIME]=timeout;
    setattributes();
}
