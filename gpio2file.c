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
static char filecontent[BUFSIZE];
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

static ssize_t mydevice_read(struct file *fp, char __user *buf, size_t count, loff_t *offs)
{
   char __user *uptr;
   printk(KERN_INFO "Reading from /proc/%s\n",MYFILE);
   printk(KERN_INFO "%zd alphabets will be read\n",count);
   uptr = buf;
   if(count > BUFSIZE){
     printk(KERN_ALERT "Operation is not allowed, size is not appropiate\n");
     return -1;
   }else{
     raw_copy_to_user(uptr,filecontent,count);
     return count;
   } 
}
static ssize_t mydevice_write(struct file *fp, const char __user *buf, size_t count, loff_t *offs)
{
   printk(KERN_INFO "Write into /proc/%s\n",MYFILE);
   printk(KERN_INFO "%zd alphabets will be write\n",count);
   if(count > BUFSIZE){
     printk(KERN_ALERT "Operation is not allowed, size is not appropiate\n");
     return -1;
   }else{
     raw_copy_from_user(filecontent,buf,count);
     return count;
   } 
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
   int i=0;
   printk(KERN_INFO "The beginning of Char driver\n");
   fakefile = proc_create("mydevice",0666,NULL,&myfops); 
   if(fakefile == NULL){
      printk(KERN_ALERT "Error: Could not create /proc/%s\n",MYFILE);
      return -1;
   }else{
     //Initail file content with 26 alphabets
     for(i=0;i<26;i++){
	filecontent[i] = alpha[i];
     }
     filecontent[i] = '\0'; //end of string
     return 0;
   }
}
static void __exit stop(void)
{
   proc_remove(fakefile);
   printk(KERN_INFO "Goodbye fake file driver\n");
}
module_init(begin);
module_exit(stop);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kanjana Eiamsaard");
