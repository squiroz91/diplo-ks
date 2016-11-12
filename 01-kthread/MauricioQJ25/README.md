#Tarea #02

Creación de un hilo de kernel

Autor:Mauricio Quijada Jiménez

Fecha:11/noviembre/2016

###Archivos contenidos en la carpeta

Makefile

threads.c


El programa contenido en esta carpeta está carpeta se compone de las siguientes partes




static int_init kernel_init(void): se usa para crear el hilo.

static void_exit kernel_exit(void): se usa para detener el hilo mediante kthread_stop().

int hilo_kernel_mau(void *data): Es lo que hará el hilo mientras se ejecuta.

####COMPILAR
Para compilar use el comando
### make

Para compilar de forma cruzada podemos usar 

####make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi -C /home/mauricio/mau/linux M=$(PWM) modules

para ejecutar el hilo usamos el comando

###insmod threads.ko

para eliminar el hilo usamos el comando

###rmmod threads.ko

se necesitan permisos de root para ejecutar los comandos.

Se pueden observar los resultados obtenidos a continuacion.

(/TareaHiloMAU.png)
![alt tag](/TareaHiloMAU.png)
