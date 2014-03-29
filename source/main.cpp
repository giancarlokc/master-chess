// Copyright 2012 Giancarlo Klemm Camilo

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

using namespace std;
using namespace gui;
using namespace chess;

int main(int argc, char **argv){
	Interface t;
	Board b;
	int cursor_x = 0, cursor_y = 0, cursor_x_to = 0, cursor_y_to = 0;
	
	b.reset();
	
	t.startBoard_nc(b);
	
	while(true){
	
	//	t.showBoard(b);
		t.showBoard_nc(b, &cursor_x, &cursor_y, &cursor_x_to, &cursor_y_to);		
	
		int a, bb, a_f, b_f;
		
		a = cursor_y;
		a_f = cursor_y_to;
		
		bb = cursor_x;
		b_f = cursor_x_to;
		
		cursor_x = cursor_x_to;
		cursor_y = cursor_y_to;
	
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
		
		
	}
	
	t.endBoard_nc(b);
}
