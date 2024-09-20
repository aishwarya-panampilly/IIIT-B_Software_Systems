/***************************************************************************************************
 *Name: 33a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to communicate between two machines using socket
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//This is the server program 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int valread;

    while (1) {
        // Clear the buffer and read the message from the client
        memset(buffer, 0, BUFFER_SIZE);
        valread = read(client_socket, buffer, BUFFER_SIZE);
        
        if (valread <= 0) {
            printf("Client disconnected\n");
            break;
        }

        // Print the message received from the client
        printf("Client: %s\n", buffer);

        // Send a message back to the client
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin); // Get server input
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket); // Close the connection when done
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create the socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up the address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept an incoming connection
    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected...\n");

    // Handle the client communication
    handle_client(client_socket);

    close(server_fd); // Close the server socket
    return 0;
}
//this is the server terminal
/******************************************OUTPUT************************************************/
/*
Server listening on port 8080...
Client connected...
Client: Hello from client!

Server: Hello from server!
Client disconnected
*/
