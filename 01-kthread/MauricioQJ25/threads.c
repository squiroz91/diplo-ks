#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kthread.h>
#include<linux/sched.h>

#define DRIVER_LIC    "BSD"
#define DRIVER_AUTHOR "Mauricio Quijada Jiménez"
#define DRIVER_DESC   "Hello World! of kernel threads"

/*
*
*Para saber la informacion descriptiva del hilo usamos el comando
*modinfo 'nombredelhilo'
*
*/
MODULE_LICENSE		(DRIVER_LIC);
MODULE_AUTHOR		(DRIVER_AUTHOR);	
MODULE_DESCRIPTION	(DRIVER_DESC);	

struct task_struct *khilo;
/*
 * 
 *  
 * 		Return id
 */

//Esta funcion ejecuta lo que hará el hilo
int hilo_kernel_mau(void *data)
{
	int id = *(int *)data;

	printk(KERN_INFO "Hilo de Hello World en ejecucion con id: %d...\n", id);
    while( !kthread_should_stop() )
	{
    	schedule();		
			
    }
	return id;
}

//Esta funcion crea el hilo
static int __init kernel_init(void)
{
	static int id_thread = 10;

	printk( KERN_INFO "\n--------------------------------------------\n" );
   	khilo = kthread_run( hilo_kernel_mau, (void *)&id_thread, "k_hilo_de_Mau" );

	if( IS_ERR(khilo) ) 
	{
		printk("Error en la creación del hilo... \n");
		return PTR_ERR(khilo);
	}
   	printk( KERN_INFO "Hilo de Kernel creado: %s con PID %d \n", khilo->comm, khilo->pid );

   	return 0;
}

//esta funcion se ejecuta cuando el hilo termina
static void __exit kernel_exit(void)
{
	int ret_hilo_kernel = kthread_stop( khilo );

	if( ret_hilo_kernel == -EINTR )
		printk( KERN_INFO "Error en la terminación del hilo \n" );
	else
		printk( KERN_INFO "Hilo de Kernel de Mau con id: %d detenido\n", ret_hilo_kernel );		
}

module_init(kernel_init);
module_exit(kernel_exit);
