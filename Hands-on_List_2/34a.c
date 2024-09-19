/***************************************************************************************************
 *Name: 34a.c
 *Author: Aishwarya J Panampilly
 *Reg.No: MT2024011
 *Description : Write a program to create a concurrent server.
                a. use fork
 *Date: 17th September, 2024
***************************************************************************************************/

/******************************************SOLUTION************************************************/
//concurrent server handles multiple client requests simultaneously
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
 
#define PORT 8080
#define BUFFER_SIZE 1024

void client_interact(int client_socket) 
{
  char buffer[BUFFER_SIZE];
  int bytes_read;
  
  // reading data from the client 
  bytes_read = read(client_socket,buffer,sizeof(buffer)-1);
  if (bytes_read < 0) {
    perror("Read error!");
    close(client_socket);
    exit(EXIT_FAILURE);
  }
  
  //read doesn't have null terminate so manually doing that
  buffer[bytes_read] = '\0';
  printf("Received Data: %s\n",buffer);
  
  //responding to client 
  const char* response = "Message Received";
  write(client_socket,response,strlen(response));
  close(client_socket);
}

int main()
{
  int server_socket,client_socket;
  struct sockaddr_in server_addr,client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  pid_t child_pid;
  server_socket = socket(AF_INET,SOCK_STREAM,0);
  if (server_socket < 0) {
    perror("Socket error!");
    exit(EXIT_FAILURE);
  }
  
  //setting up server address
  memset(&server_addr,0,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);
  
  //binding the socket 
  if (bind(server_socket(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
  {
    
