obj-m := thr_mdelay.o  threads.o
KERNELDIR ?= ../Kernel_build/linux-4.8.6/

PWD := $(shell pwd)

default:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules 
clean:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD) clean
