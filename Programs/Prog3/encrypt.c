/* Necessary includes for device drivers */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/uaccess.h> /* copy_from/to_user */

MODULE_LICENSE("Dual BSD/GPL");

/* Declaration of encrypt.c functions */
int encrypt_open(struct inode *inode, struct file *filp);
int encrypt_release(struct inode *inode, struct file *filp);
ssize_t encrypt_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t encrypt_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
void encrypt_exit(void);
int encrypt_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations encrypt_fops = {
  read: encrypt_read,
  write: encrypt_write,
  open: encrypt_open,
  release: encrypt_release
};

/* Declaration of the init and exit functions */
module_init(encrypt_init);
module_exit(encrypt_exit);

/* Global variables of the driver */
/* Major number */
int encrypt_major = 62;
	char buffer[41];
    
int encrypt_init(void) {
  int result;

  /* Registering device */
  result = register_chrdev(encrypt_major, "encrypt", &encrypt_fops);
  if (result < 0) {
    printk(
      "<1>encrypt: cannot obtain major number %d\n", encrypt_major);
    return result;
  }

  printk("<1>Inserting encrypt module now\n"); 
  return 0;

}

void encrypt_exit(void) {
  /* Freeing the major number */
  unregister_chrdev(encrypt_major, "encrypt");

  printk("<1>Removing encrypt module\n");

}

int encrypt_open(struct inode *inode, struct file *filp) {
  printk("<1>encrypt_open: completed.\n");
  /* Success */
  return 0;
}

int encrypt_release(struct inode *inode, struct file *filp) {
  printk("<1>encrypt_release: completed.\n");
	
  /* Success */
  return 0;
}

ssize_t encrypt_read(struct file *filp, char *buf, 
                    size_t count, loff_t *f_pos) { 
 
  int datasize = strlen(filp->private_data);
  int available_to_read;
	
  available_to_read = datasize - *f_pos;
  printk("<1>encrypt_read: count = %ld, available_to_read = %d\n", count, available_to_read);
  if (available_to_read <= 0) 
	return 0;
	  
  if (count > available_to_read) {
    count = available_to_read + 1;
  }
  copy_to_user(buf,filp->private_data + *f_pos,count);

  *f_pos+=count; 
  return count; 
}

ssize_t encrypt_write(struct file *filp, const char *buf, 
                    size_t count, loff_t *f_pos) { 
 
  char data[41];
    int newChar;
    int overflow = 126;
    static int currentKey = 47;
    int shift = currentKey % 94;
    int spaceOffset = 32 + shift;
    int i;
    memset(buffer, 0, 41);
     memset(data, 0, 41);
  printk("<1>encrypt_write: count = %ld\n", count);
  			    
  if (count > 41) 
	count = 40;
	  
  copy_from_user(data,buf,count);

   if(strstr(data, "KEY"))
    {
      currentKey = (data[4] - '0') * 10 + (data[5] - '0');
      printk("<1>encrypt_write: KEY = %d\n", currentKey);
      return count;
    }

  *f_pos=0;
  for (i = 0; i < count; i++)
    {
        newChar = data[i] + shift;
        buffer[i] = newChar <= overflow && newChar != spaceOffset ? newChar : newChar != spaceOffset ? 32 + (newChar - overflow) : 32;
    }
    buffer[40] = 0;
    filp->private_data = buffer;
    printk("<1>encrypt_write: STRING = %s COUNT: %d\n", filp->private_data, strlen(filp->private_data));
  return count; 
}