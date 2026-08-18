#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ecoma-ba");
MODULE_DESCRIPTION("Prints on install and removal");

static int __init hello(void)
{
        printk(KERN_INFO "Hello world!");
	return 0;
}

static void __exit goodbye(void)
{
        printk(KERN_INFO "Cleaning up module.");
}

module_init(hello);
module_exit(goodbye);
