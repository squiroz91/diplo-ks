Compilación cruzada del Kernel
==================================

Construir tu modulo de kernel para una Raspberry Pi por compilador cruzado, es un proceso de dos pasos. 

*El primero, es construir el kernel modificado para la Raspberry Pi, en un equipo con alguna distribución linux. Que es un proceso que lleva algo de tiempo, pero solo se hace una sola vez. 

*El segundo paso es después de construir el kernel, el resultado binario se es copiado en la Raspberry Pi.

##¿Cómo conseguir un compilador cruzado? 
	
El kernel de Linux consiste en los siguientes componentes:
	
	*Imagen de Kernel
		*Plataforma de 32 bits: `<boot-partition>/zImage` 		o `<boot-partition>/uImage`, dependiendo de las 		compatibilidades y configuracion de u-boot.

		*Plataforma de 64 bits: `<boot-partition>/Image`
	*Arbol binario de dispositivos, una descripcion de 		bajo nivel de los dispositivos, especifica de tu 			dispositivo (`<boot-partition>/<board>.dtb`)
	*Modulos del kernel (`/lib/modules/<kernel-version>/\*`)
	*Firmware (`/lib/firmware/\*`)
	*Headers (`/usr/include/linux`)
 
