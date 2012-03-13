CC = m68k-atari-mint-gcc
CPUFLAGS = -mcpu=5475
CFLAGS = -Wall -O3 -fomit-frame-pointer
LDFLAGS = -s
LIBS = musashi/libmusashi.a

INCLUDES = -Imusashi
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
	
$(TARGET): musashi.stamp $(OBJS)
	$(CC) $(CPUFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

.PHONY = clean
clean:
	cd musashi && $(MAKE) clean
	rm -f $(OBJS) $(TARGET) *.stamp
