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
int main(int argc, char **argv[]){
	//Expected Argument input
	//argv[0] = name of program
	//argv[1] = IP or Hostname
	//argv[2] = Port #
	//argv[3] = File Name
	
	//Set Port
	int port = 9002;                                          // Default Port
	if(argc == 4) port = strtol((char *)argv[2], NULL, 10);   // Set Port
	printf("Port: %d\n", port);                               // Print Port

	//Create Socket
	int network_socket;                                // Create boolean
	network_socket = socket(AF_INET, SOCK_DGRAM, 0);   // Create Socket
	if(network_socket == -1){                          // Check Socket
		perror("Failed to create socket");         // Print Failure
		exit(EXIT_FAILURE);                        // End Program
	}else printf("Socket Successfully Created!\n");    // Print Success
	//End if

	//Specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family      = AF_INET;       // Type of Address
	server_address.sin_port        = htons(port);   // Convert Port #
	server_address.sin_addr.s_addr = INADDR_ANY;    // Send Address

	
	//Send File Name to Server
	printf("File Name: %s\n",argv[3]);                                                                                                             // Print File Name
	int message_sent;                                                                                                                              // Create boolean
	message_sent = sendto(network_socket, (char*)argv[3], strlen((char*)argv[3]), 0, (struct sockaddr*)&server_address, sizeof(server_address));   // Send data
	if(message_sent != -1) printf("Message sent to Server!");                                                                                      // Print Success
	else perror("Fail to send");                                                                                                                   // Print Failure
 	
	
	//Receive Message from Server
	char buffer[200];                                                                    // Create Buffer
	socklen_t len = 0;                                                                   // Create length
        int receive = recvfrom(network_socket, (char *)buffer, 200, MSG_WAITALL, 0, &len);   // Receive Data 
	if(receive == -1) perror("Fail to receive package");	                             // Print Error
	printf("Message:\n%s\n", buffer);                                                      // Print Message

	//Create File
	FILE *file;
	file = fopen((char *)argv[3], "w");

	//Write the File
	//fputs((char *)buffer, file);
	for(int i = 0; i < sizeof(buffer); i++){
		if(buffer[i] == EOF) break;
		fputc(buffer[i], file);
	}//End for

	//Close File
	fclose(file);
	
	//Close the Socket
	close(network_socket);
	return 0;
}//End main
