#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_PORT 65535

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <server_ip> <start_port> <end_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *server_ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    if (start_port <= 0 || end_port > MAX_PORT || start_port > end_port) {
        fprintf(stderr, "Invalid port range\n");
        exit(EXIT_FAILURE);
    }

    for (int port = start_port; port <= end_port; ++port) {
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1) {
            perror("Error creating socket");
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, server_ip, &(server_addr.sin_addr));

        if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
            printf("Port %d is open\n", port);
        }

        close(client_socket);
    }

    return 0;
}

