KERNEL_DIR := /lib/modules/$(shell uname -r)/build
obj-m := hello-1.o
obj-m := hello-2.o
obj-m := param.o
obj-m := gpio2file.o
all:
	make -C ${KERNEL_DIR} M=$(PWD) modules
clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean

