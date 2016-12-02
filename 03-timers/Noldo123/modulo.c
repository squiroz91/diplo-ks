#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kernel_stat.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samuel Gandarilla");

static struct timer_list my_timer;

//Funcion principal
static int main_timer(void)
{
  unsigned long timeout = jiffies + 20*HZ; 
  while (time_before(jiffies,timeout))
    {
      printk(KERN_INFO "Se esta ejecutando un deley\n");
      cond_resched();
    }
}

static void exit_timer(void)
{
  printk(KERN_ALERT "Se ha terminado el deley");
}

//Global variables

module_init(main_timer);
module_exit(exit_timer);
