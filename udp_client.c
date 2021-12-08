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
#include <arpa.inet.h>

//Main
int main(){
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
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

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

	//Close the Socket
	close(sock);
	return 0;
}//End main
