ifneq ($(KERNELRELEASE),)
MODULE_NAME = memory
obj-m += $(MODULE_NAME).o
else
KERNEL_DIR = /home/panda/wangwenjia/git/kernel_ssc337
MODULEDIR := $(shell pwd)

.PHONY: modules
default: modules

modules:
	make -C $(KERNEL_DIR) M=$(MODULEDIR) modules

	arm-sstaru494-linux-gcc test_memory.c -o test_memory -Wall

clean distclean:
	rm -f *.o *.mod.c .*.*.cmd *.ko *.symvers *.order
	rm -rf .tmp_versions
	rm test_memory

install:
	cp *.ko /home/share/wangwenjia/337
	cp test_memory /home/share/wangwenjia/337
endif