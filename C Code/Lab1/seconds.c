#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <stdbool.h>

/*
Kernal module that prints the number of seconds that
have elapsed since the module was loaded when 
cat /proc/seconds command is used
akesonm@mcmaster.ca
*/


/*
defines a constant for the buffer size of the string to be printed
when the command cat /proc/jiffies is called
*/
#define BUFFER_SIZE 128

/*
defines the name of the proc
*/
#define PROC_NAME "seconds"



/////////////////////////
// Function prototypes
/////////////////////////

ssize_t proc_read(struct  file *file, char *buf, size_t count, loff_t *pos);
int proc_init(void);
void proc_exit(void);

// a global struct varible of type file_operation, named proc_ops
static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read
};

unsigned long startTime = 0;

/**
 * @brief called when the module is loaded. 
 * stores the number of seconds that have elasped since system boot
 * @return int 
 */
int proc_init(){
    // proc_create creates the /proc/seconds entry - it wraps "proc_create_data()"
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    // prints to the kernal stdout that the proc entry has been created
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    // the time in seconds at which the module was loaded

    // stores the number of seconds that have elasped since system boot in startTime
    startTime = jiffies/HZ;
    return 0;
}


/**
 * @brief called when the module is remvoed - functions to remove the 
 *  proc entries
 * 
 */
void proc_exit(){
    //removes the /proc/seconds entry
    remove_proc_entry(PROC_NAME, NULL);
    //prints to kernal stdout that the proc entry has been removed
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);


}




/**
 * @brief called everytime the /proc/seconds is read
 *  displays the number of seconds that have elasped since the module was loaded
 *  this function is called repeatedly until it has collected the data that is 
 *  to go into the cooresponding /proc file
 * 
 * ultimately returns 0 once it has collected the data 
 * 
 * @param file 
 * @param usr_buf the buffer in user space
 * @param count 
 * @param pos 
 * @return ssize_t 
 */
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos){
    // retVal stores the umber of characters printed
    int retVal = 0;
    char buffer[BUFFER_SIZE]; // creates a char[] of size buffer
    static bool completed = false; // FALSE

    if (completed){
        completed = false;
        return false;
    }

    completed = true;

    //displays the number of seconds that have elasped since the module was loaded
    retVal = sprintf(buffer, "%lu\n", jiffies/HZ - startTime);

    // copies the contents of buffer to userspace usr_buf
    copy_to_user(usr_buf, buffer, retVal);

    return retVal;

}





//////////////////////
// Module setup
//////////////////////

//set module entry point and module exit point
module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("ME");







