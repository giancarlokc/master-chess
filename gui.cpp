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

#include "gui.h"
#include <ncurses.h>
#include <iostream>

using namespace std;

namespace gui{
	void Interface::showBoard(Board b){
		char c = 'A';
	
		cout << "       1  2  3  4  5  6  7  8 \n";
		cout << "       !  !  !  !  !  !  !  !\n";
		for(int i=0;i<8;i++){
			cout << "  " << c++ << "---|";
			for(int j=0;j<8;j++){
				if(b.position[i][j].empty){
					cout << "  |";
				} else {
					if(b.position[i][j].color == BLACK){
						cout << "B";
					} else {
						cout << "W";
					}
					
					if(b.position[i][j].piece == KING){
						cout << "K|";
					} else if(b.position[i][j].piece == QUEEN){
						cout << "Q|";
					} else if(b.position[i][j].piece == BISHOP){
						cout << "B|";
					} else if(b.position[i][j].piece == HORSE){
						cout << "H|";
					} else if(b.position[i][j].piece == TOWER){
						cout << "T|";
					} else if(b.position[i][j].piece == PAWN){
						cout << "P|";
					}
				}
			}
			cout << "\n";
		}
	}
	
	void Interface::possibleMove(Board b, int lin, int col, int cursor_lin, int cursor_col){
		if(b.position[lin][col].piece == PAWN){
			if(b.position[lin][col].color == BLACK){
				attron(COLOR_PAIR(5));
				if(b.position[lin+1][col].empty){
					mvprintw(4 + lin + 1, 7 + col*4, " ");
					mvprintw(4 + lin + 1, 9 + col*4, " ");
				}
				if(!b.position[lin+1][col+1].empty && b.position[lin+1][col+1].color == WHITE){
					mvprintw(4 + lin + 1, 7 + (col+1)*4, " ");
					mvprintw(4 + lin + 1, 9 + (col+1)*4, " ");
				}
				if(!b.position[lin+1][col-1].empty && b.position[lin+1][col-1].color == WHITE){
					mvprintw(4 + lin + 1, 7 + (col-1)*4, " ");
					mvprintw(4 + lin + 1, 9 + (col-1)*4, " ");					
				}
			} else {
				attron(COLOR_PAIR(5));
				if(b.position[lin-1][col].empty){
					mvprintw(4 + lin - 1, 7 + col*4, " ");
					mvprintw(4 + lin - 1, 9 + col*4, " ");
				}
				if(!b.position[lin-1][col+1].empty && b.position[lin-1][col+1].color == BLACK){
					mvprintw(4 + lin - 1, 7 + (col+1)*4, " ");
					mvprintw(4 + lin - 1, 9 + (col+1)*4, " ");
				}
				if(!b.position[lin-1][col-1].empty && b.position[lin-1][col-1].color == BLACK){
					mvprintw(4 + lin - 1, 7 + (col-1)*4, " ");
					mvprintw(4 + lin - 1, 9 + (col-1)*4, " ");
				}
			}
		} else if(b.position[lin][col].piece == HORSE){
			if(b.position[lin][col].color == BLACK){
				attron(COLOR_PAIR(5));
				if((b.position[lin+2][col+1].empty || b.position[lin+2][col+1].color == WHITE) && lin+2 < 8 && col+1 < 8){
					mvprintw(4 + lin + 2, 7 + (col+1)*4, " ");
					mvprintw(4 + lin + 2, 9 + (col+1)*4, " ");
				}
				if((b.position[lin+2][col-1].empty || b.position[lin+2][col-1].color == WHITE) && lin+2 < 8 && col-1 >= 0){
					mvprintw(4 + lin + 2, 7 + (col-1)*4, " ");
					mvprintw(4 + lin + 2, 9 + (col-1)*4, " ");
				}
				if((b.position[lin-2][col+1].empty || b.position[lin-2][col+1].color == WHITE) && lin-2 >= 0 && col+1 < 8){
					mvprintw(4 + lin - 2, 7 + (col+1)*4, " ");
					mvprintw(4 + lin - 2, 9 + (col+1)*4, " ");
				}
				if((b.position[lin-2][col-1].empty || b.position[lin-2][col-1].color == WHITE) && lin-2 >= 0 && col-1 >= 0){
					mvprintw(4 + lin - 2, 7 + (col-1)*4, " ");
					mvprintw(4 + lin - 2, 9 + (col-1)*4, " ");
				}
				if((b.position[lin+1][col+2].empty || b.position[lin+1][col+2].color == WHITE) && lin+1 < 8 && col+2 < 8){
					mvprintw(4 + lin + 1, 7 + (col+2)*4, " ");
					mvprintw(4 + lin + 1, 9 + (col+2)*4, " ");
				}
				if((b.position[lin+1][col-2].empty || b.position[lin+1][col-2].color == WHITE) && lin+1 < 8 && col-2 >= 0){
					mvprintw(4 + lin + 1, 7 + (col-2)*4, " ");
					mvprintw(4 + lin + 1, 9 + (col-2)*4, " ");
				}
				if((b.position[lin-1][col+2].empty || b.position[lin-1][col+2].color == WHITE) && lin-1 >= 0 && col+2 < 8){
					mvprintw(4 + lin - 1, 7 + (col+2)*4, " ");
					mvprintw(4 + lin - 1, 9 + (col+2)*4, " ");
				}
				if((b.position[lin-1][col-2].empty || b.position[lin-1][col-2].color == WHITE) && lin-1 >= 0 && col-2 >= 0){
					mvprintw(4 + lin - 1, 7 + (col-2)*4, " ");
					mvprintw(4 + lin - 1, 9 + (col-2)*4, " ");
				}
			} else {
				attron(COLOR_PAIR(5));
				if((b.position[lin+2][col+1].empty || b.position[lin+2][col+1].color == BLACK) && lin+2 < 8 && col+1 < 8){
					mvprintw(4 + lin + 2, 7 + (col+1)*4, " ");
					mvprintw(4 + lin + 2, 9 + (col+1)*4, " ");
				}
				if((b.position[lin+2][col-1].empty || b.position[lin+2][col-1].color == BLACK) && lin+2 < 8 && col-1 >= 0){
					mvprintw(4 + lin + 2, 7 + (col-1)*4, " ");
					mvprintw(4 + lin + 2, 9 + (col-1)*4, " ");
				}
				if((b.position[lin-2][col+1].empty || b.position[lin-2][col+1].color == BLACK) && lin-2 >= 0 && col+1 < 8){
					mvprintw(4 + lin - 2, 7 + (col+1)*4, " ");
					mvprintw(4 + lin - 2, 9 + (col+1)*4, " ");
				}
				if((b.position[lin-2][col-1].empty || b.position[lin-2][col-1].color == BLACK) && lin-2 >= 0 && col-1 >= 0){
					mvprintw(4 + lin - 2, 7 + (col-1)*4, " ");
					mvprintw(4 + lin - 2, 9 + (col-1)*4, " ");
				}
				if((b.position[lin+1][col+2].empty || b.position[lin+1][col+2].color == BLACK) && lin+1 < 8 && col+2 < 8){
					mvprintw(4 + lin + 1, 7 + (col+2)*4, " ");
					mvprintw(4 + lin + 1, 9 + (col+2)*4, " ");
				}
				if((b.position[lin+1][col-2].empty || b.position[lin+1][col-2].color == BLACK) && lin+1 < 8 && col-2 >= 0){
					mvprintw(4 + lin + 1, 7 + (col-2)*4, " ");
					mvprintw(4 + lin + 1, 9 + (col-2)*4, " ");
				}
				if((b.position[lin-1][col+2].empty || b.position[lin-1][col+2].color == BLACK) && lin-1 >= 0 && col+2 < 8){
					mvprintw(4 + lin - 1, 7 + (col+2)*4, " ");
					mvprintw(4 + lin - 1, 9 + (col+2)*4, " ");
				}
				if((b.position[lin-1][col-2].empty || b.position[lin-1][col-2].color == BLACK) && lin-1 >= 0 && col-2 >= 0){
					mvprintw(4 + lin - 1, 7 + (col-2)*4, " ");
					mvprintw(4 + lin - 1, 9 + (col-2)*4, " ");
				}
			}
		} else if(b.position[lin][col].piece == TOWER){
			int i;
			attron(COLOR_PAIR(5));
			
			for(i=col+1;i<8;i++){
				if(!b.position[lin][i].empty)
					break;
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			if(i<8 && b.position[lin][i].color != b.position[lin][col].color){
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			
			for(i=col-1;i>=0;i--){
				if(!b.position[lin][i].empty)
					break;
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			if(i>=0 && b.position[lin][i].color != b.position[lin][col].color){
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			
			for(i=lin+1;i<8;i++){
				if(!b.position[i][col].empty)
					break;
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
			if(i<8 && b.position[i][col].color != b.position[lin][col].color){
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
			
			for(i=lin-1;i>=0;i--){
				if(!b.position[i][col].empty)
					break;
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
			if(i>=0 && b.position[i][col].color != b.position[lin][col].color){
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
		} else if(b.position[lin][col].piece == BISHOP){
			int i;
			attron(COLOR_PAIR(5));
			
			for(i=1;i<8;i++){
				if(lin+i > 7 || col+i > 7)
					break;
				if(!b.position[lin+i][col+i].empty)
					break;
				mvprintw(4 + lin+i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col+i)*4, " ");
			}
			if((lin+i < 8 && col+i < 8) && b.position[lin+i][col+i].color != b.position[lin][col].color){
				mvprintw(4 + lin+i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col+i)*4, " ");
			}
			
			for(i=1;i<8;i++){
				if(lin+i > 7 || col-i < 0)
					break;
				if(!b.position[lin+i][col-i].empty)
					break;
				mvprintw(4 + lin+i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col-i)*4, " ");
			}
			if((lin+i < 8 && col-i >= 0) && b.position[lin+i][col-i].color != b.position[lin][col].color){
				mvprintw(4 + lin+i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col-i)*4, " ");
			}
			
			for(i=1;i<8;i++){
				if(lin-i < 0 || col+i > 7)
					break;
				if(!b.position[lin-i][col+i].empty)
					break;
				mvprintw(4 + lin-i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col+i)*4, " ");
			}
			if((lin-i >= 0 && col+i < 8) && b.position[lin-i][col+i].color != b.position[lin][col].color){
				mvprintw(4 + lin-i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col+i)*4, " ");
			}
			
			for(i=1;i<8;i++){
				if(lin-i < 0 || col-i < 0)
					break;
				if(!b.position[lin-i][col-i].empty)
					break;
				mvprintw(4 + lin-i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col-i)*4, " ");
			}
			if((lin-i >= 0 && col-i >= 0) && b.position[lin-i][col-i].color != b.position[lin][col].color){
				mvprintw(4 + lin-i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col-i)*4, " ");
			}
			
			
		} else if(b.position[lin][col].piece == QUEEN){
			int i;
			attron(COLOR_PAIR(5));
			
			for(i=col+1;i<8;i++){
				if(!b.position[lin][i].empty)
					break;
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			if(i<8 && b.position[lin][i].color != b.position[lin][col].color){
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			
			for(i=col-1;i>=0;i--){
				if(!b.position[lin][i].empty)
					break;
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			if(i>=0 && b.position[lin][i].color != b.position[lin][col].color){
				mvprintw(4 + lin, 7 + (i)*4, " ");
				mvprintw(4 + lin, 9 + (i)*4, " ");
			}
			
			for(i=lin+1;i<8;i++){
				if(!b.position[i][col].empty)
					break;
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
			if(i<8 && b.position[i][col].color != b.position[lin][col].color){
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
			
			for(i=lin-1;i>=0;i--){
				if(!b.position[i][col].empty)
					break;
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
			if(i>=0 && b.position[i][col].color != b.position[lin][col].color){
				mvprintw(4 + i, 7 + (col)*4, " ");
				mvprintw(4 + i, 9 + (col)*4, " ");
			}
			
			for(i=1;i<8;i++){
				if(lin+i > 7 || col+i > 7)
					break;
				if(!b.position[lin+i][col+i].empty)
					break;
				mvprintw(4 + lin+i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col+i)*4, " ");
			}
			if((lin+i < 8 && col+i < 8) && b.position[lin+i][col+i].color != b.position[lin][col].color){
				mvprintw(4 + lin+i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col+i)*4, " ");
			}
			
			for(i=1;i<8;i++){
				if(lin+i > 7 || col-i < 0)
					break;
				if(!b.position[lin+i][col-i].empty)
					break;
				mvprintw(4 + lin+i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col-i)*4, " ");
			}
			if((lin+i < 8 && col-i >= 0) && b.position[lin+i][col-i].color != b.position[lin][col].color){
				mvprintw(4 + lin+i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin+i, 9 + (col-i)*4, " ");
			}
			
			for(i=1;i<8;i++){
				if(lin-i < 0 || col+i > 7)
					break;
				if(!b.position[lin-i][col+i].empty)
					break;
				mvprintw(4 + lin-i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col+i)*4, " ");
			}
			if((lin-i >= 0 && col+i < 8) && b.position[lin-i][col+i].color != b.position[lin][col].color){
				mvprintw(4 + lin-i, 7 + (col+i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col+i)*4, " ");
			}
			
			for(i=1;i<8;i++){
				if(lin-i < 0 || col-i < 0)
					break;
				if(!b.position[lin-i][col-i].empty)
					break;
				mvprintw(4 + lin-i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col-i)*4, " ");
			}
			if((lin-i >= 0 && col-i >= 0) && b.position[lin-i][col-i].color != b.position[lin][col].color){
				mvprintw(4 + lin-i, 7 + (col-i)*4, " ");
				mvprintw(4 + lin-i, 9 + (col-i)*4, " ");
			}
		}
		
		attron(COLOR_PAIR(1));
		return;
	}
	
	void Interface::startBoard_nc(Board b){
		initscr();
		start_color();
		noecho();
		cbreak();
		
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_WHITE, COLOR_RED);
		init_pair(3, COLOR_WHITE, COLOR_BLUE);
		init_pair(4, COLOR_BLACK, COLOR_WHITE);
		init_pair(5, COLOR_WHITE, COLOR_GREEN);
	}
	
	void Interface::endBoard_nc(Board b){
		endwin();
	}
	
	void Interface::showBoard_nc(Board b, int *cursor_x, int *cursor_y, int *cursor_x_to, int *cursor_y_to){

		bool chosedPiece = false;
		bool chosedMove = false;
		int c;
	
		while(!chosedPiece || !chosedMove){
			// Clear screen
			clear();
		
			attron(COLOR_PAIR(1));
			printw ("  ############### Computer ################\n\n");
			printw ("        1   2   3   4   5   6   7   8 \n");
			printw ("        !   !   !   !   !   !   !   !\n");
			c = 'A';
			for(int i=0;i<8;i++){
				attron(COLOR_PAIR(1));
				printw ("  %c --|", c);
				for(int j=0;j<8;j++){
					if(b.position[i][j].empty){
						if(chosedPiece == false){
							if(j == *cursor_x && i == *cursor_y){
								attron(COLOR_PAIR(2));
								printw ("   ");
							} else {
								attron(COLOR_PAIR(1));
								printw ("   ");
							}
						} else {
							if(j == *cursor_x_to && i == *cursor_y_to){
								attron(COLOR_PAIR(2));	
								printw ("   ");
							} else {
								attron(COLOR_PAIR(1));	
								printw ("   ");
							}
						}
						attron(COLOR_PAIR(1));
						printw("|");
					} else {
				
						if(b.position[i][j].color == BLACK){
							attron(COLOR_PAIR(4));
						} else {
							attron(COLOR_PAIR(3));
						}
						if(chosedPiece == false){
							if(j == *cursor_x && i == *cursor_y)
								attron(COLOR_PAIR(2));
						} else {
							if(j == *cursor_x && i == *cursor_y)
								attron(COLOR_PAIR(2));
							if(j == *cursor_x_to && i == *cursor_y_to)
								attron(COLOR_PAIR(2));
						}
				
						printw (" ");
						if(b.position[i][j].piece == KING){
							printw ("K ");
						} else if(b.position[i][j].piece == QUEEN){
							printw ("Q ");
						} else if(b.position[i][j].piece == BISHOP){
							printw ("B ");
						} else if(b.position[i][j].piece == HORSE){
							printw ("H ");
						} else if(b.position[i][j].piece == TOWER){
							printw ("T ");
						} else if(b.position[i][j].piece == PAWN){
							printw ("P ");
						}
						attron(COLOR_PAIR(1));
						printw("|");
					}
				}
				attron(COLOR_PAIR(1));
				printw ("-- %c", c);
				c++;
				printw ("\n");
			}
			printw ("        !   !   !   !   !   !   !   !\n");
			printw ("        1   2   3   4   5   6   7   8 \n");
			printw (" \n  ############## Player (You) #############\n\n");
			
			if(!chosedPiece == true){
				mvprintw(0, 60, "Piece not selected!");
			} else {
				mvprintw(0, 60, "Piece selected!");
				possibleMove(b, *cursor_y, *cursor_x, *cursor_y_to, *cursor_x_to);
			}
			
			if(!chosedMove == true){
				mvprintw(1, 60, "Move not selected!");
			} else {
				mvprintw(1, 60, "Move selected!");
			}
			
			refresh();
			int cmd = getch();
//			printw("%d", cmd);
//			getch();
			
			if(chosedPiece == false){
				// UP
				if(cmd == 119){
					if(*cursor_y != 0) *cursor_y -= 1;
				}
				// DOWN
				if(cmd == 115){
					if(*cursor_y != 7) *cursor_y += 1;
				}
				// LEFT
				if(cmd == 97){
					if(*cursor_x != 0) *cursor_x -= 1;
				}
				// RIGHT
				if(cmd == 100){
					if(*cursor_x != 7) *cursor_x += 1;
				}
				if(cmd == 10){
					if(!b.position[*cursor_y][*cursor_x].empty){
						chosedPiece = true;
						*cursor_x_to = *cursor_x;
						*cursor_y_to = *cursor_y;
					}
				}
			} else {
				if(cmd == 119){
					if(*cursor_y_to != 0) *cursor_y_to -= 1;
				}
				// DOWN
				if(cmd == 115){
					if(*cursor_y_to != 7) *cursor_y_to += 1;
				}
				// LEFT
				if(cmd == 97){
					if(*cursor_x_to != 0) *cursor_x_to -= 1;
				}
				// RIGHT
				if(cmd == 100){
					if(*cursor_x_to != 7) *cursor_x_to += 1;
				}
				if(cmd == 10){
					chosedMove = true;
				}
			}
		}
		
		return;
	}
}
