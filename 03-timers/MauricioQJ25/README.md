###TAREA TIEMPO

La siguiente tarea muestra la ejecución de un hilo
el cual imprime una linea y espera un segundo para 
imprimir la siguiente.

se compila con el comando

make

Para esperar un tiempo antes de la ejecución de maneras diferentes.

se usan 2 

// mdelay(1000); Imprime la linea cada segundo pero detiene al procesador: esto es peligroso.
   si queremos que el procesador haga otras tareas.

// schedule_timeout(); Imprime la linea si se coloca la tarea como: task interruptible

//while (time_before(...)) schedule(); Si lo hago con esta linea no veo nada con dmesg.

se puede ver su ejecución en  la siguiente imagen con schedule_timeout(); en el código

timer.png
![alt tag](https://github.com/MauricioQJ25/diplo-ks/blob/timerkernelmau/03-timers/MauricioQJ25/tarea_tiempo.png)

