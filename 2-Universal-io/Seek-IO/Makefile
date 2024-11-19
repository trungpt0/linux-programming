TARGET = seek-io

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

SRCS = seek-io.c get_num.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
