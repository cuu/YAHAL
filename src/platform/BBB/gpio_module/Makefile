CPPFLAGS += -std=c++0x -Wall -I../../../interface
obj-m    += gpio_bbb.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f *~ *.o
	
