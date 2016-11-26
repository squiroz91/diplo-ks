# Inserción de una tarea a una cola de trabajo

Esta tarea es un ejemplo pequeño de la forma en la que se inserta una tarea a
una cola de trabajo. La misma registra un mensaje cada segundo en la bitácora
del sistema.

Al estar hecha para la misma arquitectura donde se compila, es suficiente
crear un makefile que manda a llamar al Makefile que usa Linux para compilar
módulos de kernel.

Para ejecutar este módulo de kernel se debe ejecutar el siguiente comando
como superusuario:

```bash
insmod cola_trabajo.ko
```

En la siguiente pantalla se muestra una pantalla de la bitácora del sistema
después de cargar dicho módulo.

![module](img/cola_trabajo_01.png)

Para descargar el módulo, se usa (como superusuario también):

```bash
rmmod cola_trabajo
```

En la siguiente pantalla se muestra una pantalla de la bitácora del sistema
después de descargar el módulo.

![module](img/cola_trabajo_02.png)

Finalmente, se muestra una captura de la salida del comando lsmod

![module](img/cola_trabajo_03.png)
