# The next line defines the kernel modules to be built
obj-m = encrypt.o

# Obtain the version of the running kernel
KVERSION = $(shell uname -r)

all: modules rot47

modules:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

rot47: rot47.c
	gcc -orot47 rot47.c
	
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
	rm rot47
