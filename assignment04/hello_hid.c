#include <linux/module.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ecoma-ba");
MODULE_DESCRIPTION("Prints on install and removal");

static const struct usb_device_id hello_table[] = {
    { USB_INTERFACE_INFO (3, 1, 1) },
    { }
};

MODULE_DEVICE_TABLE(usb, hello_table);	

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
