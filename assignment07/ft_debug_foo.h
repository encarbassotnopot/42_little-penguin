#ifndef FT_DEBUG_FOO_H
#define FT_DEBUG_FOO_H
#define __NO_VERSION__

ssize_t ft_foo_read (struct file *filp, char __user *buff, size_t count, loff_t *offp);
ssize_t ft_foo_write (struct file *filp, const char __user *buff, size_t count, loff_t *offp);
#endif
