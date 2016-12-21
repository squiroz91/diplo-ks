# Tarea 4: Tuning

## Optimizando el kernel de linux

El sistema operativo de Raspberrypi tiene un repositorio en [linux raspberry](https://github.com/raspberrypi/linux) donde podemos
descargar la version del kernel de linux con sus drivers para la raspberry. El repositorio incluye un archivo de configuracion
*bcm2709_devfconfig* el cual contiene las opciones para crear un kernel optimizado para la raspberry. El archivo .config es creado
al ejecutar el makefile:

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig

Un vez creado el archivo .config, se realizaron 2 optimizaciones adicionales de forma manual: 

1. General Setup
	*Kernel compresion mode LZ4.*
	Este algoritmo de compresion usado en el kernel tiene un indice de compresión de aproximadamente el 35%,
	en comparación con 25% del algoritmo gzip que viene activo por default, aunque gzip comprime mas, la ventaja de LZ4 es que 
	descomprime hasta 3.6 veces mas rápido [1], Benchmark realizado en ARM64, por lo que el tiempo de arranque del sistema se reduce
	considerablemente [2].

	Una desventaja de LZ4 es que requiere mas memoria para la compresion y descompresion, 13MB, pero en el caso de la Raspberrypi 3
	con 1Gb de memoria eso no es problema.

[1] http://catchchallenger.first-world.info/wiki/Quick_Benchmark:_Gzip_vs_Bzip2_vs_LZMA_vs_XZ_vs_LZ4_vs_LZO
[2] Michael Opdenacker, "Embedded Linux Optimizations", Free Electrons. 

2. Processor type and features
	*Preemption model. Preemptible kernel.* 
	Esta opción es usada en kernel monoliticos donde todos o la mayoria de los device drivers se ejecutan en el espacio de kernel- 
	El planificador esta autorizado a realizar forzosamente un cambio de contexto durante la ejecución de un driver o módulo 
	de kernel, si ocurre la ejecucion de otro módilo de kernel, sin tener que esperar a que termine éste su ejecución [3].
	
	Con esta opción se genera un Kernel de tiempo real suave [4] muy adecuado para sistemas embebidos de tiempo real.

[3] Steven Rostedt, "Intro to Real­Time Linux for Embedded Developers", Maintainer of Real time patch for linux kernel.
[4] Kanaka Juvva, "Real-Time Systems", Dependable Embedded Systems, Carnegie Mellon University, 1998.

La compilación cruzda es realizada con:

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs

En la compilacion del kernel se generan los siguientes archivos en el orden mostrado:
	Archivos .o de los módulos 
	Archivos .mod.o 
	Archivos .ko
	Archivos .bin y .fw



