#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbba681f6, "module_layout" },
	{ 0x28ebf353, "cdev_del" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xc489d629, "cdev_add" },
	{ 0x9f17caaf, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xad27f361, "__warn_printk" },
	{ 0xb35dea8f, "__arch_copy_to_user" },
	{ 0x98cf60b3, "strlen" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x1000e51, "schedule" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xe1537255, "__list_del_entry_valid" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0xcf2a6966, "up" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0x37a0cba, "kfree" },
	{ 0x25170ad2, "down_interruptible" },
	{ 0xa202a8e5, "kmalloc_order_trace" },
	{ 0x9166fada, "strncpy" },
	{ 0xb742fd7, "simple_strtol" },
	{ 0x349cba85, "strchr" },
	{ 0x84bc974b, "__arch_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xdcb764ad, "memset" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x1f7386be, "__ll_sc_atomic_add" },
	{ 0x7c32d0f0, "printk" },
	{ 0xf9a3efb9, "__ll_sc_atomic_sub" },
	{ 0x1fdc7df2, "_mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "EA6E9E35F52CFE139C5B540");
