#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>

#include <linux/jiffies.h>
#include <linux/delay.h>
#include <linux/timer.h>

struct task_struct *task;

int data;
int ret;

/*
 * Función principal del hilo de kernel, la misma solo imprime una linea y se
 * queda esperando a ser detenido. Mientras espera para ser detenida, cada
 * segundo imprime un mensaje en la bitácora del sistema, haciendo uso de la
 * función schedule_timeout.
 *
 * Mientras no se llame a la función kthread_stop(), la función se ejecutará y
 * se ira a dormir por (aproximadamente) un segundo.
 */

int thread_function(void *data)
{
	printk(KERN_INFO "Hello from my_kthread.\n");

	while (!kthread_should_stop())
	{
		// while (time_before(jiffies, timeout)) cpu_relax();

		// mdelay(1000);

		// while (time_before(jiffies, timeout)) schedule();

		// Se está investigando qué hace exactamente schedule_timeout()
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(1 * HZ);

		printk(KERN_INFO "Hello, again!.\n");
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

MODULE_AUTHOR("Ricardo Balderas");
MODULE_LICENSE("GPL");
