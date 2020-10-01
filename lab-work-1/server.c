#include "unp.h"

int main(int argc, char **argv) {
    int listenfd, connfd;
    // pid_t is a signed integer type defined in `sys/types.h`
    pid_t childpid;
    // socklen_t is an unsigned integer type defined in `sys/socket.h`
    socklen_t clilen;
    // sockaddr_in is a struct for handling internet address defined in `netinet/in.h`
    struct sockaddr_in cliaddr, servaddr;

    /**
     * Socket() is a wrapper for socket which is defined in `sys/socket.h`.
     * See: unpv13e/lib/wrapsock.c
     * 
     * Parameters
     *  family: the value is AF_INET, which means IPv4 protocol.
     *  type: the value is SOCK_STREAM.
     *  protocol: the value is 0, which means select a system's default for 
     *          the given conbination of family and type.
     */
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    /** 
     * The bzero() function erases the data in the n bytes of the memory
     * starting at the location pointed to by s, by writing zeros (bytes
     * containing '\0') to that area.
     */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    /**
     * `INADDR_ANY` instructs listening socket to bind to all available interfaces,
     * it's the same as trying to bind to `0.0.0.0`.
     * 
     * htonl() converts from host byte to network byte order.
     */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /**
     * SERV_PORT is a constant with a value of 9877 defined in `unpv13e/lib/unp.h`.
     *
     * The function of htons() is same as htonl(). The only difference between them
     * is that the type of the parameter for htonl() is uint32_t, and for htons() is
     * uint16_t.
     */
    servaddr.sin_port = htons(SERV_PORT);

    /**
     * `SA` is a type alias for `struct sockaddr`, which defined in `unpv13e/lib/unp.h`.
     * `struct sockaddr` is defined in `sys/socket.h`. The difference between `sockaddr`
     * and `sockaddr_in` is a member named `sa_data` in `sockaddr` mixs address with 
     * port, however, in `sockaddr_in` ip address and port is separated.
     */
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    /**
     * Listen() is a wrapper for listen(), which moves the socket from the CLOSED state 
     * to the LISTEN state.
     * 
     * Parameters:
     *  sockfd: an integer value returned from socket().
     *  backlog: specify the maximun number of connections the kernel should queue for 
     *          this socket. In this case, LISTENQ is defined by `unpv13e/lib/unp.h` to
     *          1024.
     */
    Listen(listenfd, LISTENQ);

    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        /**
         * A connection could be accpeted only if three-way handshake was completed.
         * 
         * The return value of appect() is a descriptor which refers to the TCP
         * connection with the client. The connection will be closed, in other words, 
         * a FIN will be sent to client, if the reference count for the descriptor is
         * equals to 0.
         *
         * If you are not insteaded in the data related to client, cliaddr & addrlen
         * could be null.
         */
        connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);

        if ((childpid = Fork()) == 0) {
            Close(listenfd);
            str_echo(connfd);
            // Optional
            // Close(connfd)
            exit(0);
        }
        Close(connfd);
    }

    return 0;
}
