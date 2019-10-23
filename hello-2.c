#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
//__initdata __init __exit are defined as macro
static int devNo __initdata = 99;
static int __init hello(void){
   printk(KERN_INFO "Hello developer number %d\n",devNo);
   return 0;
}
static void __exit hello_exit(void){
   printk(KERN_EMERG "Please do not leave me alone, developer number\n");
}
module_init(hello);
module_exit(hello_exit);
