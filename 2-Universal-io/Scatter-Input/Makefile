TARGET = scatter-input

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

SRCS = scatter-input.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
