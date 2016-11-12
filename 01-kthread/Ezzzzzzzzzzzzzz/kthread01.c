#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Esaú Rojas"); 
MODULE_VERSION("0.1"); 

static struct task_struct *thread_st;
// Función ejecutada por el hilo (kthread)
static int thread_fn(void *unused)
{
    //Podemos usar la señal SIGKILL
    allow_signal(SIGKILL);
    while (!kthread_should_stop())
    {
        printk(KERN_INFO "Corriendo Kthread...\n");
        ssleep(5);
        // Checa si hay señales pendientes
        if (signal_pending(current))
            break;
    }
    printk(KERN_INFO "...Deteniendo Kthread\n");
    do_exit(0);
    return 0;
}
// Inicialización del modulo
static int __init init_thread(void)
{
    printk(KERN_INFO "Creando Kthread\n");
    //Crea el hilo del kernel (kthread) con el nombre 'mi-kthread'
    thread_st = kthread_run(thread_fn, NULL, "mi-kthread");
    if (thread_st)
        printk(KERN_INFO "Kthread Creado Satisfactoriamente!!\n");
    else
        printk(KERN_ERR "ERROR: Creación del Kthread\n");
    return 0;
}
// Modulo de salida
static void __exit cleanup_thread(void)
{
   printk(KERN_INFO "Limpiando\n");
   if (thread_st)
   {
       kthread_stop(thread_st);
       printk(KERN_INFO "Kthread Detenido");
   }
}

module_init(init_thread);
module_exit(cleanup_thread);
