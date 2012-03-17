# Makefile
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

CC = m68k-atari-mint-gcc
CPUFLAGS = -mcpu=5475
CFLAGS = -Wall -O3 -fomit-frame-pointer
LDFLAGS = -s
LIBS = musashi/libmusashi.a

TARGET = 68kemu.prg

OBJS = 68kemu.o asm.o

.PHONY = all
all: $(TARGET)

%.o: %.c musashi.stamp
	$(CC) $(CPUFLAGS) $(CFLAGS) -c $<

%.o: %.S musashi.stamp
	$(CC) $(CPUFLAGS) $(CFLAGS) -c $<

.PHONY: musashi
musashi: musashi.stamp
musashi.stamp:
	cd musashi && $(MAKE) libmusashi.a
	touch $@
	
$(TARGET): musashi.stamp $(OBJS) $(LIBS)
	$(CC) $(CPUFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

.PHONY = clean
clean:
	cd musashi && $(MAKE) clean
	rm -f $(OBJS) $(TARGET) *.stamp
