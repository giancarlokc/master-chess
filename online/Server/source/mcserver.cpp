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

void initServerMesg(void){
	cout << "Master-Chess Online Server\n";
	cout << "- Using standard socket 8888.\n";
}

void setupServerMesg(void){
	cout << "\n# Server Setup #\n";
}

void recvConnMesg(void){
	cout << "\n# Waiting for players #\n\n";
}

void initRoomMesg(void){
	cout << "\n# Starting Game #\n\n";
}

/* Iniciate TCP Server socket */
bool initServerTCP(int *socket_desc, struct sockaddr_in *server, int *c){
	*socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (*socket_desc == -1){
		cout << "Creating socket [FAIL]\n";
		return false;
	}
	cout << "Creating socket [DONE]\n";
	
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = htonl(INADDR_ANY);
	server->sin_port = htons( 8888 );
	if( bind(*socket_desc,(struct sockaddr *) server , sizeof(*server)) < 0){
		cout << "Setting up socket [FAIL]\n";
		return false;
	}
	cout << "Setting up socket [DONE]\n";

	listen(*socket_desc , 10);
	
	*c = sizeof(struct sockaddr_in);
	
	return true;
}

/* Sent the current board configuration to a player */
bool sendBoard(Board b, int sock){
	char message[2000];
	int mesg_index = 0;

	memset(message, 0, 2000);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			message[mesg_index] = (char) b.position[i][j].color;
			message[mesg_index+1] = (char) b.position[i][j].piece;
			message[mesg_index+2] = (char) b.position[i][j].empty;
			mesg_index+=3;
		}
	}
	
	write(sock, message, 64*3+1);
}

bool receiveMove(Board *b, int sock){
	int read_size;
	char client_message[2000];
	
	memset(client_message, 0, sizeof(client_message));
	if(read_size = read(sock , client_message , sizeof(client_message)) < 0){
		cout << "Read error\n";
		return false;
	} else {
		cout << "Received move:\n";
		cout << (int) client_message[0] << "\n";
		cout << (int) client_message[1] << "\n";
		cout << (int) client_message[2] << "\n";
		cout << (int) client_message[3] << "\n";
		int a, bb, a_f, b_f;
		
		a = (int) client_message[2];
		a_f = (int) client_message[3];
		
		bb = (int) client_message[0];
		b_f = (int) client_message[1];
	
		if(!b->position[a][bb].empty && b->position[a][bb].piece == PAWN){
			if(!b->movePawn(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b->position[a][bb].empty && b->position[a][bb].piece == HORSE){
			if(!b->moveHorse(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b->position[a][bb].empty && b->position[a][bb].piece == TOWER){
			if(!b->moveTower(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b->position[a][bb].empty && b->position[a][bb].piece == BISHOP){
			if(!b->moveBishop(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b->position[a][bb].empty && b->position[a][bb].piece == QUEEN){
			if(!b->moveQueen(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		if(!b->position[a][bb].empty && b->position[a][bb].piece == KING){
			if(!b->moveKing(a, bb, a_f, b_f))
				cout << "Invalid Move!";
		}
		
		return true;
	}
}

int main(int argc, char **argv){
	
	int p1_sock, p2_sock;
	int n_player = 0, nc_player, state = INIT_STATE, start_flag = 0, screen_sent = 0;
	int socket_desc, client_sock, c, *new_sock;
	struct sockaddr_in server, client;
	
	int read_size;
	char client_message[2000], message[2000];
	char p1_name[2000], p2_name[2000];
	
	initServerMesg();
	
	setupServerMesg();
	if(!initServerTCP(&socket_desc, &server, &c))
		return 1;
	
	recvConnMesg();
	
	while(true){
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
			n_player++;
			if(n_player == 1){
				p1_sock = client_sock;
				
				// Receive first player connection
				cout << "   Received connection\n";
				cout << "   Socket: " << p1_sock << "\n";
				memset(client_message, '\0', 2000);
				if(read_size = read(p1_sock , client_message , sizeof(client_message)) < 0){
					cout << "   Read error\n";
					return 1;
				} else {
					cout << "   Read: " << client_message << "\n";
				}
				cout << "   Name: " << client_message << "\n";
				strcpy(p1_name, client_message);
			} else if(n_player == 2){
				p2_sock = client_sock;
				
				// Receive first player connection
				cout << "   Received connection\n";
				cout << "   Socket: " << p2_sock << "\n";
				memset(client_message, '\0', 2000);
				if(read_size = read(p2_sock , client_message , sizeof(client_message)) < 0){
					cout << "   Read error\n";
					return 1;
				} else {
					cout << "   Read: " << client_message << "\n";
				}
				cout << "   Name: " << client_message << "\n";
				strcpy(p2_name, client_message);
				break;
		}
		
	}
	
	/***************************** START THE GAME HERE *****/
	/* Player 1 - p1_sock
	/* Player 2 - p2_sock
	/*******************************************************/
	
	initRoomMesg();
	Board b;
	
		
	b.reset();
	b.movePawn(1,0,2,0);
	
	do{
		/* Send board to player 1 */
		cout << "Sending board to P1...\n";
		sendBoard(b, p1_sock);
		cout << "[OK]\n";
		
		/* Get player 1 move */
		cout << "Getting P1 move...\n";
		receiveMove(&b, p1_sock);
		cout << "[OK]\n";
		
		/* Send board to player 2 */
		cout << "Sending board to P2...\n";
		sendBoard(b, p2_sock);
		cout << "[OK]\n";
		
		/* Get player 2 move */
		cout << "Getting P2 move...\n";
		receiveMove(&b, p2_sock);
		cout << "[OK]\n";

	}while(!b.checkMate(WHITE) && !b.checkMate(BLACK)); 
	
}
