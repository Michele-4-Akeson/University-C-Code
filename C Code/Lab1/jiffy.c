#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <stdbool.h>

/*
This Kernal module that prints the jiffies value (the number of time interrupts
that have occured since the system was booted) when cat /proc/jiffies command is used
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
#define PROC_NAME "jiffies"



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

/**
 * @brief called when the module is loaded
 * 
 * @return int 
 */
int proc_init(){
    // proc_create creates the /proc/jiffies entry 
    // this function call wraps "proc_create_data()", passing NULL as the last argument
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    // prints to the kernal stdout that the proc entry has been created
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
    return 0;
}


/**
 * @brief called when the module is remvoed - functions to remove the 
 *  proc entries
 * 
 */
void proc_exit(){
    //removes the /proc/jiffies entry
    remove_proc_entry(PROC_NAME, NULL);
    //prints to kernal stdout that the proc entry has been removed
    printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);


}




/**
 * @brief called everytime the /proc/jiffies is read
 * 
 *  this function is called repeatedly until it has collected the data that is 
 *  to go into the cooresponding /proc file
 * 
 * @param file 
 * @param usr_buf the buffer in user space
 * @param count 
 * @param pos 
 * @return ssize_t 
 */
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos){
    // retVal stores the number of characters printed
    int retVal = 0;
    char buffer[BUFFER_SIZE]; // creates a char[] of size buffer
    static int completed = false; // FALSE

    if (completed){
        completed = false;
        return false;
    }

    completed = true;
    //display the number of time interrupts that have occured since the system was booted
    retVal = sprintf(buffer, "%lu\n", jiffies);

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
MODULE_DESCRIPTION("Jiffies Module");
MODULE_AUTHOR("ME");







