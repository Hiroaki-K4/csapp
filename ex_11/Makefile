NAME := csapp

CLIENT := client
SERVER := server
TINY := tiny

CLIENT_SRCS := echo_client.c csapp.c
SERVER_SRCS := echo_server.c csapp.c
TINY_SRCS := tiny.c csapp.c

CLIENT_OBJS := $(CLIENT_SRCS:.c=.o)
SERVER_OBJS := $(SERVER_SRCS:.c=.o)
TINY_OBJS := $(TINY_SRCS:.c=.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I.

%.o: %.c
	$(CC) $(INCLUDE) -c $< -o $@

$(client): $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT)

build_client: $(client)

$(server): $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(SERVER)

build_server: $(server)

$(TINY): $(TINY_OBJS)
	$(CC) $(TINY_OBJS) -o $(TINY)

build_tiny: $(TINY)

clean:
	rm $(CLIENT) $(SERVER) $(TINY) a.out

.PHONY: client server clean build_client build_server build_tiny
