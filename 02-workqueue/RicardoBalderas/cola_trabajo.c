#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

static void fn_trabajo(struct work_struct *ws);

/*
 * DECLARE_DELAYED_WORK se usa para poner una tarea en la cola de trabajo
 * en tiempo de compilación. Esta macro llama a __DELAYED_WORK_INITIALIZER()
 * que a su vez llama a __WORK_INITIALIZER() y a __TIMER_INITIALIZER().
 */

static DECLARE_DELAYED_WORK(trabajo, fn_trabajo);

static int cont;

/*
 * Función de trabajo con la funcionalidad principal, la misma cumple su
 * cometido y se vuelve a colocar al final de la cola de trabajo.
 */

static void fn_trabajo(struct work_struct *ws)
{
	printk(KERN_INFO "Contador: %d.\n", ++cont);
	schedule_delayed_work(&trabajo, HZ);
}

/*
 * La siguiente función carga el módulo de kernel. En este caso, el módulo
 * registra un mensaje en la bitácora del sistema y se coloca al final de
 * la cola de trabajo.
 */

static int iniciar(void)
{
	printk(KERN_INFO "Cola de trabajo iniciada.\n");
	schedule_delayed_work(&trabajo, HZ);

	cont = 0;
	return 0;
}

/*
 * La siguiente función registra un mensaje final en la bitácora del sistema,
 * y posteriormente termina el trabajo que estaba relizando.
 *
 * Es importante mencionar que es necesario llamar a cancel_delayed_work() para
 * que descargue las tareas pendientes que no se completaron.
 */

static void terminar(void)
{
	printk(KERN_INFO "Terminando cola de trabajo.\n");
	cancel_delayed_work(&trabajo);
	flush_scheduled_work();
}

module_init(iniciar);
module_exit(terminar);

MODULE_AUTHOR("Ricardo Balderas");
MODULE_LICENSE("GPL");
