#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");

// Global variable, workqueue struct
struct workqueue_struct *wq;

// Function to be performed by the work, it just print a message
static void wq_handler(struct work_struct *work)
{
    printk(KERN_INFO "Greetings from wq_handler\n");
}


static int wq_init(void)
{
    // Work struct variable, is needed to have it static or global
    // because the address is needed in the handler
    static struct work_struct work;

    printk(KERN_INFO "Init Workqueue\n");

    // Function to create the workqueue named 's_wq', Use the macro to initialize the work
    // with a given handler and queue the work in the workqueue created
    wq = create_workqueue("s_wq");
    INIT_WORK(&work, wq_handler);
    queue_work(wq, &work);

    return 0;
}

static void wq_exit(void)
{
    printk(KERN_INFO "Exit Workqueue\n");

    // Clear and destroy the workqueue
    flush_workqueue(wq);
    destroy_workqueue(wq);
}

module_init(wq_init);
module_exit(wq_exit);
