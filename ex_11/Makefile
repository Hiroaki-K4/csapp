NAME := csapp

CLIENT := client
SERVER := server
TINY := tiny

CLIENT_SRCS := echo_client.c csapp.c
SERVER_SRCS := echo_server.c csapp.c
TINY_SRCS := tiny.c csapp.c

CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I.

client:
	$(CC) $(CFLAGS) $(INCLUDE) $(CLIENT_SRCS) -o $(CLIENT)

server:
	$(CC) $(CFLAGS) $(INCLUDE) $(SERVER_SRCS) -o $(SERVER)

tiny:
	$(CC) $(CFLAGS) $(INCLUDE) $(TINY_SRCS) -o $(TINY)

clean:
	rm $(CLIENT) $(SERVER) $(TINY)

.PHONY: client server clean a.out
