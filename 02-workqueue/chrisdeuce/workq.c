#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>

//Register functions
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felix Ruiz");
MODULE_DESCRIPTION("mykmod");
MODULE_VERSION(".01");

static void fn_trabajo_handler(struct work_struct *ws);

static struct workqueue_struct *wq=0;
static DECLARE_DELAYED_WORK(mykmod_work,fn_trabajo_handler);
static unsigned long onesec;

static void fn_trabajo_handler(struct work_struct *ws)
{
  printk("Contador de jiffies %u \n",(unsigned)onesec);
}

static int kernel_init(void)
{
  onesec = msecs_to_jiffies(1000);
  printk("Cola de trabajo iniciada: %u jiffies\n",(unsigned)onesec);

  if(!wq)
     wq = create_singlethread_workqueue("mykmod");
  if(wq)
    queue_delayed_work(wq,&mykmod_work,onesec);

  return 0;
}

static void kernel_exit(void)
{
  if(wq)
  {
    //verificamos que el trabajo en cola se haya ejecutado
    flush_workqueue(wq);
    //Termina la cola de trabajo
    destroy_workqueue(wq);
   }
    printk(KERN_ALERT "Fin de la cola\n");
}


module_init(kernel_init);
module_exit(kernel_exit);
