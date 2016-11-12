¿Qué son los hilos de kernel?

En muchos aspectos son similares a los hilos de espacio de usuario, pero una de las principales diferencias es que existen en el espacio de kernel y se ejecutan en un modo privilegiado y tienen acceso total a las estructuras de datos presentes en el kernel.
Son básicamente utilizados para implementar tareas en segundo plano en del kernel. La tarea podría ser desde atender eventos asíncronos o esperar a que un evento ocurra. Los drivers de dispositivos utilizan los servicios de hilos de kernel para atender tareas como las ya mencionadas. Un ejemplo es el hilo de kernel 'khubd' que monitorea los hubs de usb y ayuda en la configuración de dispostivos usb durante la acción de 'hot-plugging'.

Descripción del código utilizado.

El hilo de kernel es creado en la función 'init_thread()'. Esta función a su vez contiene a 'kthread_create' el cual es el responsable de crear el hilo utilizando los siguientes parámetros:
kthread_create(int (*function)(void *data), void *data, const char name[], ...)

Parameters:
function – The function that the thread has to execute
data – The ‘data’ to be passed to the function
name – The name by which the process will be recognized in the kernel

Retuns: Pointer to a structure of type task_struct

El hilo creado ejecuta la función 'thread_fn()'. Sin embargo, 'kthread_create' crea el hilo en estado de sleep, por lo que se utiliza a 'wake_up_process()' para correr el hilo. Se concluye entonces que para correr un hilo se requiere de un proceso de dos pasos, primero crear el hilo y luego levantarlo. Por lo que se cuenta con 'kthread_run' para poder resumir estos pasos utilizando los siguientes parámetros:
kthread_run(int (*function)(void *data), void *data, const char name[], ...)

Parameters:
function – The function that the thread has to execute
data – The ‘data’ to be passed to the function
name – The name by which the process will be recognized in the kernel

Returns: Pointer to a structure of type task_struct

Para poder detener un hilo de kernel se utiliza la llamada 'kthread_stop()' la cual emplea los siguientes parámetros:
int kthread_stop(struct task_struct *k);
Parameters:
k – pointer to the task structure of the thread to be stopped

Returns:  The result of the function executed by the thread, -EINTR, if wake_up_process() was never called.

Al correr el código e insertar el módulo con 'insmod', todo ocurre de manera correcta; sin embargo, al intentar remover el módulo utilizando 'rmmod' se puede observar que deja de responder el hilo, esto se debe a que 'kthread_stop' es una llamada de bloqueo que espera a que el hilo salga, pero nuestro hilo esta en un loop infinito while(1), por lo que 'rmmod' nunca podrá tener efecto. Se concluye que 'kthread_stop' es una señal solamente, no un comando, por lo quinvocarla no nos permite matar o detener el hilo, solamente coloca una bandera en el 'task_struct()' del hilo y espera a que el hilo salga. 
Además si lanzamos el comando 'kill -9 <thread_id>' podremos observar hasta el momento que el hilo de kernel ignora todas las señales debido a que el hilo de kernel tiene control total sobre cuándo puede ser asesinado. 
Entonces, lo que se necesita para poder indicarle al hilo de kernel cuando alguien lo quiere detener o asesinar es utilizando la llamada 'kthread_should_stop()', el hilo deberá invocar esta llamada periódicamente y si regresa 'True' deberá realizar el 'clean up' requerido y salir. 

Señalizando al hilo de Kernel
Para poder enviar la señal al hilo de kernel se utiliza la llamada 'allow_signal()'. El hilo de kernel debe invocar periódicamente 'signal_pending()' para revisar si hay alguna señal pendiente y poder actuar como lo requiera. 

Al integrar la señalización y la revisión de 'stop', se logró remover exitosamente el módulo utilizando 'rmmod' sin algún bloqueo de por medio. 

Referencias:
https://sysplay.in/blog/linux-kernel-internals/2015/04/kernel-threads/
