#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include<linux/fs.h>
#include<linux/sched.h>
#include<linux/fs_struct.h>
#include<asm/uaccess.h> //for tranfer data between user and kernel space

#define alpha "abcdefghijklmnopqrstuvwxyz"
#define BUFSIZE 32
#define MYFILE "mydevice"
//static char msg[BUFSIZE];
static struct proc_dir_entry *fakefile;

static int mydevice_open(struct inode *inode, struct file *fp)
{
   try_module_get(THIS_MODULE);
   printk(KERN_INFO "/proc/%s is opened\n",MYFILE);
   return 0;
}

static int mydevice_close(struct inode *inode, struct file *fp)
{
   module_put(THIS_MODULE);
   printk(KERN_INFO "/proc/%s is closed\n",MYFILE);
   return 0;
}

static ssize_t mydevice_read(struct file *fp, char *buf, size_t count, loff_t *offs)
{
   printk("Read from /proc/%s\n",MYFILE);
   return 1;
}
static ssize_t mydevice_write(struct file *fp, const char *buf, size_t count, loff_t *offs)
{
   printk("Write into /proc/%s\n",MYFILE);
   return 1;
}

//Declare our own file operations.
struct file_operations myfops =
{
  owner: THIS_MODULE,
  open: mydevice_open,
  release: mydevice_close,
  read: mydevice_read,
  write: mydevice_write,
};

static int __init begin(void)
{
   printk(KERN_INFO "The beginning of Char driver\n");
   fakefile = proc_create("mydevice",0666,NULL,&myfops); 
   if(fakefile == NULL){
      printk(KERN_ALERT "Error: Could not create /proc/%s\n",MYFILE);
      return -1;
   }
   return 0;
}
static void __exit stop(void)
{
   proc_remove(fakefile);
   printk(KERN_INFO "Goodbye Char driver\n");
}
module_init(begin);
module_exit(stop);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kanjana Eiamsaard");
