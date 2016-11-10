Compilación cruzada del Kernel
==================================

El Kernel de Linux consiste en los siguientes componentes:

+	Imagen de Kernel
	*	Plataforma de 32 bits: `<boot-partition>/zImage` o `<boot-partition>/uImage`, dependiendo de las compatibilidades y configuración de u-boot.
	*	Plataforma de 64 bits: `<boot-partition>/Image`.
+	Árbol binario de dispositivos, una descripción de bajo nivel de los dispositivos, especifica de tu dispositivo (`<boot-partition>/<board>.dtb`).
+	Módulos del Kernel (`/lib/modules/<kernel-version>/*`).
+	Firmware (`/lib/firmware/*`).
+	Headers (`/usr/include/linux`).

Construir tu modulo de Kernel para una Raspberry Pi por compilador cruzado, es un proceso de dos pasos. 

*	El primero, es construir el Kernel modificado para la Raspberry Pi, en un equipo con alguna distribución Linux. Que es un proceso que lleva algo de tiempo, pero solo se hace una sola vez. 
*	El segundo paso es después de construir el Kernel, el resultado binario se es copiado en la Raspberry Pi.

		Get the source code for linux kernel and other tools to make image.

    		$ mkdir raspberrypi
    		$ cd raspberrypi
    		$ git clone https://github.com/raspberrypi/tools.git
    		$ git clone https://github.com/raspberrypi/linux.git


##¿Cómo conseguir un compilador cruzado? 

Cuando compilamos un Kernel de Linux en otra arquitectura de CPU:
	
+	Mucho mas rápido que compilar nativamente, cuando el sistema objetivo (target) es mucho mas lento que tu GNU/Linux.
+	Mucho mas fácil el desarrollar herramientas para tu GNU/LINUX y faciles de encontrar. 
+	Para hacer diferencia con el compilador nativo, los ejecutables de la compilación cruzada están prefijadas con el nombre del sistema objetivo (target), arquitectura y a veces librerías.	 
	+	Examples: mips-linux-gcc, the prefix is mips-linux-arm linux-gnueabi-gcc, the prefix is arm-linux-gnueabi-

##¿Cómo configurar el kernel para que soporte la plataforma de Hardware deseada?

La arquitectura del CPU y el prefijo de la compilación cruzada esta definido atravez de las variables `ARCH` y `CROSS_COMPILE` en el toplevel del Makefile.
 
+	`ARCH` es el nombre de la arquitectura. Es definida por el nombre de el subdirectorio en `arch/` dentro de la fuente del Kernel.
		+	Ejemplo: `arm` si tu quieres compilar un kernel para una arquitectura `arm`.
+	`CROSS_COMPILE` es el prefijo de las herramientas de compilación cruzada
		+	Ejemplo: `arm-linux-` si tu compilador es `arm-linux-gcc` 

##¿Qué pasos hace el proceso de compilación para generar el código objeto final?
   
Existen configuraciones por default disponibles, por tarjeta o por familia de CPU
+	Estan disponibles en `arch/<arch>/configs/`, y están solo los archivos mínimos `.config`
	+	*Este es el camino mas común para configurar el kernel para plataformas embebidas*
+	Se puede correr `make help` para encontrar si alguna configuración esta disponible para tu plataforma
+	Para crear tu propio archivo de configuración
	+	`make savecdfconfig` para crear una configuración mínima
	+	`mv defconfig arch/<arch>/configs/myown_defconfig`
+	Después de cargar la configuración por default, se puede ajustar la configuración a tus necesidades con:
	+	`make config` 
[NOTES on "make config"](https://github.com/raspberrypi/linux)
	+	`make xconfig`
	+	`make gconfig`
	+	`make menuconfig`	

Dependiendo de la arquitectura el hardware seleccionado puede estar descrito usando código en C directo con el kernel, o usar un lenguaje espacial de descriptivo en el árbol de dispositivos (Device tree).
+	ARM, PowerPC, OpenRISC, ARC, son ejemplos de arquitecturas usando Device Tree.
+	Correr `make`
+	Copiar la imagen final del Kernel 
	+	Puede ser `zImage`, `vmlinux`, `bzImage` en `arch/<arch>/boot`
	+	Copiar el "Device tree blob" tal vez pueda ser necesario `arch/<arch>/boot/dts`
+	`make modules_install` suele ser usado en el desarrollo de embebidos, instala algunos módulos y archivos de descripción 
	+	`make INSTALL_MOD_PATH=<dir>/ modules_install`	


En el caso de Raspberry Pi [Kernel building](https://www.raspberrypi.org/documentation/linux/kernel/building.md) 


##¿Cómo arrancar el nuevo kernel?

Compilando un kernel modificado casi siempre conlleva el riesgo de que el nuevo kernel no boote por alguna razón. Algunos conocimientos sobre ARM boot loader u-boot nos ayudan a bootear de una manera correcta la imagen del kernel y levantar nuestro dispositivo ARM de nuevo. 

Booteando con u-boot

+	Las versiones recientes de u-boot pueden bootear el binario `zImage`
+ 	Otras versiones mas antiguas necesitan un formato especial de kernel: `uImage`
	+	`uImage` es generada de `zImage` usando la herramienta `mkimage`.
	+	En algunos ARM, `make uImage` requiere una variable `LOADADDR` que indica en cual dirección de la memoria física sera ejecutado.
+	El típico proceso de booteo 
	+	Cargar `zImage` o `uImage` en la dirección X de la memoria
	+	Cargar `<board>.dbt` de la dirección Y de la memoria
	+	Inicia el kernel con `bootz X - Y(en el caso de zImage)` o `booym X - y (en el caso de uImage)`  


***
Ref:
[Rpi linux](https://github.com/raspberrypi/linux)
[How To compile a custom Linux kernel for your ARM device](https://github.com/umiddelb/armhf/wiki/How-To-compile-a-custom-Linux-kernel-for-your-ARM-dev ice)
[Linux kernel introducction](http://free-electrons.com/)
***

    






 

