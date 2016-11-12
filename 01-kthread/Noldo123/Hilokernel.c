#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samuel Gandarilla"); 

static struct task_struct *thread_st;
//Funcion de ejecucion
static int thread_fn(void *unused){
    while (1){
        printk(KERN_INFO "Ejecutando el hilo \n");
        ssleep(10);
    }
    printk(KERN_INFO "Parando el Hilo\n");
    do_exit(0);
    return 0; //Si es diferente de 0 fallo
}

// Iniciando del modulo
static int __init init_thread(void){
    printk(KERN_INFO "Creando Hilo\n");
    thread_st = kthread_run(thread_fn, NULL, "kthread-Hilokernel");
    if (thread_st)
        printk(KERN_INFO "Se ha creado el Hilo\n");
    else
        printk(KERN_ERR "Fallo la creacion del Hilo\n");
    return 0;
}
// Finaliznado modulo
static void __exit cleanup_thread(void){
   printk(KERN_INFO "Deteniendo el Hilo\n");
   if (thread_st){
       kthread_stop(thread_st);
       printk(KERN_INFO "Hilo Detenido");
   }
}

module_init(init_thread);
module_exit(cleanup_thread);
