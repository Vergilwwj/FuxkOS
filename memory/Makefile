ifneq ($(KERNELRELEASE),)
MODULE_NAME = memory
obj-m += $(MODULE_NAME).o
else
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
MODULEDIR := $(shell pwd)

.PHONY: modules
default: modules

modules:
	make -C $(KERNEL_DIR) M=$(MODULEDIR) modules

	gcc test_memory.c -o test_memory -Wall

clean distclean:
	rm -f *.o *.mod.c .*.*.cmd *.ko *.symvers *.order
	rm -rf .tmp_versions
	rm test_memory
endif