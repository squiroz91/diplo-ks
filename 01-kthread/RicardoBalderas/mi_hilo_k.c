#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>

struct task_struct *task;

int data;
int ret;

/*
 * Función principal del hilo de kernel, la misma solo imprime una linea y se
 * queda esperando a ser detenido. La funcion schedule() es la encargada de
 * poner a dormir al hilo para que no continue usando recursos cuando no está
 * haciendo nada.
 *
 * Mientras no se llame a la función kthread_stop(), kthread_should_stop()
 * devolverá un valor de 0, y en ese caso, el hilo será dormido por un tiempo.
 */

int thread_function(void *data)
{
	printk(KERN_INFO "Hello from my_kthread.\n");

	while (!kthread_should_stop())
	{
		schedule();
	}

	return 0;
}

/*
 * Función de inicio del hilo. La misma usa la función kthread_run() para
 * crear y despertar al hilo que usará la función thread_function().
 */

static int kernel_init(void)
{
	printk(KERN_INFO "Starting my_kthread...\n");

	task = kthread_run(thread_function, (void *) &data, "my_kthread");

	printk(KERN_INFO "Kernel Thread: %s\n", task->comm);

	return 0;
}

/*
 * Función de término del hilo, la misma manda a llamar a la función
 * kthread_stop() con el task_struct del hilo que se está ejecutando.
 */

static void kernel_exit(void)
{
	printk(KERN_INFO "Deteniendo my_thread.\n");

	kthread_stop(task);
}

/*
 * Las siguientes dos lineas registran los aliases usados para las funciones
 * init_module() y cleanup_module() respectivamente.
 */

module_init(kernel_init);
module_exit(kernel_exit);

MODULE_AUTHOR("Ricardo");
MODULE_LICENSE("GPL");
