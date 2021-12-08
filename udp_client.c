/**
 * Program Assignment 2 Client
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
	//argv[1] = IP or Hostname
	//argv[2] = Port #
	//argv[3] = File Name
	
	//Set Port
	int port = 9002;                //Default Port
	if(argc == 4) port = argv[2];   //Set Port

	//Message from Client
	char * msg = "Hello From Client";

	//Create Socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_DGRAM, 0);

	//Check to see if socket is created.
	if(network_socket == -1){
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}//End if

	//Specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family      = AF_INET;       //Type of Address
	server_address.sin_port        = htons(port);   //Convert Port #
	server_address.sin_addr.s_addr = INADDR_ANY;    //Send Address

	int len = sendto(network_socket, (const char *)msg, strlen(msg), 0, (const struct sockaddr *)&server_address, sizeof(server_address));
	if(len == -1){
		perror("Fail to send");
	}//end if

	/*
	//Create Connection
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	//Check for errors with the connection
	if(connection_status == -1){
		perror("Failed to creat connection to the remote socket");
		exit(EXIT_FAILURE);
	}//End if

	//Recieve Data from Server
	char server_response[256];                                            //Store Server Data
	recv(network_socket, &server_response, sizeof(server_response), 0);   //Recieve Data
	printf("The server sent the data: %s", server_response);              //Print Data

	//Send Data to Server
	//int 

	*/
	//Close the Socket
	close(network_socket);
	return 0;
}//End main
