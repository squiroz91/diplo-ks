#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

#define DRIVER_LIC    "GPL"
#define DRIVER_AUTHOR "Victor Hugo Garcia Ortega"
#define DRIVER_DESC   "Cola de trabajo dinamica"

MODULE_LICENSE		(DRIVER_LIC);
MODULE_AUTHOR		(DRIVER_AUTHOR);	
MODULE_DESCRIPTION	(DRIVER_DESC);	

static struct workqueue_struct *my_wq;

//Estructura con datos propios del trabajo a ejecutar
typedef struct 
{
	struct work_struct my_work;
  	int    x;
} my_work_t;

my_work_t *work1, *work2;

/* 
 *	Funcion ejecutada por cada trabajo encolado 
 */
static void my_wq_function( struct work_struct *work )
{
	my_work_t *my_work = (my_work_t *)work;

	printk( "Variable: my_work.x = %d\n", my_work->x );
	//Se libera la memoria de cada trabajo ejecutado
	kfree( (void *)work );
}
/* 
 *	Funcion kernel_init, crea la cola de trabajo, 
 * 	dos trabajos a ejecutar y los agrega a la cola de trabajo 
 */

static int kernel_init( void )
{
	int ret;

	// Se crea la cola de trabajo
	my_wq = create_workqueue("my_queue");
	if( my_wq ) 
	{
		/* 
		 *	Primer elemento de la cola de trabajo 
		 * 	kmalloc_large(size_t size, gfp_t flags)
		 * 	size: Número de bytes a reservar
		 * 	flags: Tipo de memoria a reservar
		 * 	GFP_KERNEL Reserva mEmoria normal del KERNEL
		 */
		work1 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
		if (work1) 
		{
			INIT_WORK( (struct work_struct *)work1, my_wq_function );
			work1->x = 1;
			//Se agrega el elemento 1 a la cola de trabajo
			ret = queue_work( my_wq, (struct work_struct *)work1 );
		}
		printk("Trabajo 1 creado y encolado\n");


		/* 
		 *	Segundo elemento de la cola de trabajo 
		 *	bool queue_work(struct workqueue_struct *wq, struct work_struct *work)
		 * 	Retorna "false" si el trabajo ya fue encolado, en caso contrario retorna true 
		*/
		work2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
		if (work2) 
		{
			INIT_WORK( (struct work_struct *)work2, my_wq_function );
		  	work2->x = 2;
			//Se agrega el elemento 2 a la cola de trabajo
		  	ret = queue_work( my_wq, (struct work_struct *)work2 );
		}
		printk("Trabajo 2 creado y encolado\n");

	}

	return 0;
}

static void kernel_exit(void)
{
	//Aseguramos que cualquier trabajo encolado se haya ejecutado 
	flush_workqueue( my_wq );
	//Termina con seguridad una cola de trabajo
	destroy_workqueue( my_wq );

	printk(KERN_ALERT "Cola terminada\n");
}

module_init(kernel_init);
module_exit(kernel_exit);

