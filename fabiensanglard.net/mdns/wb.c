#ifdef _WIN32
#include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
#include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXAMPLE_PORT 5353
#define EXAMPLE_GROUP "224.0.0.251"

#define MESSAGE_BUFFER_SIZE 2048
char message[MESSAGE_BUFFER_SIZE];

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: wb [*|1](SO_REUSEADDR) [*|1](SO_REUSEPORT)\n");
        return 1;
    }
    struct sockaddr_in addr;
    socklen_t addrlen;
    int sock, cnt;
    struct ip_mreq mreq;

#ifdef _WIN32
    // Initialize Windows Socket API with given VERSION.
    WSADATA wsaData;
    if (WSAStartup(0x0101, &wsaData)) {
        perror("WSAStartup");
        return 1;
    }
#endif

    /* set up socket */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    int optval = 1;
    if (argv[1][0] == '1') {
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(optval));
    }
#if !defined(_WIN32)
    optval = 1;
    if (argv[2][0] == '1') {
        setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (char *) &optval, sizeof(optval));
    }
#endif

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(EXAMPLE_PORT);
    addrlen = sizeof(addr);

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("Cannot bind to " EXAMPLE_GROUP ":5353");
        exit(1);
    }
    mreq.imr_multiaddr.s_addr = inet_addr(EXAMPLE_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        perror("Cannot setsockopt to join group");
        exit(1);
    }
    while (1) {
        cnt = recvfrom(sock, message, MESSAGE_BUFFER_SIZE, 0, (struct sockaddr *) &addr, &addrlen);
        if (cnt < 0) {

            perror("recvfrom");
#if defined(_WIN32)
            printf("Error %d\n", WSAGetLastError());
#else
            printf("Error %d\n", cnt);
#endif
            exit(1);
        } else if (cnt == 0) {
            break;
        }
        printf("%s: message = '%c%c%c%c' size=%d\n", inet_ntoa(addr.sin_addr), message[0], message[1], message[2], message[3], cnt);
    }


    return 0;
}
