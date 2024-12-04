ifneq ($(KERNELRELEASE),)
obj-m := mymodules.o
else
	KERNELDIR := /lib/modules/$(shell uname -r)/build # 指向内核源码目录
	PWD := $(shell pwd)

modules:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules # 编译内核模块
endif
