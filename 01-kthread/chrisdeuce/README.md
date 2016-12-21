#Creación de un hilo en el kernel de linux

##Tarea 01 módulo de kernel

####Un hilo de kernel es una abstracción moderna en programación, con el objetivo de ejecutarse en el espacio de la memoria compartida. Adicionalmente pueden compartirse archivos y otros recursos.

#### Linux tiene una implementación única de hilos, pero para el kernel no existe un concepto de kernel, de manera tal que los hilos son tratados como un proceso estándard. El kernel de linux no provee alguna semántica especial o estructuras para representar hilos; de tal manera que un hilo es simplemente un proceso que comparte recursos con otros procesos.