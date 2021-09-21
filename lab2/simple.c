#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define DRIVER_LIC "GPL"
#define DRIVER_DESCRIPTION "Simple Module"
#define DRIVER_AUTHOR "Enkh-Amar.G"

/*
 * "make" to compile
 * "sudo insmod simple.ko" to load kernel module
 * "sudo rmmod simple" to unload kernel module
 * "make clean" to clean the compiled products
 * "sudo dmesg" to show the kernel log
 * "sudo dmesg -c" to clear the kernel log
 **/

static int __init simple_init(void) {
    printk(KERN_INFO "Simple module has been loaded\n");
    return 0;
}

static void __exit simple_exit(void) {
    printk(KERN_INFO "Simple module has been unloaded\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE(DRIVER_LIC);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_AUTHOR(DRIVER_AUTHOR);