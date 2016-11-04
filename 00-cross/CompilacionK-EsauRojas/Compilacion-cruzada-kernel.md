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

##¿Cómo conseguir un compilador cruzado? 

Cuando compilamos un Kernel de Linux en otra arquitectura de CPU:
	
+	Mucho mas rápido que compilar nativamente, cuando el sistema objetivo (target) es mucho mas lento que tu GNU/Linux.
+	Mucho mas fácil el desarrollar herramientas para tu GNU/LINUX y faciles de encontrar. 
+	Para hacer diferencia con el compilador nativo, los ejecutables de la compilación cruzada están prefijadas con el nombre del sistema objetivo (target), arquitectura y a veces librerías.	 
	+	Examples:mips-linux-gcc, the prefix is mips-linux-arm-linux-gnueabi-gcc, the prefix is arm-linux-gnueabi-

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

	- NOTES on "make config":

    - Having unnecessary drivers will make the kernel bigger, and can
      under some circumstances lead to problems: probing for a
      nonexistent controller card may confuse your other controllers

    - Compiling the kernel with "Processor type" set higher than 386
      will result in a kernel that does NOT work on a 386.  The
      kernel will detect this on bootup, and give up.

    - A kernel with math-emulation compiled in will still use the
      coprocessor if one is present: the math emulation will just
      never get used in that case.  The kernel will be slightly larger,
      but will work on different machines regardless of whether they
      have a math coprocessor or not.

    - The "kernel hacking" configuration details usually result in a
      bigger or slower kernel (or both), and can even make the kernel
      less stable by configuring some routines to actively try to
      break bad code to find kernel problems (kmalloc()).  Thus you
      should probably answer 'n' to the questions for "development",
      "experimental", or "debugging" features.

	+	`make xconfig`
	+	`make gconfig`
	+	`make menuconfig`	


 

