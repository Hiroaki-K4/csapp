#include "csapp.h"

void read_requesthdrs(rio_t *rp)
{
    char buf[MAXLINE];

    rio_readlineb(rp, buf, MAXLINE);
    while (strcmp(buf, "\r\n")) {
        rio_readlineb(rp, buf, MAXLINE);
        printf("readline: %s\n", buf);
    }
    return;
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
    char *ptr;

    if (!strstr(uri, "cgi-bin")) { // Static content
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/')
            strcat(filename, "home.html");
        return 1;
    }
    else {
        ptr = index(uri, '?');
        if (ptr) {
            strcpy(cgiargs, ptr + 1);
            *ptr = '\0';
        } else {
            strcpy(cgiargs, "");
        }
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

void doit(int fd)
{
    int is_static;
    // struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    // Read request line and headers
    rio_readinitb(&rio, fd);
    rio_readlineb(&rio, buf, MAXLINE);
    printf("Request headers:\n");
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);
    printf("method: %s uri: %s version: %s\n", method, uri, version);
    int cmp_res = strcasecmp(method, "GET");
    printf("cmp_res: %d\n", cmp_res);
    if (cmp_res != 0) {
        // clienterror(fd, method, "501", "Not implemented", "Tiny does not implement this method");
        printf("Tiny does not implement this method\n");
        return;
    }
    read_requesthdrs(&rio);

    // Parse URI from GET request
    is_static = parse_uri(uri, filename, cgiargs);
    printf("is_static: %d\n", is_static);
    // if (stat(filename, &sbuf < 0) < 0) {
    //     clienterror(fd, filename, "404", "Not found", "Tiny cloudn't find this file");
    //     return;
    // }
    // if (is_static) { // Serve static content
    //     if (!(S_ISREG(sbuf.st_mode) || !(S_IRUSR & sbuf.st_mode))) {
    //         clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't read the file");
    //         return;
    //     }
    //     serve_static(fd, filename, sbuf,st_size);
    // }
    // else { // Serve dynamic content
    //     if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
    //         clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
    //         return;
    //     }
    //     serve_dynamic(fd, filename, cgiargs);
    // }
}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];

    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }
    listenfd = open_listenfd(argv[1]);
    printf("Server listenfd: %d\n", listenfd);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        doit(connfd);
        close(connfd);
    }
    return 0;
}
