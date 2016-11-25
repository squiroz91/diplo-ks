#Tarea 3: Cola de trabajo



    Nombre: Mauricio Quijada Jiménez

El programa realizado en c tiene las mismas funciones que el hilo de kernel de la tarea 2.

las cuales son static int kernel_init(void), static void kernel_exit(void) y static void my_wq_function().

Para este trabajo se tomaron en cuenta las referencias
##### Robert Love Linux kernel Develepment, Jonathan Corbet.

para ejecutar la compilación se ejecuta el comando 

###Make

y para la compilación cruzada

###make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/victor/diplomadoLinux/linux M=$(PWD) modules

Se insertan de la misma manera con insmod y rmmod con permisos de Root.

para observar la ejecución del programa se muestra la siguiente imagen.

imagen

tareacolas.png


