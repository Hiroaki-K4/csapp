# Chapter_12
- echo_serverp.c
- echo_client.c
- echo_serverm.c

## How to build echo_serverp.c
```
gcc -I../chapter_11/tiny echo_serverp.c ../chapter_11/tiny/csapp.c -o echo_serverp
```

## How to run echo_serverp
```
./echo_serverp 8080
```

## How to build echo_client.c
```
gcc -I../chapter_11/tiny echo_client.c ../chapter_11/tiny/csapp.c -o echo_client
```

## How to run echo_client
```
./echo_client ::1 8080
```
