# Chapter_11 tiny server(simple http server)
This is the simple http server.
<br></br>

## How to build
```
make
gcc -I. client.c -o client
```
<br></br>

## How to run
tiny server
```
tiny <Port>
```
client
```
./client <Host> <Port>
```
<br></br>

## http request(static contents)
You can request static contents from tiny server. In the example below, the server will return the contents of home.html
```
GET / HTTP/1.1
```
## http request(dynamic contents)
You can request dynamic contents from tiny server. In the example below, the server returns the result of an adder program (cgi) that adds two values.
```
GET /cgi-bin/adder?15000&213 HTTP/1.1
```
