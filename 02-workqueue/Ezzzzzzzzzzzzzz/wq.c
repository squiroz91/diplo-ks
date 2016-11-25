#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Esaú Rojas"); 


static struct workqueue_struct *my_wq; //Workqueue (workqueue_struct) creado de manera explicita

typedef struct {

	struct work_struct my_work;
	int x;

} my_work_t;

my_work_t *work, *work2;

/*Handler*/
static void my_wq_function(struct work_struct *work){ // Función que va a ser llamada

	my_work_t *my_work = (my_work_t *)work;
	printk("my_work.x %d\n", my_work->x);
	kfree((void *)work); 
	return;	
}

int init_module(void){

	int ret;
	my_wq = create_workqueue("my_queue"); //Crea workqueue, que retorna a la referencia (workqueue_struct) 
	if(my_wq){
			
		/*Queue some work (item 1)*/
		work = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);	// GFP_KERNEL.-Aqui, el proceso puede dormir si la memoria no 											// esta disponible

		if(work){

			INIT_WORK((struct work_struct *)work, my_wq_function);	//Un camino para declarar de forma dinámica el trabajo (work)
			work->x = 1;
			ret = queue_work(my_wq, (struct work_struct *)work);	//Encolar trabajos a dicha cola
		}

		printk("Work 1 created\n");
		
		/*Queue some additional work (item 2)*/
		work2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
		
		if(work2){
		
			INIT_WORK((struct work_struct *)work2, my_wq_function);	//Un camino para declarar de forma dinámica el trabajo (work)
			work2->x = 2;
			ret = queue_work(my_wq, (struct work_struct *)work2);	//Encolar trabajos a dicha cola

		}
		
		printk("Work 2 created\n");		
	}
return 0;
}

void cleanup_module(void){		//Finalizar trabajos 
			
	flush_workqueue(my_wq); 	// Para sacar todas las tareas pendientes, y salir limpiamente de alguna rutina del kernel
	destroy_workqueue(my_wq);
	printk(KERNEL_ALERT "Finished Workqueue\n");
	return;
}

module_init(init_module);
module_exit(cleanup_module);
