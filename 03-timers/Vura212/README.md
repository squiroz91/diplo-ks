**Modificación de Hilo con temporizadores

En los módulos del kernel una forma práctica de obtener las diferencias de tiempo entre dos eventos es usando 
la variable jiffies. La variable jiffies permite obtener el tiempo desde el último arranque del kernel, y se va incrementando en función de la constante HZ. Dicha constante puede variar según la arquitectura, en el
 caso de x86_64 esta a 1000. Para el caso del modulo del kernel mas larga que modifica el uptime del sistema
 podemos usar la variable jiffies para que una vez modificado el uptime se vaya incrementando de nuevo a un
 ritmo normal.

==============================================================================

Para nuestro programa usaremos distintos temporizadores a la hora de crear el hilo.

	usado en el primer programa de mi hilo
	sleep(5);

	Una demora corta son los mdelay medida para milisegundos
	mdelay(1000); //demora de 1 segundo

	Otro metodo es llamar a schedule_timeout(). Coloca la función a dormir hasa que se haya cumplido el tiempo indicado
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(2 * HZ);


EL programa completoo se muestra en n el archivo Thread_timer.c
Para cargar el hilo usaremos un Makefile
Una vez creado el Makefile ejecutaremos un make para cargar el modulo nuevo

`make`

enseguida para correr el hilo usaremos el comando:

`sudo insmod Thread_timer.ko`

Para ver la ejecución del comando usaremos el comando 

`dmesg`

A continuación se muestra como el hilo se ejecutara cada tiempo que determinamos en nuestro temporizador
hasta que se mate el hilo:

<IMG src=https://github.com/Vura212/diplo-ks/blob/master/03-timers/Vura212/Timer_1.png>
