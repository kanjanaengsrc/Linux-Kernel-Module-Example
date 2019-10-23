#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/stat.h> //use for st_mode

/* Macro function for licensing
 * and copyright */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kanjana Eiamsaard");

static int value = 555;
static char *mystring = "Adapt char pointer";
static int myarr[10];
static int num = 0;

/* There are 3 parameters when using module_param.
 * 1. Parameter name
 * 2. Parameter type
 * 3. Permissions bits
 */
/* There are 2 kind of permission bits
 * 1. st_mode
 * - S_IRUSR = Readable for owner
 * - S_IWUSR = Writeable for owner
 * - S_IRGRP = Readable for group of owner
 * - S_IROTH = Readable for other
 * 2. digit (same as unix permission number) 
  See more at https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
 */

module_param(value,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
module_param(mystring,charp,0000);
/*There are 4 paramters when using module_param_array.
 * 1. Array name
 * 2. Array type
 * 3. Address of variable that will store the number
 * of elements of the array initialized by user at module loading time.
 * 4. permission bits
 */
module_param_array(myarr,int,&num,0000); //nobody and read write nor execute

static int __init begin(void)
{
   int i;
   printk(KERN_INFO "Welocome to the kernel parameters passing example");
   printk(KERN_INFO "Value is an integer: %d\n", value);
   printk(KERN_INFO "mystring is a string: %s\n", mystring);
   for(i=0;i<(sizeof myarr / sizeof(int));i++){
      printk(KERN_INFO "myarr[%d] = %d\n", i, myarr[i]);
   }
   printk(KERN_INFO "got %d arguments for myarr.\n", num);
   return 0;
}
static void __exit stop(void)
{
   printk(KERN_INFO "Goodbye\n");
}
module_init(begin);
module_exit(stop);
/* Run this program with
 * sudo insmod param.ko mystring="DaddyisDaddy" myarr=-1,-2,3,4,5,6
 * sudo insmod param.ko mystring="DaddyisDaddy" myarr=-1,-2,3,4,5,6 value=777
 */
