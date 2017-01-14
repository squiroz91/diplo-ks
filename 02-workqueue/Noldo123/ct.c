//Librerias de uso para los modulos de Kernel
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/slab.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samuel Gandarilla Perez"); 


//Funcion para crear la cola de trabajo
static struct workqueue_struct *my_wq; 

typedef struct {

	struct work_struct my_work;
	int	x;

} my_work_t;

my_work_t *work, *work2;

//Esta es la funcion que sera ejecutada
static void my_wq_function( struct work_struct *work){ 

	my_work_t *my_work = (my_work_t *)work;
	printk( "El trabajo es: %d\n", my_work->x );
	kfree( (void *)work );	
}

int i_module( void )
{

	int ret;
        //Con esto se crea la cola y hace referencia a workqueue_struct
	my_wq = create_workqueue("queue");  
	if(my_wq){
			
		/*Queue some work (item 1)*/
		work = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);	// GFP_KERNEL.-Aqui, el proceso puede dormir si la memoria no 											// esta disponible

		if(work){

			INIT_WORK( (struct work_struct *)work, my_wq_function); //
			work->x = 1;
			ret = queue_work( my_wq, (struct work_struct *)work );	//Con esta instruccion se coloca los trabajos en fila
		}

		printk("Se ha creado un trabajo\n");
		
		
		work2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
		
		if(work2){
		
			INIT_WORK((struct work_struct *)work2, my_wq_function);	
			work2->x = 2;
			ret = queue_work(my_wq, (struct work_struct *)work2);	

		}
		
		printk("Se ha creado el 2 trabajo\n");		
	}
return 0;
}

//Funcion para salir de los procesos
void clean_module( void )
{				
	flush_workqueue( my_wq ); 	
	destroy_workqueue( my_wq );
	printk(KERN_ALERT "Cerrando la cola de trabajo\n");
}

module_init(i_module);
module_exit(clean_module);
