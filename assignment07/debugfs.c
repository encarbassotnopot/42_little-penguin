#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ecoma-ba");
MODULE_DESCRIPTION("Registers folder fortytwo under debugfs");

extern const struct file_operations ft_fops;
extern const struct file_operations ft_jif;
extern const struct file_operations ft_foo;

struct dentry *ft_dir;

static int __init hello(void)
{
	ft_dir = debugfs_create_dir("fortytwo", NULL);
	if (!ft_dir) return 1;
	debugfs_create_file("id", 0666, ft_dir, NULL, &ft_fops);
	debugfs_create_file("jiffies", 0444, ft_dir, NULL, &ft_jif);
	debugfs_create_file("foo", 0644, ft_dir, NULL, &ft_foo);
	return 0;
}

static void __exit goodbye(void)
{
        debugfs_remove(ft_dir);
}

module_init(hello);
module_exit(goodbye);
