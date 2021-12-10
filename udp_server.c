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
	int port = 9002;                                         // Set Default Port
	if(argc == 3) port = strtol((char*)argv[2], NULL, 10);   // Set User's Port
	
	//Create Server Socket
	int server_socket = socket(AF_INET, SOCK_DGRAM, 0);   // Create Socket
	if(server_socket == -1){                              // Check bad Socket
		perror("Failed to create socket");            // Print Error
		exit(EXIT_FAILURE);                           // Exit Program
	}else printf("Socket successfully Created!\n");       // Print Success

   	//Specify the Server Address
	struct sockaddr_in server_address;                    // Create Stuct
	memset(&server_address, 0, sizeof(server_address));   // Clear Memory
	server_address.sin_family      = AF_INET;             // Type of Address
	server_address.sin_port        = htons(port);         // Convert Port #
	server_address.sin_addr.s_addr = INADDR_ANY;	      // Send Address

	//Bind Socket
	int bind_socket = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));   // Bind Socket
	if(bind_socket == -1){                                                                               // Check bad Bind
		perror("Bind Failed");                                                                       // Send Error
		close(server_socket);                                                                        // Close Server
		exit(EXIT_FAILURE);                                                                          // Exit Program
	}else printf("Bind Successfull!\n");                                                                 // Print Success
	printf("Listening for Clients...\n");                                                                // Print listening

	//Receive file name from client 
	char buffer[200] = {0};                                                                                                   // Create Buffer
	int receive;                                                                                                              //
    	socklen_t len = sizeof(server_address);                                                                                   // Set Length
    	receive = recvfrom(server_socket, (char*)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*)&server_address, &len);   // receive file
    	if(receive != 1) printf("Received message from client!\n");                                                               // Print Success
	else perror("Failed to received");                                                                                        // Print Failure

	/*** File Reader ***/
    	// Try to open file
    	FILE* file = fopen(buffer, "r");
    
    	//Print file name
    	buffer[receive] = '\n';
    	printf("File Name Received: %s", buffer);
	memset(&buffer, 0, sizeof(buffer));
    
    	//Checks if File exists.
    	if (file == NULL)
     		perror("ERROR: File does not exit.\n");
    	else
        	printf("File opened successfully!\n");
    
    	//Send File
    	int EndOfFile = 1;   // Flag to see if EOF has been reached
    	int sent;            // Flag for sendto


	//Proccess and send file
    	while (EndOfFile != -1) {
        	//Proccess the File
        	for (int i = 0; i < sizeof(buffer); i++){   // Loop through buffer
			buffer[i] = fgetc(file);            // Save string
            		if (buffer[i] == EOF){              // Check EOF (End Of File)
				buffer[i] = '\0';           // Set the End to empty
			       	EndOfFile = -1;             // Update Flag
				break;                      // Break Loop
			}//End if
        	}//End for

		//Send file to Client
        	sent = sendto(server_socket, (const char *)buffer, strlen(buffer), 0, (struct sockaddr*) &server_address, len);   // Send Packet
		if(sent != -1) printf("Sent Packet Successfull!\n");                                                              // Print Success
		else perror("Failed to send packet!\n");                                                                          // Print Failure
    	}//while
    
    	// Close File
    	fclose(file);

	//Close Socket
	close(server_socket);

	return 0;
}//End main
