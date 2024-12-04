#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/unistd.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<linux/fdtable.h>
#include<linux/uaccess.h>

#include<linux/rtc.h>

MODULE_LICENSE("Dual BSD/GPL");
 
#define _DEBUG
#ifdef _DEBUG
#define kprintk(fmt,args...) printk(KERN_ALERT fmt,##args)
#define kprintf(fmt,args...) printf(fmt,##args)
#define kperror(str) perror(str)
#else
#define kprintk
#define kprintf
#define kperror
#endif

/*Function declaration*/
long * get_sys_call_table(void);

long * g_sys_call_table=NULL;//save address of sys_call_table

struct _idtr{
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

struct _idt_descriptor{
    unsigned short offset_low;
    unsigned short sel;
    unsigned char none,flags;
    unsigned short offset_high;
}__attribute__((packed));

/*Get the address of sys_call_table*/
long * get_sys_call_table(void){
    
    struct _idt_descriptor * idt;
    struct _idtr idtr;
    unsigned int sys_call_off;
    int sys_call_table=0;
    unsigned char* p;
    int i;
    asm("sidt %0":"=m"(idtr));
    kprintk("   address of idtr: 0x%x\n",(unsigned int)&idtr);
    idt=(struct _idt_descriptor *)(idtr.base+8*0x80);
    sys_call_off=((unsigned int)(idt->offset_high<<16)|(unsigned int)idt->offset_low);
    kprintk("   address of idt 0x80: 0x%x\n",sys_call_off);
    p=(unsigned char *)sys_call_off;
    for(i=0;i<100;i++){
        if(p[i]==0xff&&p[i+1]==0x14&&p[i+2]==0x85){
            sys_call_table=*(int*)((int)p+i+3);
            kprintk("   address of sys_call_table: 0x%x\n",sys_call_table);

            return (long*)sys_call_table;
        }
    }
    
    return 0;
}

int monitor_init(void){
    kprintk("Monitor init\n");
    g_sys_call_table = get_sys_call_table();
    return 0;
}

void monitor_exit(void){
    kprintk("Monitor exit\n");
}

module_init(monitor_init);
module_exit(monitor_exit);
