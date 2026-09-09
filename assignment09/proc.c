#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/rbtree.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/ns_common.h>
#include <linux/mount.h>
#include <../fs/mount.h>
#include <linux/nsproxy.h>
#include "proc.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ecoma-ba");
MODULE_DESCRIPTION("Registers /proc/mymounts");

static struct proc_dir_entry *proc;

// https://pointer-overloading.blogspot.com/2013/09/linux-creating-entry-in-proc-file.html ffs

static int proc_show(struct seq_file *m, void *v)
{
	struct mount *mnt, *tmp;
	struct rb_root root = current->nsproxy->mnt_ns->mounts;

	rbtree_postorder_for_each_entry_safe(mnt, tmp, &root, mnt_node) {
		seq_printf(m, "%s\n", mnt->mnt.mnt_sb->s_id);
	}
	return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_show, NULL);
}

static const struct proc_ops pops = {
	.proc_open = proc_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

static int __init hello(void)
{
        proc = proc_create("mymounts", 0444, NULL, &pops);
	return 0;
}

static void __exit goodbye(void)
{
        remove_proc_entry("mymounts", NULL);
}

module_init(hello);
module_exit(goodbye);
