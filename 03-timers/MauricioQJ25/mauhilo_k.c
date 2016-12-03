/*
* El programa hace uso de la funcion schedule_timeout
* Imprime una linea cualquiera cada segundo
*
*/

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
int counter=0;

MODULE_AUTHOR("Mauricio Quijada");
MODULE_LICENSE("GPL");




int thread_function(void *data)
{
	printk(KERN_INFO "Hola Mau!\n");

	while (!kthread_should_stop())
	{
		// while (time_before(jiffies, timeout)) cpu_relax();

		// mdelay(1000);

		// while (time_before(jiffies, timeout)) schedule();

		// Se está investigando qué hace exactamente schedule_timeout()
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(1 * HZ);

		printk(KERN_INFO "Hola # %d!.\n",counter++);
	}

	return 0;
}

/*
 *despertar al hilo con thread_function().
 * 
 */

static int kernel_init(void)
{
	printk(KERN_INFO "Starting mau_kthread...\n");

	task = kthread_run(thread_function, (void *) &data, "mau_kthread");

	printk(KERN_INFO "Kernel Thread Mau: %s\n", task->comm);

	return 0;
}

/*
 *  Término del hilo
 *
 */

static void kernel_exit(void)
{
	printk(KERN_INFO "Deteniendo mau_thread.\n");

	kthread_stop(task);
}

/*
 * los 'nombres' usados para las funciones
 * init_module() y cleanup_module() respectivamente.
 */

module_init(kernel_init);
module_exit(kernel_exit);



