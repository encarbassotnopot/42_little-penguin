#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ecoma-ba");
MODULE_DESCRIPTION("Registers /dev/fortytwo");

static const char LOGIN[] = "ecoma-ba\n";
static const ssize_t LOGIN_LEN = sizeof(LOGIN);
#define MY_BUFFER_SIZE 20
static char MY_BUFFER[MY_BUFFER_SIZE+1];

ssize_t ft_read (struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
	// és divertit veure què passa si no uses *offp com toca.
	// pr_info("/dev/fortytwo: Read %u bytes at offset %i\n", (unsigned int) count, (int) *offp);
	// count = 1;

	if (*offp >= LOGIN_LEN)
		return 0;

	if (*offp + count > LOGIN_LEN)
		count = LOGIN_LEN - *offp;

	if (copy_to_user(buff, LOGIN + *offp, count))
		return -EFAULT;

	*offp += count;
	return count;
}

ssize_t ft_write (struct file *filp, const char __user *buff, size_t count, loff_t *offp)
{
	size_t real_count = count;
	int ret = 0;
	memset(MY_BUFFER, 0, MY_BUFFER_SIZE+1);

	if (*offp >= MY_BUFFER_SIZE)
		return count;

	if (*offp + count > MY_BUFFER_SIZE)
		real_count = MY_BUFFER_SIZE - *offp; // no ens importa la resta del buffer, el descartem però reportem que l'hem llegit tot.

	if (copy_from_user(MY_BUFFER + *offp, buff + *offp, real_count))
		return -EFAULT;

	ret = count;
	
	//pr_info("/dev/fortytwo: Wrote %u bytes at offset %i. Will report %u bytes\n", (unsigned int) real_count, (int) *offp, (unsigned int) count);
	//pr_info("/dev/fortytwo: len %u, string: %s\n", (unsigned int) strlen(MY_BUFFER), MY_BUFFER);

	if (strcmp(LOGIN, MY_BUFFER) != 0)
		ret = -EINVAL;

	*offp += count;

	return ret;
}

static const struct file_operations ft_fops = {
	.owner = THIS_MODULE,
	.read = ft_read,
	.write = ft_write,
};

static struct miscdevice fortytwo = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fortytwo",
	.fops = &ft_fops,
};

static int __init hello(void)
{
        return misc_register(&fortytwo);
}

static void __exit goodbye(void)
{
        misc_deregister(&fortytwo);
}

module_init(hello);
module_exit(goodbye);
