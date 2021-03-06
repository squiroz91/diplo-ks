/*Creación de mi primer hilo al Kernel*/

//Llamadas de librerias para la creación de un hilo
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

//Puntero a la estructura del hilo que será detenido
static struct task_struct *thread_st;

/* Funcion ejecutada por el hilo del Kernel
	El hilo verificará que sea cierto la creación y saldrá ya que sí retorna un 0
	significa que algo habra salido mal. 
*/
static int thread_fn(void *unused){
    while (1){
        printk(KERN_INFO "Thread created and running ;) \n");
        ssleep(5);
    }
    printk(KERN_INFO "Something wrong was happened, Thread stopped \n");
    do_exit(0);
    return 0;
}

// Inicialización del modulo
static int __init init_thread(void){
    printk(KERN_INFO "Creating a new Thread\n");
    //Creando hilo del kernel con el nombre "Vura212"
    thread_st = kthread_run(thread_fn, NULL, "Vura212 Thread created");
    if (thread_st)
        printk(KERN_INFO "Success creating threads Vura212\n");
    else
        printk(KERN_ERR "Vura212 thread filed\n");
    return 0;
}
// Función de salida
/* Función que se encargará de eliminar el Hilo creado 
a través del comando en consola: sudo rmmod thread*/
static void __exit cleanup_thread(void){
   printk(KERN_INFO "Killing and earising thread\n");
   if (thread_st){
       kthread_stop(thread_st);
       printk(KERN_INFO "Thread stopped");
   }
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marco Serrano"); 
module_init(init_thread);
module_exit(cleanup_thread);
