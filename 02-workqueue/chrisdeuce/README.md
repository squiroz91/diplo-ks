#Inserción de una cola de trabajo en un kernel de linux

###Un patrón de programación en cualquier kernel es el conocido como _productor-consumidor_. La manera más fácil de implementar este patrón en el kernel es medianate una cola de trabajo (_workqueue_). El productor envia data a la cola y el consumidor consume esa información (jala la información). El consumidor consume esa información en el orden que llega. Este proceso es conocido como FIFO (_first-in,first-out_).

###La implementación de una cola de trabajo en el kernel de linux es llamada kfifo y está implementada in kernel/kfifo.c, declarada en _<linux/kfifo.h>_.

##**kfifo**
###El kfifo en linux funciona con dos funciones básicas: enqueue (encolar) y dequeue (quitar de la cola).

##Creación de una cola
### Para crear una cola usando kfifo, primero se debe de declarar y luego inicilaizarla. Como casi todos los objetos del kernel esto se puede hacer de manera estática o dinámica. La manera más común es de manera dinámica:

####_int kfifo_alloc(struct kfifo *fifo, unsigned int size, gfp_t gfp_mask);_

### La función crea e inicializa un kfifo con una cola de un _tamaño_ de bytes, el kernel utiliza **gfp mask** _gfp_mask_ para asignar la cola. EN caso de exito kfifo_alloc() regresa cero, de lo contario regresa un número negativo.



