#Tarea 0: Compilacion cruzada

* ¿Cómo conseguir un compilador cruzado?
	Un compilador cruzado es aquel compilador que te permite programar para un sistema ajeno. Normalmente es usado para el desarrollo de sistemas emebidos debido a que no siempre tienen un sistema operativo donde poder programar. Los compiladores cruzados se usan para el desarrollo de programas binarios, que contienen lenguaje de maquina y la libreria estandar de C. Uno de los croscompiladores mas usadoes es el GNU Compiler Collection ya que soporta varias plataformas y varios lenguajes de programacion.

Para el raspberry pi, se nesesita usar la siguiente configuracion:

ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

* ¿Cómo configurar el kernel para que soporte la plataforma de Hardware deseada?

	Dentro de Linux, el sistema permite cargar y descargar extensiones en forma de modulos. Lo que permite mantener un control de los modulos y de la memoria que se necesita para el hardware que tenemos.
Para compilar nuevos modulos del kernel, es necesario obtener los headers y el codigo fuente del modulo que queremos agregar, asi como sus dependientes.
Dentro de GCC, para indicar que sistema se quiere usar, se hace uso de Target Triplet, que describe la plataforma donde se correra el codigo. La estructura es:
	
	machine-vendor-operatingsystem
	
En Raspberry Pi3  se indica con:

KERNEL=kernel7
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig

Donde se indica que se quiere usar la architectura arm con el sistema linux-gnueabihf- de la configuracion bcm2709_defconfig 

* ¿Qué pasos hace el proceso de compilación para generar el código objeto final?

Dentro de linux, se puede descargar la version de kernel deseada y una vez descomprimido se corren los comandos:

	make

	make modules

	make modules_install

	make install


* ¿Cómo arrancar el nuevo kernel?
Dentro de linux, se tiene que configurar la forma de arrancar, esto se encuntra en /boot/grub/menu.1st

Y se tiene que configurar lo siguiente:
	 
	 title           Ubuntu GNU/Linux, kernel x.x.xx Default
     root            (hd0,0)
     kernel          /boot/vmlinuz root=/dev/hda1 ro
     initrd          /boot/initrd.img-2.6.36
     savedefault
     boot


