#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

// Global variables, threads struct, and kernel module name
static struct task_struct *s_thread;
static char *thread_name = "masvthread";

// Thread functions, each 3 seconds prints "Waiting..."
// Does not do anything else
// It is a little anoying to print but it shows that is
// actually working
static int thread_sleep(void *data) {
    // This function receives returns true if rmmod is called
    while (!kthread_should_stop()) {
        printk(KERN_INFO "Waiting...\n");
        ssleep(3);
    }
    printk(KERN_INFO "Thread has been killed\n");
    do_exit(0);
    return 0;
}

// Main function
static int __init main_thread(void) {
    // Create a kernel thread and wake it up
    s_thread = kthread_run(thread_sleep, NULL, thread_name);
    if (s_thread)
        printk(KERN_INFO "MASV threads created!\n");
    else
        printk(KERN_ERR "kthread_run failed\n");
    return 0;
}

// Exit function
static void __exit del_thread(void) {
   printk(KERN_INFO "Deleting thread\n");
   if (s_thread)
       kthread_stop(s_thread);
}

// Register Functions
MODULE_LICENSE("GPL");
module_init(main_thread);
module_exit(del_thread);
