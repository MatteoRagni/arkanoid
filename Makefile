TARGET_EXEC ?= arkanoid

SRCS := $(shell ls *.c)
OBJS := $(SRCS:%.c=%.o)
DEPS := $(OBJS:.o=.d)

CC := gcc
CFLAGS := -Wall -O2
LDFLAGS := -lglut -lglfw -lGL -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

default: $(TARGET_EXEC)

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET_EXEC)