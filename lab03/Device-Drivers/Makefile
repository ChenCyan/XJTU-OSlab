obj-m := globalvar.o

# 用于查找内核的源代码路径
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# 编译模块
all:
	make -C $(KDIR) M=$(PWD) modules

# 清理构建产物
clean:
	make -C $(KDIR) M=$(PWD) clean

# 安装模块
install:
	sudo insmod globalvar.ko

# 卸载模块
uninstall:
	sudo rmmod globalvar

# 查看内核日志
log:
	dmesg | tail -n 20

