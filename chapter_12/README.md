# Chapter_12
## Files
- echo_serverp.c
  - simple parallel echo server
- echo_serverm.c
  - echo server using I/O multiplexing
- echo_servers.c
  - parallel event trigger server based on I/O multiplexing
- echo_client.c
  - client program
<br></br>

## How to run echo_serverp.c
```
gcc -I../chapter_11/tiny echo_serverp.c ../chapter_11/tiny/csapp.c -o echo_serverp
./echo_serverp 8080
```

## How to run echo_serverm.c
```
gcc -I../chapter_11/tiny echo_serverm.c ../chapter_11/tiny/csapp.c -o echo_serverm
./echo_serverm 8080
```

## How to run echo_servers.c
```
gcc -I../chapter_11/tiny echo_servers.c ../chapter_11/tiny/csapp.c -o echo_servers
./echo_servers 8080
```

## How to run echo_client.c
```
gcc -I../chapter_11/tiny echo_client.c ../chapter_11/tiny/csapp.c -o echo_client
./echo_client ::1 8080
```

## How to run thread/echo_servert_pre.c
```
gcc -I../chapter_11/tiny -I./thread thread/echo_servert_pre.c ../chapter_11/tiny/csapp.c -o echo_servert_pre
```
