#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kernel_stat.h>
#include <linux/timer.h>

//Register functions
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felix Ruiz");
MODULE_DESCRIPTION("Timer tarea 03");
MODULE_VERSION("0.1");

static struct timer_list my_timer;

// Main function
static int main_timer(void){
  unsigned long timeout = jiffies + 5*HZ; /*two seconds*/
  while (time_before(jiffies,timeout))
    {
      printk(KERN_INFO "El delay sigue funcionando\n");
      cond_resched();
    }
}

static void exit_timer(void)
{
  printk(KERN_ALERT "Salinedo del delay");
}

//Global variables

module_init(main_timer);
module_exit(exit_timer);
