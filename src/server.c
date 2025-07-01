#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // for close()
#include <arpa/inet.h>  // for sockaddr_in, inet_ntoa()
#include "../include/system_info.h"

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 1. Create the socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Bind to an IP/Port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port 8080
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // 3. Start listening
    listen(server_socket, 1);
    printf("Server waiting for a connection on port 8080...\n");

    // 4. Accept a client
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket < 0) {
        perror("Accept failed");
        return 1;
    }
    printf("Client connected!\n");

    // 5. Get RAM and send it
    int ram_kb = get_ram();
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Available RAM: %d kB\n", ram_kb);
    send(client_socket, buffer, strlen(buffer), 0);

    // 6. Close connections
    close(client_socket);
    close(server_socket);
    return 0;
}
