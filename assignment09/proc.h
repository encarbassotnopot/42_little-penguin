#ifndef PROC_H
#define PROC_H

ssize_t ft_read (struct file *filp, char __user *buff, size_t count, loff_t *offp);
ssize_t ft_write (struct file *filp, const char __user *buff, size_t count, loff_t *offp);
#endif
