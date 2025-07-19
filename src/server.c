#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/system_info.h"

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(server_socket, 1);
    printf("Server waiting for a connection on port 8080...\n");

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket < 0) {
        perror("Accept failed");
        return 1;
    }
    printf("Client connected!\n");

    int ram_kb = get_ram();
    float uptime = get_uptime();
    float cpu = get_cpu_usage();
    const char* hostname = get_hostname();

    char json_buffer[512];
    snprintf(json_buffer, sizeof(json_buffer),
             "{ \"hostname\": \"%s\", \"ram_kb\": %d, \"cpu_usage\": %.2f, \"uptime_sec\": %.2f }\n",
             hostname, ram_kb, cpu, uptime);

    send(client_socket, json_buffer, strlen(json_buffer), 0);

    close(client_socket);
    close(server_socket);

    return 0;
}

