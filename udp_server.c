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
	struct sockaddr_in server_address;
	server_address.sin_family      = AF_INET;       // Type of Address
	server_address.sin_port        = htons(port);   // Convert Port #
	server_address.sin_addr.s_addr = INADDR_ANY;	// Send Address

	//Bind Socket
	int bind_socket = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));   // Bind Socket
	if(bind_socket == -1){                                                                               // Check bad Bind
		perror("Bind Failed");                                                                       // Send Error
		close(server_socket);                                                                        // Close Server
		exit(EXIT_FAILURE);                                                                          // Exit Program
	}else printf("Bind Successfull!\n");                                                                 // Print Success
	printf("Listening for Clients...\n");                                                                // Print listening

	//Receive file name from client 
	char buffer[50] = {0};
    	socklen_t len = 0;
    	int n = recvfrom(server_socket, (char *)buffer, 50, MSG_WAITALL, 0, &len);
    
    	// Try to open file
    	FILE* file = fopen(buffer, "r");
    
    	//Print file name
    	buffer[n] = '\n';
    	printf("File Name Received: %s", buffer);
    
    	//Did file open succesfully?
    	if (file == NULL)
        	printf("Failed to open file!\n");
    	else
        	perror("File opened successfully!");
    
    	//Send File
    	int EndOfFile = 0; //flag to see if EOF has been reached
    	int sent;
    	while (1) {
        	//process
        	for (int i = 0; i < 50; i++){                        //BUFFER 50
            		buffer[i] = fgetc(file);
            		if (buffer[i] == EOF) EndOfFile = 1;
        	}
        
        	
        	/*while (1) { //Loop till client receives file.
        		//send*/
        		sent = sendto(server_socket, (const char *)buffer, strlen(buffer), 0, (struct sockaddr*) &server_address, sizeof(server_address));
        		/*
        		//wait for confirmation
        		socklen_t len = 0;
            		n = recvfrom(server_socket, (char *)buffer, 50, MSG_WAITALL, 0, &len);
         		//FIXME -- check that the ACK is correct.
        	}*/
            
        //End While
        
        //Exit loop if EOF
        if (EndOfFile) break;
        
    	}//while
    
    	// Close File
    	if (file != NULL)
        	fclose(file);

	/*
	//Receive Message from Client
	char buffer[50] = {0};
	socklen_t len = 0;                                                                 // Set data length 
	int receive = recvfrom(server_socket, (char *)buffer, 50, MSG_WAITALL, 0, &len);   // Get data
	buffer[receive] = '\n';                                                            // Add space to message
	printf("Message from Client: %s", buffer);                                         // Print Msg

	//Send Message to Client
	char * server_message = "You reach the server!";                                                             //Data to send
	int sent = sendto(server_socket, (const char *)server_message, strlen(server_message), 0, (const struct sockaddr*) &server_address, sizeof(server_address));   //Send MSG
	if(sent != -1)printf("Message Sent!\n");                                                                          //Check sent
	else perror("Message failed to send");               

	*/
	//Close Socket
	close(server_socket);

	
	return 0;
}//End main
