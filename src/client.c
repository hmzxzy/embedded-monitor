// src/client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // close(), read(), sleep()
#include <arpa/inet.h>      // socket(), connect(), sockaddr_in
#include <sys/select.h>     // select()

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define INTERVAL 5  // seconds

int main() {
    struct sockaddr_in server_addr;
    fd_set read_fds;
    struct timeval timeout;

    // Prepare server info once
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    while (1) {
        //Wait for 5 seconds without wasting CPU
        FD_ZERO(&read_fds);
        timeout.tv_sec = INTERVAL;
        timeout.tv_usec = 0;
        select(0, NULL, NULL, NULL, &timeout);  // Just wait

        //Connect to the server
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket failed");
            continue;
        }

        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("Connection failed");
            close(sock);
            continue;
        }

        //Receive JSON response
        char buffer[256] = {0};
        read(sock, buffer, sizeof(buffer));
        printf("Server says: %s\n", buffer);

        close(sock);
    }

    return 0;
}

