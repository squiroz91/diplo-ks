#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/timer.h>

//Register functions
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felix Ruiz");
MODULE_DESCRIPTION("Thread, Tarea 1");
MODULE_VERSION("01");

struct task_struct *task;

int data;
int ret;

int thread_function(void *data)
{
  printk(KERN_INFO "Mi hilo de kernel.\n");
  while(!kthread_should_stop())
    {
      schedule();
    }
  return 0;
}

static int kernel_init(void)
{
  printk(KERN_INFO "Iniciando el hilo..\n");
  task =kthread_run(thread_function,(void *)&data,"mi_hilo");
  printk(KERN_INFO "Hilo de kernel: %s\n",task->comm);
  return 0;
}

static void kernel_exit(void)
{
  printk(KERN_INFO "Deteniendo el hilo:\n");
  kthread_stop(task);
}
module_init(kernel_init);
module_exit(kernel_exit);

