# Mi simple Workqueue

En esta tarea se creo una cola de trabajo (Workqueue) que no hace absolutamente
nada util, solamente imprime un texto.

La WQ fue probrada en una Intel galileo Gen 2 con el kernel de `linux 4.8.6`.

El codigo se encuentra en `wqueue.c`

Para poder compilar el modulo de kernel basta con ejecutar:

```bash
make ARCH=i386 CROSS_COMPILE=i586-unknown-linux-gnu-
```

Se compila exactamente igual que la tarea del hilo de kernel, solamente se
cambio el archivo que va a generar.

Se agrega una imagen mostrando la carga y descarga del modulo.


![module](img/module.png)

	Funcionamiento de la cola de trabajo.

