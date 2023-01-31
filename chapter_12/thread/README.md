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
