# musashi/Makefile
# Written in 2010-2012 by Vincent Riviere <vincent.riviere@freesbee.fr>
#
# This file is part of:
# 68Kemu - A CPU emulator for Atari TOS computers
# http://vincent.riviere.free.fr/soft/68kemu/
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along
# with this software.
# If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

# Warning: The purpose of this Makefile is to build the Musashi CPU emulator,
# which is Copyright 1998-2001 Karl Stenerud and provided with its own license.
# There are restrictions for using and redistributing Musashi.
# See readme.txt in 3rd-party/musashi-3.3.1/musashi331.zip for details.

CC = m68k-atari-mint-gcc
CPUFLAGS = -mcpu=5475
CFLAGS = -Wall -O3 -fomit-frame-pointer
AR = m68k-atari-mint-ar

NATIVE_CC = gcc
NATIVE_CFLAGS = -O -Wall -pedantic

M68KMAKE_SOURCES = m68kmake.c
M68KMAKE_INPUT = m68k_in.c

CFILES = m68kcpu.c m68kdasm.c
HFILES = m68k.h m68kconf.h m68kcpu.h
FILES = $(CFILES) $(HFILES) $(M68KMAKE_SOURCES) $(M68KMAKE_INPUT)

GENCFILES = m68kops.c m68kopnz.c m68kopdm.c m68kopac.c
GENHFILES = m68kops.h
GENFILES = $(GENCFILES) $(GENHFILES)

OBJS = $(patsubst %.c,%.o,$(CFILES) $(GENCFILES))

.PHONY: all
all:	libmusashi.a

.PHONY: unzip
unzip: unzip.stamp
unzip.stamp:
	unzip ../3rd-party/musashi-3.3.1/musashi331.zip
	touch $@

.PHONY: patch
patch: patch.stamp
patch.stamp: unzip.stamp
	patch -p1 <musashi.patch
	touch $@

$(FILES): patch.stamp

m68kmake: $(M68KMAKE_SOURCES)
	$(NATIVE_CC) $(NATIVE_CFLAGS) $^ -o $@

$(GENFILES): m68kmake $(M68KMAKE_INPUT)
	./m68kmake . $(M68KMAKE_INPUT)

$(OBJS): %.o: %.c
	$(CC) $(CPUFLAGS) $(CFLAGS) -c $<

libmusashi.a: $(OBJS)
	$(AR) cr $@ $^
	
clean:
	rm -f $(filter-out Makefile musashi.patch, $(wildcard *))

# Dependencies
m68kcpu.o: m68kops.h m68kcpu.h
m68kopac.o: m68kcpu.h
m68kopdm.o: m68kcpu.h
m68kopnz.o: m68kcpu.h
