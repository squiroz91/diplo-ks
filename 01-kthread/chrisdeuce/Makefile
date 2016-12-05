obj-m +=thread.o
all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -C /home/felix/Documentos/develop/kbuild/linux M=$(PWD) modules
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -C /home/felix/Documentos/develop/kbuild/linux M=$(PWD) clean
