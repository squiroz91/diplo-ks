ifneq ($(KERNELRELEASE),)
	obj-m := threads.o
else

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

################################################################
#
#obj-m += thread-1.o
#
#all:
#
#	CROSS COMPILER for Raspberry PI 3:
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/mau/linux M=$(PWD) modules
#
#clean:	
#
#	CROSS COMPILER for Raspberry PI 3:
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ~/mau/linux M=$(PWD) clean
#
##################################################################3
