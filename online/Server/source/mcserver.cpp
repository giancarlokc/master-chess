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

/* Iniciate TCP Server socket */
bool initServerTCP(int *socket_desc, struct sockaddr_in *server, int *c){
	*socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (*socket_desc == -1){
		cout << "Creating socket [FAIL]\n";
		return 1;
	}
	cout << "Creating socket [DONE]\n";
	
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;
	server->sin_port = htons( 8888 );
	if( bind(*socket_desc,(struct sockaddr *) server , sizeof(*server)) < 0){
		cout << "Setting up socket [FAIL]\n";
		return 1;
	}
	cout << "Setting up socket [DONE]\n";

	listen(*socket_desc , 3);
	
	*c = sizeof(struct sockaddr_in);
	
	return true;
}

int main(int argc, char **argv){
	Interface t;
	Board b;
	
	int p1_sock, p2_sock;
	int n_player = 0, nc_player, state = INIT_STATE, start_flag = 0, screen_sent = 0;
	int socket_desc, client_sock, c, *new_sock;
	struct sockaddr_in server, client;
	
	if(!initServerTCP(&socket_desc, &server, &c))
		return 1;
	
	do{
		while(n_player < 2 && (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))){
			n_player++;
			if(n_player == 1){
				p1_sock = client_sock;
			} else if(n_player == 2){
				p2_sock = client_sock;
			}
			
		}
	}while(n_player < 2);
	
	int read_size;
	char client_message[2000], message[2000];
	char p1_name[2000], p2_name[2000];
	
	// Receive first player connection
	cout << "# Received connection #\n";
	cout << "- socket: " << p1_sock << "\n";
	read_size = recv(p1_sock , client_message , 2000 , 0);
	cout << "- name: " << client_message << "\n";
	strcpy(p1_name, client_message);
	strcpy(message, "CONFIRMATION");
	if( send(p1_sock , message , strlen(message) , 0) < 0){
		cout << "Send failed";
		return 1;
	}
	cout << "\n";
	
	// Receive second player connection
	cout << "# Received connection #\n";
	cout << "- socket: " << p2_sock << "\n";
	read_size = recv(p2_sock , client_message , 2000 , 0);
	cout << "- name: " << client_message << "\n";
	strcpy(p2_name, client_message);
	strcpy(message, "CONFIRMATION");
	if( send(p2_sock , message , strlen(message) , 0) < 0){
		cout << "Send failed";
		return 1;
	}
	cout << "\n";
	
	/***************************** START THE GAME HERE *****/
}
