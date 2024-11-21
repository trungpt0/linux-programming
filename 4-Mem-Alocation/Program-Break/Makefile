TARGET = break-free

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

SRCS = break-free.c get_num.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
