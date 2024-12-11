#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define sys_No 78  // syscall number for gettimeofday

// 在aarch64架构下，每个syscall表项是8字节
unsigned long old_sys_call_func;
unsigned long p_sys_call_table = 0xffff000008af0698;  // sys_call_table地址（根据你的架构和内核版本调整）

asmlinkage int hello(int a, int b) {
    printk("No 78 syscall has changed to hello\n");
    return a + b;  // 返回a + b的和
}

// 修改syscall
void modify_syscall(void) {
    unsigned long *sys_call_addr;
    sys_call_addr = (unsigned long *)(p_sys_call_table + sys_No * 8);  // aarch64架构每个syscall占8字节

    old_sys_call_func = *(sys_call_addr);  // 保存原来的syscall函数地址
    *(sys_call_addr) = (unsigned long)&hello;  // 将syscall表项替换为新的hello函数
}

// 恢复syscall
void restore_syscall(void) {
    unsigned long *sys_call_addr;
    sys_call_addr = (unsigned long *)(p_sys_call_table + sys_No * 8);  // aarch64架构每个syscall占8字节

    *(sys_call_addr) = old_sys_call_func;  // 恢复原来的syscall函数地址
}

// 初始化模块
static int mymodule_init(void) {
    printk("Loading syscall modifier module\n");
    modify_syscall();  // 修改syscall表
    return 0;
}

// 卸载模块
static void mymodule_exit(void) {
    printk("Unloading syscall modifier module\n");
    restore_syscall();  // 恢复syscall表
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A module to modify syscall");

