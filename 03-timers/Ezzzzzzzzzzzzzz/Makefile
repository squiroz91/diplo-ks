obj-m+=timer01.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean


## Dynamically Loading/Unloading a Kernel Module
##
##    We use insmod command to load the kernel module as below. We need to execute this command with root privileges
##
##        $ insmod timer01.ko
##
##    In order to list the modules, execute lsmod as below. This will show you the skm loaded.
##
##        $ lsmod
##
##    And for removing/unloading the module, execute rmmod command as below:
##
##      $ rmmod timer01
##
##    Note that while unloading, we use module name (timer01), not the file name (timer01.ko).
