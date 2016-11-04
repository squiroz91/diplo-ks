Compilación cruzada del Kernel
==================================

Construir tu modulo de Kernel para una Raspberry Pi por compilador cruzado, es un proceso de dos pasos. 

*El primero, es construir el Kernel modificado para la Raspberry Pi, en un equipo con alguna distribución Linux. Que es un proceso que lleva algo de tiempo, pero solo se hace una sola vez. 

*El segundo paso es después de construir el Kernel, el resultado binario se es copiado en la Raspberry Pi.

##¿Cómo conseguir un compilador cruzado? 
	
El Kernel de Linux consiste en los siguientes componentes:
	
	Imagen de Kernel
		*Plataforma de 32 bits: `<boot-partition>/zImage` o `<boot-partition>/uImage`, dependiendo de las compatibilidades y configuración de u-boot.
		*Plataforma de 64 bits: `<boot-partition>/Image`.
	Árbol binario de dispositivos, una descripción de bajo nivel de los dispositivos, especifica de tu dispositivo(`<boot-partition>/<board>.dtb`).
	Módulos del Kernel (`/lib/modules/<kernel-version>/*`).
	Firmware (`/lib/firmware/*`).
	Headers (`/usr/include/linux`).
 
