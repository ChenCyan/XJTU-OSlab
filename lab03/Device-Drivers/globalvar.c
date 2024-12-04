#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/semaphore.h>
MODULE_LICENSE("GPL");
#define MAJOR_NUM 290

static int global_var = 0;           // 用于模拟设备的全局变量
static struct semaphore write;
static struct semaphore read;         // 用于同步的信号量
static struct semaphore sem;
// 函数声明
static ssize_t globalvar_read(struct file *, char *, size_t, loff_t*);
static ssize_t globalvar_write(struct file *, const char *, size_t, loff_t*);
static int globalvar_open(struct inode *, struct file *);
static int globalvar_release(struct inode *, struct file *);

// 文件操作结构体
struct file_operations globalvar_fops = {
    .open = globalvar_open,
    .read = globalvar_read,
    .write = globalvar_write,
    .release = globalvar_release
};

// 模块初始化函数
static int __init globalvar_init(void) {
    int ret;

    // 初始化信号量
    sema_init(&sem, 1);
    sema_init(&read,0);
    sema_init(&write,1);
    // 注册字符设备
    ret = register_chrdev(MAJOR_NUM, "globalvar", &globalvar_fops);
    if (ret) {
        printk("globalvar register failure\n");
        return ret;
    } else {
        printk("globalvar register success\n");
    }
    return 0;
}

// 模块清理函数
static void __exit globalvar_exit(void) {
    unregister_chrdev(MAJOR_NUM, "globalvar");
    printk("globalvar module exited\n");
}

// open()函数
static int globalvar_open(struct inode *inode, struct file *file) {
    printk("globalvar device opened\n");
    return 0;
}

// release()函数
static int globalvar_release(struct inode *inode, struct file *file) {
    printk("globalvar device released\n");
    return 0;
}

// read()函数
static ssize_t globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off) {
    // 使用信号量来保护共享资源
    if (down_interruptible(&sem) || down_interruptible(&read)) {
        return -ERESTARTSYS;  // 被信号中断
    }
    
    // 模拟读操作，将 global_var 的值复制到用户空间
    if (copy_to_user(buf, &global_var, sizeof(int))) {
        up(&sem);
        up(&read);
        return -EFAULT;
    }

    up(&sem);  // 操作完成后释放信号量
    up(&write);
    return sizeof(int);

}

// write()函数
static ssize_t globalvar_write(struct file *filp, const char *buf, size_t len, loff_t *off) {
    // 使用信号量来保护共享资源
    if (down_interruptible(&sem) || down_interruptible(&write)) {
        return -ERESTARTSYS;  // 被信号中断
    }

    // 模拟写操作，将用户空间的数据复制到 global_var
    if (copy_from_user(&global_var, buf, sizeof(int))) {
        up(&sem);
        up(&write);
        return -EFAULT;
    }

    up(&sem);  // 操作完成后释放信号量
    up(&read);
    return sizeof(int);
}

module_init(globalvar_init);
module_exit(globalvar_exit);
