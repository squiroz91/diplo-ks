#Inserción de una cola de trabajo en un kernel de linux

###Un patrón de programación en cualquier kernel es el conocido como _productor-consumidor_. La manera más fácil de implementar este patrón en el kernel es medianate una cola de trabajo (_workqueue_). El productor envia data a la cola y el consumidor consume esa información (jala la información). El consumidor consume esa información en el orden que llega. Este proceso es conocido como FIFO (_first-in,first-out_).

###La implementación de una cola de trabajo en el kernel de linux es llamada kfifo y está implementada in kernel/kfifo.c, declarada en **<linux/kfifo.h>**.

##**kfifo**
El kfifo en linux funciona con dos funciones básicas: enqueue (encolar) y dequeue (quitar de la cola).



