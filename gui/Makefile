#
# A Simple Makefile Template of GNU make for library
# Copyright (c) 1998, Soliton Technologies CO., LTD.
# Author: kccheng@hepmail.phys.sinica.edu.tw (Kuang-chun Cheng)
#

#
# Variables
#
LINUX_SHARED = liblinux.so
LINUX_SRC   := linux.c
LINUX_OBJ   := $(patsubst %.c, %.o, $(LINUX_SRC))

DRV_SRC    =
DRV_OBJ   := $(patsubst %.c, %.o, $(DRV_SRC))

SHELL      = /bin/sh
CFLAGS     = -O2
LDFLAGS    = -L/usr/local/lib -ltcl
ARFLAGS    =
DEBUG      = -Wall -g
INCLUDE    = -I/usr/local/include -I.

.SUFFIXES:
.SUFFIXES: .c .o

#
# Rules 
#
.PHONY: all install uninstall depend test clean
all: depend $(TCL_SHARED) $(LINUX_SHARED) $(DRV_OBJ)
	@echo "make all..."

#
# Make utility
#
$(filter %.o, $(TCL_OBJ)): %.o: %.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(INCLUDE) $< -o $@

$(TCL_SHARED): $(TCL_OBJ)
	@echo "make $(TCL_SHARED)..."
	$(CC) -shared $< -o $@
#	ar -cr $(TCL_SHARED) $(TCL_OBJ)
#	-ranlib $(TCL_SHARED)

$(LINUX_SHARED): $(LINUX_OBJ)
	@echo "make $(LINUX_SHARED)..."
	$(CC) -shared $< -o $@
#	ar -cr $(LINUX_SHARED) $(LINUX_OBJ)
#	-ranlib $(LINUX_SHARED)

$(filter %.o, $(DRV_OBJ)): %.o: %.c
	$(CC) -c -D__KERNEL__ -DMODULE $(CFLAGS) $(DEBUG) $(INCLUDE) $< -o $@

install:
	@echo "make install..."

uninstall:
	@echo "make uninstall..."

depend:
	@echo "make depend..."
	@makedepend -Y \
		-- $(INCLUDE) -- $(TCL_SRC) $(LINUX_SRC) $(DRV_SRC) 2> /dev/null    

test:
	@echo "make test..."

clean:
	@echo "make clean..."
	-$(RM) $(TCL_OBJ) $(LINUX_OBJ) $(DRV_OBJ)
	-$(RM) $(TCL_SHARED) $(LINUX_SHARED)

# DO NOT DELETE
