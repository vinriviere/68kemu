VPATH = musashi

MULTILIB_FLAGS = -mcpu=5475
#MULTILIB_FLAGS = 
MULTILIB_FLAGS_TARGET = -m68000
CFLAGS = -O3 -fomit-frame-pointer -Wall
#CFLAGS = -g
LDFLAGS = -s
GCC = m68k-atari-mint-gcc
CC = $(GCC) $(MULTILIB_FLAGS)
CC_TARGET = $(GCC) $(MULTILIB_FLAGS_TARGET)
INCLUDES = -Imusashi
EXEFILE = 68kemu.prg

MUSASHI_OBJS = $(notdir $(patsubst %.c,%.o,$(wildcard musashi/*.c)))
MAIN_OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
HOST_OBJS = $(MUSASHI_OBJS) $(MAIN_OBJS)
TARGET_OBJS = asm.o
OBJS = $(HOST_OBJS) $(TARGET_OBJS)

.PHONY = all
all: $(EXEFILE)

$(EXEFILE): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(HOST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET_OBJS): %.o: %.S
	$(CC_TARGET) $(INCLUDES) -c $< -o $@

.PHONY = clean
clean:
	rm -f $(OBJS) $(EXEFILE)
