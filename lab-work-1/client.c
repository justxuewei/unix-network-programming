#include "unp.h"

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: client <IPAddress>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    /**
     * Inet_pton() is a wrapper for `inet_pton()`, you may refer to
     * https://man7.org/linux/man-pages/man3/inet_pton.3.html.
     * 
     * inet_pton() converts IPv4 and IPv6 addresses from text to binary form.
     * 
     * Parameters:
     *  af: specify what family is used.
     *  src: IP address formatted in dotted-decimal
     *  dst: a pointer to sturct in_addr
     */
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    /**
     * `connect()` initiates TCP's three-way handshake handled by `listen()`
     * in server side.
     */
    Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    exit(0);
}