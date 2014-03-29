#include "master-chess.h"
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE_BUFF 100
#define BEGIN_GAME 1
#define INIT_STATE 0
#define TRUE 1
#define FALSE 0

using namespace std;
using namespace gui;
using namespace chess;

int n_player, nc_player, state = INIT_STATE, start_flag = 0, screen_sent = 0;
int socket_desc, client_sock, c, *new_sock;
struct sockaddr_in server, client;

/* Manage the connection */
void *manage_connection(void *socket_desc){
	cout << "HELLO";
}

int main(int argc, char **argv){
	Interface t;
	Board b;
	
	int sock, i;
	struct sockaddr_in server;
	char message[10000] , server_reply[20000];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		cout << "Creating socket [FAIL]\n";
	}
	cout << "Creating socket [DONE]\n";
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		cout << "Connecting to server [FAIL]\n";
		return 1;
	}
	
	strcpy(message, "My Name");
	if( send(sock , message , strlen(message) , 0) < 0)
		{
			cout << "Send failed";
			return 1;
		}
		
	if( recv(sock , server_reply , 10000 , 0) < 0) {
	   	cout << "recv failed";
			return 0;
	   }
	
	cout << "Starting the game!\n";
	
	/***************************** START THE GAME HERE *****/
}
