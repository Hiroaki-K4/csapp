NAME := tiny

SRCS := tiny.c csapp.c

OBJS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I.

all: $(NAME)

%.o: %.c
	$(CC) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

.PHONY: all clean fclean
