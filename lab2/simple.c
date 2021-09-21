#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init rickroll_init(void) {
    printk(KERN_INFO "Rickroll module has been loaded\n");
    return 0;
}

static void __exit rickroll_exit(void) {
    printk(KERN_INFO "Rickroll module has been unloaded\n");
}

module_init(rickroll_init);
module_exit(rickroll_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");