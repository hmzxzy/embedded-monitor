#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // close()
#include <arpa/inet.h>  // socket, connect, sockaddr_in

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[128] = {0};

    // 1. Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // must match server
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // 3. Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // 4. Receive and print
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Server says: %s", buffer);

    close(client_socket);
    return 0;
}
