/**
 * Program Assignment 2 Server
 *
 * Discription:
 * This program is the client side of the Server Client
 * program. Using UDP trasport, this program is meant
 * to send chunks of different files to the client.
 *
 * This program is made possible by these links:
 *
 **/

//Standard Library
#include <stdio.h>
#include <stdlib.h>

//Socket Function
#include <sys/types.h>
#include <sys/socket.h>

//Store Addresses Library
#include <netinet/in.h>

//Extra Libraries
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

//Main
int main(int argc, char *argv[]){
	//Expected Argument input
	//argv[0] = name of program
	//argv[1] = name of file
	//argv[2] = port #
	
	//Create port #
	

	//Data we want to send to client
	char server_message[256] = "You reach the server!";
	
	//Create Server Socket
	char buffer[50] = {0};
	int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
		
	//Check Socket
	if(server_socket == -1){
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}//End if

   	//Specify the Server Address
	struct sockaddr_in server_address;
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;	

	//Bind Socket
	int bind_socket = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	if(bind_socket == -1){
		perror("Bind Failed");
		close(server_socket);
		exit(EXIT_FAILURE);
	}//End if

	socklen_t len = 0;
	int n = recvfrom(server_socket, (char *)buffer, 50, MSG_WAITALL, 0, &len);
	buffer[n] = '\n';
	printf("Message: %s", buffer);

	
	/*
	//Listen on the socket
	int listen_socket = listen(server_socket, 5);
	if(listen_socket == -1){
		perror("Listen Failed");
		exit(EXIT_FAILURE);
	}//End if

	//Create Client Socket
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	//Send Data
	send(client_socket, server_message, sizeof(server_message), 0);*/

	//Close Socket
	close(server_socket);

	return 0;
}//End main
