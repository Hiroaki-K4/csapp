NAME := csapp

CLIENT_SRCS := echo_client.c csapp.c
SERVER_SRCS := echo_server.c csapp.c

CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I.

client:
	$(CC) $(CFLAGS) $(INCLUDE) $(CLIENT_SRCS) -o client

server:
	$(CC) $(CFLAGS) $(INCLUDE) $(SERVER_SRCS) -o server

clean:
	rm client server

.PHONY: client server clean
