# per https://www.kernel.org/doc/html/v7.2/kbuild/modules.html - shared makefile

ifneq ($(KERNELRELEASE),)
obj-m := hello_hid.o

else
KDIR ?= /lib/modules/`uname -r`/build

all: install

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install: modules
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

rules: all
	cp -v 99-hello_hid*.rules /etc/udev/rules.d/
	udevadm control --reload-rules && udevadm trigger

re: clean all

.PHONY: all modules clean re rules

endif
