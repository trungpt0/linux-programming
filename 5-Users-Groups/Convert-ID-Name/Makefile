TARGET = cvt-ug-id-name

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

SRCS = cvt-ug-id-name.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)