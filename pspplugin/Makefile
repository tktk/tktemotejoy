TARGET = tktemotejoy
OBJS = \
    src/tktemotejoy/exports.o \
    src/tktemotejoy/main.o \
    src/tktemotejoy/hook.o \
    src/tktemotejoy/ctrl.o \

USE_KERNEL_LIBC = 1
USE_KERNEL_LIBS = 1

INCDIR = 
CFLAGS = -std=gnu11 -Os -G0 -Wall -fno-builtin-printf -Iinc -I../../psplinkusb/usbhostfs
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS = -L../../psplinkusb/libusbhostfs_driver
LIBS = -lusbhostfs_driver -lpspusb_driver

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
