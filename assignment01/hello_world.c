#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ecoma-ba");
MODULE_DESCRIPTION("Prints on install and removal");

static int __init hello(void)
{
        pr_info("Hello world!\n");
	return 0;
}

static void __exit goodbye(void)
{
        pr_info("Cleaning up module.\n");
}

module_init(hello);
module_exit(goodbye);
