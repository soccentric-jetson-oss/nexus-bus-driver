#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "dump_stack" },
	{ 0xe8213e80, "_printk" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xb485f613, "_dev_info" },
	{ 0xdb375fb3, "cdev_add" },
	{ 0xb485f613, "_dev_err" },
	{ 0x160b81b4, "device_create" },
	{ 0x7ed256c3, "noop_llseek" },
	{ 0x07a5cde6, "class_unregister" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0xfb598b3a, "__platform_driver_register" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0xd17123e4, "device_destroy" },
	{ 0x1a29d1ea, "dev_err_probe" },
	{ 0x189ec92d, "class_register" },
	{ 0xd2554727, "cdev_init" },
	{ 0x2e921116, "cdev_del" },
	{ 0x9aa6980d, "mutex_init_generic" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x5ce224b8, "devm_kmalloc" },
	{ 0x0064884b, "platform_driver_unregister" },
	{ 0x385ea3b7, "__dynamic_dev_dbg" },
	{ 0xd954c786, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xd272d446,
	0xe8213e80,
	0xbd03ed67,
	0xd272d446,
	0xb485f613,
	0xdb375fb3,
	0xb485f613,
	0x160b81b4,
	0x7ed256c3,
	0x07a5cde6,
	0xd272d446,
	0x092a35a2,
	0xfb598b3a,
	0x0bc5fb0d,
	0xd17123e4,
	0x1a29d1ea,
	0x189ec92d,
	0xd2554727,
	0x2e921116,
	0x9aa6980d,
	0x9f222e1e,
	0x092a35a2,
	0x5ce224b8,
	0x0064884b,
	0x385ea3b7,
	0xd954c786,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"dump_stack\0"
	"_printk\0"
	"__ref_stack_chk_guard\0"
	"__stack_chk_fail\0"
	"_dev_info\0"
	"cdev_add\0"
	"_dev_err\0"
	"device_create\0"
	"noop_llseek\0"
	"class_unregister\0"
	"__x86_return_thunk\0"
	"_copy_to_user\0"
	"__platform_driver_register\0"
	"unregister_chrdev_region\0"
	"device_destroy\0"
	"dev_err_probe\0"
	"class_register\0"
	"cdev_init\0"
	"cdev_del\0"
	"mutex_init_generic\0"
	"alloc_chrdev_region\0"
	"_copy_from_user\0"
	"devm_kmalloc\0"
	"platform_driver_unregister\0"
	"__dynamic_dev_dbg\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cnvidia,tegra234-nexus-bus");
MODULE_ALIAS("of:N*T*Cnvidia,tegra234-nexus-busC*");

MODULE_INFO(srcversion, "AFB2A77E3847EF31FF53C24");
