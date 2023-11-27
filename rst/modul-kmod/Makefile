obj-m := my_module.o

PWD := $(shell pwd)
KDIR := /lib/modules/$(shell uname -r)/build
#make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
