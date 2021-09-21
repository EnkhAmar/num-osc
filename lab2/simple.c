#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


static int __init simple_init(void) {
    printk(KERN_INFO "Simple module has been loaded\n");
    return 0;
}

static void __exit simple_exit(void) {
    printk(KERN_INFO "Simple module has been unloaded\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");