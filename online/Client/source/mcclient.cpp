// Copyright 2013 Giancarlo Klemm Camilo

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// ********************************************************************* //

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

bool receiveBoard(Board *b, char *message){
	int mesg_index = 0;

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			b->position[i][j].color = (int) message[mesg_index];
			b->position[i][j].piece = (int) message[mesg_index+1];
			b->position[i][j].empty = (int) message[mesg_index+2];
			mesg_index+=3;
		}
	}
	
	return true;
}

int main(int argc, char **argv){

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
	
	strcpy(message, argv[1]);
	write(sock , message , strlen(message));
	
	/***************************** START THE GAME HERE *****/
	int read_size;
	Board b;
	Interface t;
	
	b.reset();
	t.startBoard_nc(b);
	int cursor_x = 0, cursor_y = 0, cursor_x_to = 0, cursor_y_to = 0;
	
	do{
		int t_x = -1;
		int t_x_to = -1;
		int t_y = -1;
		int t_y_to = -1;
		t.showBoard_nc_onlyshow(b, &t_x, &t_y, &t_x_to, &t_y_to);
	
		/* Receive board */
		memset(server_reply, 0, sizeof(server_reply));
		if(read_size = read(sock, server_reply, sizeof(server_reply)-1) < 0){
			cout << "Read error\n";
			return 1;
		} else {
			receiveBoard(&b, server_reply);
		}
		
		cursor_x = 0;
		cursor_x_to = 0;
		cursor_y = 0;
		cursor_y_to = 0;
		/* Show board and get move */
		t.showBoard_nc(b, &cursor_x, &cursor_y, &cursor_x_to, &cursor_y_to);
		
		int a, bb, a_f, b_f;
		
		a = cursor_y;
		a_f = cursor_y_to;
		
		bb = cursor_x;
		b_f = cursor_x_to;
		
//		cursor_x = cursor_x_to;
//		cursor_y = cursor_y_to;
	
		if(!b.position[a][bb].empty && b.position[a][bb].piece == PAWN){
			if(!b.movePawn(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b.position[a][bb].empty && b.position[a][bb].piece == HORSE){
			if(!b.moveHorse(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b.position[a][bb].empty && b.position[a][bb].piece == TOWER){
			if(!b.moveTower(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b.position[a][bb].empty && b.position[a][bb].piece == BISHOP){
			if(!b.moveBishop(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b.position[a][bb].empty && b.position[a][bb].piece == QUEEN){
			if(!b.moveQueen(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b.position[a][bb].empty && b.position[a][bb].piece == KING){
			if(!b.moveKing(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		t_x = -1;
		t_x_to = -1;
		t_y = -1;
		t_y_to = -1;
		t.showBoard_nc_onlyshow(b, &t_x, &t_y, &t_x_to, &t_y_to);
		
		/* Send move */
		memset(message, 0, sizeof(message));
		message[0] = (char) cursor_x;
		message[1] = (char) cursor_x_to;
		message[2] = (char) cursor_y;
		message[3] = (char) cursor_y_to;
		write(sock, message, 4);
		
		
		
		
		
	}while(strcmp(server_reply, "checkmate") != 0);
	
	cout << "CHECKMATE\n";
	t.endBoard_nc(b);
}
