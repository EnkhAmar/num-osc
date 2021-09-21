/*
 * "make" to compile
 * "sudo insmod simple.ko" to load kernel module
 * "sudo rmmod simple" to unload kernel module
 * "make clean" to clean the compiled products
 * "sudo dmesg" to show the kernel log
 * "sudo dmesg -c" to clear the kernel log
 * "lsmod | grep simple" to check the simple module is loaded
 **/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

#define DRIVER_LIC "GPL"
#define DRIVER_DESCRIPTION "Simple Module"
#define DRIVER_AUTHOR "Enkh-Amar.G"


// Birthday struct 
typedef struct _birthday {
    int day;
    int month;
    int year;
    struct list_head list;
} birthday;

// Declare and initialize the head of the linked list
static LIST_HEAD(birthday_list);

/* This function will be called when the module is loaded.
 * It initializes the birthday struct values,
 * allocated memory for a struct element and creates
 * and inserts 5 birthdats into the list.
 * Then prints each birthday to the kernel log.
 **/
static int __init birthday_init(void) {
    printk(KERN_INFO "Loading Birthday Module\n");

    // Allocates 5 birthdays from kernel
    {birthday *person;};
    int i = 0;
    for (i = 0; i < 5; i++) {
        // Allocate from kernel memory
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        // Assing value to the struct
        person->day = 23 + i;
        person->month = 8 + i;
        person->year = 2000 + i;
        // Initialize the list member in struct birthday.
        INIT_LIST_HEAD(&person->list);
        // Add this struct to the tail of the list.
        list_add_tail(&person->list, &birthday_list);
    }

    // Traverse through kernel linked list and print
    {birthday *ptr;};
    list_for_each_entry(ptr, &birthday_list, list) {
        printk(KERN_INFO "Birthday: %d/%d/%d\n",
                ptr->year,
                ptr->month,
                ptr->day);
    }

    return 0;
}

static void birthday_exit(void) {
    printk(KERN_INFO "Unloading Birthday Module\n");
    // Traverse through kernel linked list and free the memory
    {birthday *ptr, *next;};
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        printk(KERN_INFO "Deleting Birthday: %d/%d/%d\n",
                ptr->year,
                ptr->month,
                ptr->day);
        // Delete list
        list_del(&ptr->list);
        // Free list memory
        kfree(ptr);
    }
}

module_init(birthday_init);
module_exit(birthday_exit);

MODULE_LICENSE(DRIVER_LIC);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_AUTHOR(DRIVER_AUTHOR);