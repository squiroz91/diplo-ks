#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/timer.h>

int mi_time_interval = 1000;

struct timer_list mi_timer;

void _Timhandler(unsigned long data)
{
    	
    	mod_timer( &mi_timer, jiffies + msecs_to_jiffies(mi_time_interval));
	printk(KERN_INFO "Ejecutando timer...\n");

}

static int __init tim_init(void)
{
    	setup_timer(&mi_timer, _Timhandler, 0);
    	mod_timer( &mi_timer, jiffies + msecs_to_jiffies(mi_time_interval));

    	return 0;
}

static void __exit tim_exit(void)
{
    del_timer(&mi_timer);
    printk(KERN_ALERT "...Timer terminado\n");
}

module_init(tim_init);
module_exit(tim_exit);
