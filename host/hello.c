#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Engenheiro Francisco Lima");
MODULE_DESCRIPTION("My first of many LKMs");
MODULE_VERSION("0:0.1");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello, cruel world\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
