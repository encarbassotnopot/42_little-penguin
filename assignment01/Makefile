# per https://www.kernel.org/doc/html/v7.2/kbuild/modules.html - shared makefile

ifneq ($(KERNELRELEASE),)
obj-m := main.o

else
KDIR ?= /lib/modules/`uname -r`/build

all: modules

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

re: clean all

.PHONY: all modules clean re

endif
