#include <linux/kallsyms.h>

unsigned long *sys_call_table;

sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
if (sys_call_table) {
    printk("sys_call_table address: %lx\n", (unsigned long)sys_call_table);
}
