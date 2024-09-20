/***************************************************************************************************
 *Name: 34b.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a concurrent server.
                b. use pthread_create
 *Date: 20th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void* handle_client(void* client_socket) {
    int sock = *(int*)client_socket;
    char buffer[BUFFER_SIZE] = {0};

    // Read data from the client
    int valread = read(sock, buffer, BUFFER_SIZE);
    printf("Message from client: %s\n", buffer);

    // Send a response back to the client
    const char *response = "Message received";
    send(sock, response, strlen(response), 0);
    
    // Close the client socket
    close(sock);
    free(client_socket);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set the address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Accept incoming connection
        int* client_socket = malloc(sizeof(int));
        if ((*client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            free(client_socket);
            continue; // Continue to accept other connections
        }

        // Create a new thread for each client
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_socket) != 0) {
            perror("Thread creation failed");
            close(*client_socket);
            free(client_socket);
            continue;
        }

        // Detach the thread so it can clean up after itself
        pthread_detach(thread_id);
    }

    // Close the server socket (unreachable in this example)
    close(server_fd);
    return 0;
}

//execute this server program first, then use netcat to connect to the server
/******************************************OUTPUT************************************************/

/*******************SERVER**********************/
/*
Server is listening on port 8080...
Message from client: hey there!
*/
/*******************CLIENT*********************/
/*
aishjp@Aish-Linux:~/my-repo/Hands-on_List_2$ nc localhost 8080
hey there!    
Message received
*/
