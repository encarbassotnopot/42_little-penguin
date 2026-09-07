#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include "ft_debug_foo.h"

static DEFINE_MUTEX(mut);
static char page[PAGE_SIZE];

ssize_t ft_foo_read (struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
	int ret;

	mutex_lock(&mut);
	ret = simple_read_from_buffer(buff, count, offp, page, strlen(page));
	mutex_unlock(&mut);
	return ret;
}

ssize_t ft_foo_write (struct file *filp, const char __user *buff, size_t count, loff_t *offp)
{
	int ret;

	if (count > PAGE_SIZE)
		return -ENOSPC;

	mutex_lock(&mut);
	ret = simple_write_to_buffer(page, PAGE_SIZE-1, offp, buff, count);
	mutex_unlock(&mut);
	if (ret < 0)
		return ret;

	return count;
}

const struct file_operations ft_foo = {
	.owner = THIS_MODULE,
	.read = ft_foo_read,
	.write = ft_foo_write,
};

