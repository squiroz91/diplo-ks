obj-m := wqueue.o
#KERNELDIR ?= /home/mvictor/Documents/Diplomados/EmbeddedLinux/Module5/Kernel_build/linux-4.8.6/
KERNELDIR ?= ../Kernel_build/linux-4.8.6/

PWD := $(shell pwd)

default:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD) clean
