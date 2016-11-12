**Creación de mi hilo de Kernel**
===================================

La forma de manejar los hilos de Linux es únicamente en comparación con el enfoque tradicional. 
En general, un hilo y un proceso se tratan de diferentes formas, 
pero en el caso de hilo de Linux es también sólo otro 
proceso y se manejan de la misma manera que cualquier otro proceso. 
En esta tarea se escribió un pequeño módulo para crear un hilo al Kernel y 
tratar de entender las diversas funciones que intervienen en el mismo.

El hilo se compone de dos archivo: 
> - thread.c 
> - Makefile

Para correr nuestro nuevo hilo se ejecutara la instrucción:

`make`

Creara los arcivos necesarios para nuestro hilo, en seguida escribiremos

`sudo insmod thread.ko`

Si todo salió bien podremos verificar si nuestro hilo esta corriendo:

`ps -ef | grep Vura212`

<IMG src=https://github.com/Vura212/diplo-ks/blob/master/01-kthread/Vura212/Thread_Vura212.png>

Para detener el hilo se usará el comando

`sudo rmmod thread.ko`

