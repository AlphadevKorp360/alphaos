# C++, LD, AS Executable and Flags:
CXX = gcc
LD = ld
AS = as
ASPARAMS = --32
LDPARAMS = -melf_i386

# SOURCE DIRECTORY:
SRC		:= src
INCLUDE	:= include
LIB		:= lib
BOOTLOADER := bootloader

BOOTLOADERDIR := $(shell find $(BOOTLOADER) -type d)
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# Execute Make Task directory Through ($ make all /$ make):
all:
	$(AS) $(ASPARAMS) $(BOOTLOADERDIR)/boot.asm -o boot.o
	$(CXX) -m32 $(INCLUDES) -c $(SOURCEDIRS)/kernel.cpp -o kernel.o -std=c++23 -nostdlib -ffreestanding -g -O2 -Wall -Wextra -Wwrite-strings
	$(LD) $(LDPARAMS) -T linker.ld kernel.o boot.o -o alphaos.bin -nostdlib

	# Create ISO and Run on Emulator (KVM):
	grub-file --is-x86-multiboot alphaos.bin
	mkdir -p isodir/boot/grub
	cp alphaos.bin isodir/boot/alphaos.bin
	cp $(BOOTLOADERDIR)/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o alphaos.iso isodir
	(killall qemu-system-x86_64 && sleep 1) || true
	qemu-system-x86_64 -cdrom alphaos.iso
	rm -rf isodir alphaos.bin alphaos.iso kernel.o boot.o
