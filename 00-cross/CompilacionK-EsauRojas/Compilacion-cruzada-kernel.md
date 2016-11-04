Compilación cruzada del Kernel
==================================

Construir tu modulo de Kernel para una Raspberry Pi por compilador cruzado, es un proceso de dos pasos. 

*	El primero, es construir el Kernel modificado para la Raspberry Pi, en un equipo con alguna distribución Linux. Que es un 	
	proceso que lleva algo de tiempo, pero solo se hace una sola vez. 

*	El segundo paso es después de construir el Kernel, el resultado binario se es copiado en la Raspberry Pi.

##¿Cómo conseguir un compilador cruzado? 
	
El Kernel de Linux consiste en los siguientes componentes:

+	Imagen de Kernel
	*	Plataforma de 32 bits: `<boot-partition>/zImage` o `<boot-partition>/uImage`, dependiendo de las compatibilidades y 			configuración de u-boot.
	*	Plataforma de 64 bits: `<boot-partition>/Image`.
+	Árbol binario de dispositivos, una descripción de bajo nivel de los dispositivos, especifica de tu dispositivo (`<boot-partition>/<board>.dtb`).
+	Módulos del Kernel (`/lib/modules/<kernel-version>/*`).
+	Firmware (`/lib/firmware/*`).
+	Headers (`/usr/include/linux`).

Primero que nada obtenemos las herramientas para hacer compilación cruzada del Kernel:

	$ cd /usr/src
	$ git clone git://github.com/raspberrypi/tools.git --depth=1
	$ git clone git://git.denx.de/u-boot.git --depth=1

El sitio [www.kernel.org](www.kernel.org) ofrece las fuentes de Linux, y puedes obtener las versiones mas actuales. Aunque usualmente los vendedores organizan el kernel de sus tarjetas particulares en branches de github, destinadas para esto.

Raspberry Pi 2/3[rpi4.8.y](https://github.com/raspberrypi/linux)

   
 

