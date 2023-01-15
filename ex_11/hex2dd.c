#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Please enter arg!\n");
        return (0);
    }

    uint32_t hex;
    sscanf(argv[1], "%x", &hex);
    uint32_t hex_n = htonl(hex);
    char ans[16];
    if (!inet_ntop(AF_INET, &hex_n, ans, 16)) {
        printf("inet_ntop error!");
        return (1);
    }
    printf("%s\n", ans);

    return (0);
}
