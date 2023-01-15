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

    // uint32_t hex;
    // sscanf(argv[1], "%x", &hex);
    // uint32_t hex_n = htonl(hex);
    uint32_t ans;
    if (!inet_pton(AF_INET, argv[1], &ans)) {
        printf("inet_pton error!");
        return (1);
    }
    uint32_t final_ans;
    final_ans = ntohl(ans);
    printf("0x%x\n", final_ans);

    return (0);
}
