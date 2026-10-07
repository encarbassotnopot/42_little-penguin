#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>

// Dont have a license, LOL
MODULE_LICENSE("LICENSE");
MODULE_AUTHOR("Louis Solofrizzo <louis@ne02ptzero.me>");
MODULE_DESCRIPTION("Useless module");

static ssize_t myfd_read(struct file *fp, char __user *user,
			 size_t size, loff_t *offs);

static ssize_t myfd_write(struct file *fp, const char __user *user,
			  size_t size, loff_t *offs);

static struct file_operations myfd_fops = {
	.owner = THIS_MODULE,
	.read  = &myfd_read,
	.write = &myfd_write,
};

static struct miscdevice myfd_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "reverse",
	.fops  = &myfd_fops,
};

static char str[PAGE_SIZE];
static DEFINE_MUTEX(str_lock);
static size_t str_len;

static int __init myfd_init(void)
{
	return misc_register(&myfd_device);
}

static void __exit myfd_cleanup(void)
{
	misc_deregister(&myfd_device);
}

ssize_t myfd_read(struct file *fp,
		  char __user *user,
		  size_t size,
		  loff_t *offs)
{
	size_t t, i, ret;
	char *tmp;

	if (!str_len)
		return 0;
	mutex_lock(&str_lock);
	/*
	 * Malloc like a boss
	 */
	tmp = kmalloc(str_len, GFP_KERNEL);
	if (!tmp) {
		mutex_unlock(&str_lock);
		return -ENOMEM;
	}
	for (i = 0; i < str_len; i++)
		tmp[i] = str[str_len - 1 - i];
	tmp[i] = '\0';
	ret = simple_read_from_buffer(user, size, offs, tmp, str_len);

	kfree(tmp);
	mutex_unlock(&str_lock);
	return ret;
}

ssize_t myfd_write(struct file *fp,
		   const char __user *user,
		   size_t size,
		   loff_t *offs)
{
	ssize_t ret;

	mutex_lock(&str_lock);
	ret = simple_write_to_buffer(str, PAGE_SIZE, offs, user, size);
	if (ret >= 0) {
		str[ret] = '\0';
		str_len = ret;
	}
	mutex_unlock(&str_lock);
	return ret;
}

module_init(myfd_init);
module_exit(myfd_cleanup);
