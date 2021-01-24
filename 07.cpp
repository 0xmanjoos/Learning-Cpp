#include <iostream>
#include <time.h>

#ifdef _WIN32
#include <windows.h>

#define LEN 1000
#else

#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <cstring>
#define LEN 1
#define BUFFER 1024
#endif

// this should be where we get into the networking side of things
// this one will demonstrate a socket server in *NIX systems, next will be with winsock2

void handle(const char* errorMessage) {
    perror(errorMessage);
    exit(1);
}

int main(int argc, char* argv[]) {
    system("echo socket server has started, do \"netstat -tulpn\" or something of the sort to see port");
    // define the buffer size
    char message[BUFFER];
    // file descriptors
    int lfd, cfd;
    // setup
    struct sockaddr_in addr;
    // AF_INET is ipv4 and SOCK_STREAM is TCP
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    // clear out buffer
    bzero(&addr, sizeof(addr));
    // specify
    addr.sin_family = AF_INET;
    // bind to 0.0.0.0, which is all interfaces
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    // for some reason this keeps changing to a random port
    // :/
    addr.sin_port = htons(4444);
    // bind to the port
    bind(lfd, (struct sockaddr*) NULL, NULL);
    // listen and accept a maximum of 10 concurrent connections
    listen(lfd, 10);
    // accept connections
    cfd = accept(lfd, (struct sockaddr*) NULL, NULL);

    while(1) {
        // clear out message again
        memset(message, 0, BUFFER);
        // read at most 1024 bytes
        read(cfd, message, 1024);
        // output
        std::cout<<"Message: "<<message;
        // send back data
        write(cfd, message, strlen(message)+1);
    }
    return 0;
}

