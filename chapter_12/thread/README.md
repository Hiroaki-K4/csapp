# Thread
## How to run hello.c
```
gcc -pthread -I../../chapter_11/tiny hello.c -o hello
./hello
```
```
gcc -pthread -I../../chapter_11/tiny sharing.c -o sharing
./sharing
```
```
gcc -pthread -I../../chapter_11/tiny cnt.c -o cnt
./cnt 1000000
```
## How to run thread/echo_servert_pre.c
```
gcc -pthread -I../../chapter_11/tiny -I. echo_servert_pre.c sbuf.c  ../../chapter_11/tiny/csapp.c -o echo_servert_pre
./echo_servert_pre 8080
```

## How to run echo_client.c
```
gcc -pthread -I../../chapter_11/tiny echo_client.c ../../chapter_11/tiny/csapp.c -o echo_client
```

## How to run psum_mutex.c
```
gcc -pthread -I../../chapter_11/tiny psum_mutex.c ../../chapter_11/tiny/csapp.c -o psum_mutex
./psum_mutex 1 31
```
