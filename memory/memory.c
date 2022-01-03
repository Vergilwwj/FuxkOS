#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/ioctl.h>

static int memory_device_major = 0;
static const char module_name[] = "memory_test";
static struct class *memory_device_class;
static struct file *filp = NULL;

static char write_buf[1024] = {0};
static char read_buf[1024] = "Hey! What's up ?!";

#define min_test(x, y) ({ \
	typeof(x) min_1 = x; \
	typeof(y) min_2 = y; \
	(void)(&min_1 == &min_2); \
	min_1 < min_2 ? min_1 : min_2;})

static int memory_test_open(struct inode *inode, struct file *file)
{
	printk("Welcome to Devil May Cry !\n");
	printk("\n");

	return 0;
}

static ssize_t memory_test_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	// printk("write success\n");
	if (count <= 0) {
		printk("memory_test_write is NULL!\n");
		return -EFAULT;
	}

	if (copy_from_user(write_buf, buf, count)) {
		return -EFAULT;
	}

	printk("Vergil: %s\n", write_buf);

	return 0;
}

#if 1
static ssize_t memory_test_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int ret = 0;
	// printk("read success\n");
	ret = copy_to_user(read_buf, buf, count);
	if (ret < 0) {
		printk("copy_to_user failed with %#x\n", ret);
		return -EFAULT;
	}

	printk("Dante: %s\n", read_buf);

	return 0;
}
#endif

static struct file_operations memory_test_fops = {
	.owner = THIS_MODULE,
	.open = memory_test_open,
	.read = memory_test_read,
	.write = memory_test_write
};

static int __init memory_test_init(void)
{
	int ret = 0;

	ret = register_chrdev(memory_device_major, module_name, &memory_test_fops);
	if (ret < 0) {
		printk(KERN_WARNING "memory_test module register error\n");
		return ret;
	}

	memory_device_major = ret;
	printk(KERN_NOTICE "Simple-driver: registered character device with major number = %i and "
				"minor numbers 0...255\n", memory_device_major);
	
	memory_device_class = class_create(THIS_MODULE, "memory_test_drv");
	device_create(memory_device_class, NULL, MKDEV(memory_device_major, 0), NULL, "my_memory_test_drv");
}

static void __exit memory_test_exit(void)
{
	unregister_chrdev(memory_device_major, module_name);
	device_destroy(memory_device_class, MKDEV(memory_device_major, 0));
	class_destroy(memory_device_class);
	
    printk(KERN_EMERG "memory test module removed.\n");

	return;
}

module_init(memory_test_init);
module_exit(memory_test_exit);
MODULE_LICENSE("GPL");