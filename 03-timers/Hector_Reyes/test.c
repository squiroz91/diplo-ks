#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/timer.h>
 
int g_time_interval = 60000; /*Timeout value: expiration time*/
struct timer_list g_timer;   /*Store the timer*/
 
void _TimerHandler(unsigned long data)
{
    /*Mod_Timer nos permite modificar el timeout del timer*/
    /*este segmento nos permite reiniciar el timer cuando se llama en setup_timer()*/
    /*msecs_to_jiffies nos permite transformar nuestro tiempo deseado en ticks de reloj*/
    mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
 
    printk(KERN_INFO "Estoy corriendo...\n");
}
 
static int __init my_init(void)
{
    printk(KERN_INFO "Hola!!.\n");
 
    /*Iicializacion del timer.*/
    setup_timer(&g_timer, _TimerHandler, 0); /*setup_timer es una funcion de tmier.h que manda a llamar a __init_timer*/
    /*Como se le configuro _TimeHandler, la funcion se llamara cada g_time_interval*/
    mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
 
    return 0;
}
 
static void __exit my_exit(void)
{
    /*este modulo nos permite matar el timer module y mandar mensaje*/
    del_timer(&g_timer);
    printk(KERN_INFO "My module exited from kernel!!!\n");
}
 
module_init(my_init);
module_exit(my_exit);
