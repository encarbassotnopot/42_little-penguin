#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>

ssize_t print_jif(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
	char my_buff[20];

	snprintf(my_buff, sizeof(my_buff), "%ld\n", jiffies);

	if (*offp >= sizeof(my_buff) - 1)
                return 0;

        if (*offp + count > sizeof(my_buff) - 1)
                count = sizeof(my_buff) - 1 - *offp;

	if (copy_to_user(buff, my_buff, count))
		return -EFAULT;

	*offp += count;
        return count;
}

const struct file_operations ft_jif = {
	.owner = THIS_MODULE,
	.read = print_jif,
};
