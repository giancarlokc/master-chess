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

#include "chess.h"

#include <iostream>

using namespace std;

namespace chess{
	/* Reset board */
	void Board::reset(){
		/* Prepare for the pieces */
		for(int i=0;i<4;i++)
			for(int j=0;j<8;j++){
				position[i][j].empty = false;
				position[i][j].color = BLACK;
			}
		for(int i=4;i<8;i++)
			for(int j=0;j<8;j++){
				position[i][j].empty = false;
				position[i][j].color = WHITE;
			}
	
		/* Set middle of the board emptcol */
		for(int i=2;i<6;i++)
			for(int j=0;j<8;j++)
				position[i][j].empty = true;
				
		for(int i=0;i<8;i++){
			/* Place BLACK pawns */
			position[1][i].piece = PAWN;
			position[1][i].color = BLACK;
			/* Place WHITE pawns */
			position[6][i].piece = PAWN;
			position[6][i].color = WHITE;
		}
		
		position[0][0].piece = TOWER;
		position[0][7].piece = TOWER;
		position[0][1].piece = HORSE;
		position[0][6].piece = HORSE;
		position[0][2].piece = BISHOP;
		position[0][5].piece = BISHOP;
		position[0][3].piece = QUEEN;
		position[0][4].piece = KING;
		blackKing_x = 0;
		blackKing_y = 4;
		
		position[7][0].piece = TOWER;
		position[7][7].piece = TOWER;
		position[7][1].piece = HORSE;
		position[7][6].piece = HORSE;
		position[7][2].piece = BISHOP;
		position[7][5].piece = BISHOP;
		position[7][3].piece = QUEEN;
		position[7][4].piece = KING;
		whiteKing_x = 7;
		whiteKing_y = 4;
		
	}
	
	/* Move Pawn */
	bool Board::movePawn(int lin, int col, int lin_final, int col_final){
		if(lin < 0 || lin > 7 || lin_final < 0 || lin_final > 7)
			return false;
		if(col < 0 || col > 7 || col_final < 0 || col_final > 7)
			return false;
		if(position[lin][col].empty || position[lin][col].piece != PAWN)
			return false;
			
		if(position[lin][col].color == BLACK){
			if(lin_final > lin + 1 || lin_final <= lin)
				return false;
		} else {
			if(lin_final < lin -1 || lin_final >= lin)
				return false;
		}
		
		if(position[lin_final][col_final].empty){
			/* Valid Move */
			if(col == col_final){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		} else {
			/* Valid Move */
			if(col == col_final-1 || col == col_final+1){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		return false;
	}
	
	/* Move Horse */
	bool Board::moveHorse(int lin, int col, int lin_final, int col_final){
		if(lin < 0 || lin > 7 || lin_final < 0 || lin_final > 7)
			return false;
		if(col < 0 || col > 7 || col_final < 0 || col_final > 7)
			return false;
		if(position[lin][col].empty || position[lin][col].piece != HORSE)
			return false;
			
		if(lin_final == lin+1){
			if(col_final == col+2){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(col_final == col-2){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		} else if(lin_final == lin-1){
			if(col_final == col+2){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(col_final == col-2){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		} else if(lin_final == lin+2){
			if(col_final == col+1){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(col_final == col-1){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		} else if(lin_final == lin-2){
			if(col_final == col+1){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(col_final == col-1){
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		}
		return false;
	}
	
	/* Move Tower */
	bool Board::moveTower(int lin, int col, int lin_final, int col_final){
//		cout << "HELO\n\n\n\n\n";
		if(lin < 0 || lin > 7 || lin_final < 0 || lin_final > 7)
			return false;
		if(col < 0 || col > 7 || col_final < 0 || col_final > 7)
			return false;
		if(position[lin][col].empty || position[lin][col].piece != TOWER)
			return false;
			
//			cout << "HELO\n";
		if(lin_final != lin && col_final == col){
			if(lin_final > lin){
				for(int p=lin+1;p<lin_final;p++)
					if(!position[p][col].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(lin_final < lin){
				for(int p=lin-1;p>lin_final;p--)
					if(!position[p][col].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		} else if(lin_final == lin && col_final != col){
			if(col_final > col){
				for(int p=col+1;p<col_final;p++)
					if(!position[lin][p].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(col_final < col){
				for(int p=col-1;p>col_final;p--)
					if(!position[lin][p].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		}
		
		return false;
	}
	
	/* Move Bishop */
	bool Board::moveBishop(int lin, int col, int lin_final, int col_final){
		int disp_lin, disp_col;
	
//		cout << "HELO\n\n\n\n\n";
		if(lin < 0 || lin > 7 || lin_final < 0 || lin_final > 7)
			return false;
		if(col < 0 || col > 7 || col_final < 0 || col_final > 7)
			return false;
		if(position[lin][col].empty || position[lin][col].piece != BISHOP)
			return false;
			
		disp_lin = lin_final - lin;
		if(disp_lin < 0) disp_lin *= -1;
		
		disp_col = col_final - col;
		if(disp_col < 0) disp_col *= -1;
		
		if(disp_lin != disp_col)
			return false;

		if(lin_final > lin && col_final > col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin+p][col+p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		if(lin_final < lin && col_final > col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin-p][col+p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		if(lin_final > lin && col_final < col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin+p][col-p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		if(lin_final < lin && col_final < col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin-p][col-p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		return false;
	}
	
	/* Move Queen */
	bool Board::moveQueen(int lin, int col, int lin_final, int col_final){
		int disp_lin, disp_col;
	
//		cout << "HELO\n\n\n\n\n";
		if(lin < 0 || lin > 7 || lin_final < 0 || lin_final > 7)
			return false;
		if(col < 0 || col > 7 || col_final < 0 || col_final > 7)
			return false;
		if(position[lin][col].empty || position[lin][col].piece != QUEEN)
			return false;
			
		if(lin_final != lin && col_final == col){
			if(lin_final > lin){
				for(int p=lin+1;p<lin_final;p++)
					if(!position[p][col].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(lin_final < lin){
				for(int p=lin-1;p>lin_final;p--)
					if(!position[p][col].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		} else if(lin_final == lin && col_final != col){
			if(col_final > col){
				for(int p=col+1;p<col_final;p++)
					if(!position[lin][p].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			} else if(col_final < col){
				for(int p=col-1;p>col_final;p--)
					if(!position[lin][p].empty)
						return false;
				if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
					position[lin_final][col_final] = position[lin][col];
					position[lin][col].empty = true;
					return true;
				}
			}
		}
			
		disp_lin = lin_final - lin;
		if(disp_lin < 0) disp_lin *= -1;
		
		disp_col = col_final - col;
		if(disp_col < 0) disp_col *= -1;
		if(disp_lin != disp_col)
			return false;

		if(lin_final > lin && col_final > col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin+p][col+p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		if(lin_final < lin && col_final > col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin-p][col+p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		if(lin_final > lin && col_final < col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin+p][col-p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		if(lin_final < lin && col_final < col){
			for(int p=1;p<disp_lin;p++)
				if(!position[lin-p][col-p].empty)
					return false;
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				position[lin_final][col_final] = position[lin][col];
				position[lin][col].empty = true;
				return true;
			}
		}
		
		return false;
	}
	
	bool Board::safeKing(int lin, int col, int myColor){
		int i;
		
		// Check for possible HORSE threats
		if(lin+1 < 8 && col+2 < 8 && position[lin+1][col+2].piece == HORSE && position[lin+1][col+2].color != myColor && position[lin+1][col+2].empty == false){
			return false;
		} else if(lin+1 < 8 && col-2 >= 0 && position[lin+1][col-2].piece == HORSE && position[lin+1][col-2].color != myColor && position[lin+1][col-2].empty == false){
			return false;
		} else if(lin-1 >= 0 && col+2 < 8 && position[lin-1][col+2].piece == HORSE && position[lin-1][col+2].color != myColor && position[lin-1][col+2].empty == false){
			return false;
		} else if(lin-1 >= 0 && col-2 >= 0 && position[lin-1][col-2].piece == HORSE && position[lin-1][col-2].color != myColor && position[lin-1][col-2].empty == false){
			return false;
		} else if(lin+2 < 8 && col+1 < 8 && position[lin+2][col+1].piece == HORSE && position[lin+2][col+1].color != myColor && position[lin+2][col+1].empty == false){
			return false;
		} else if(lin+2 < 8 && col-1 >= 0 && position[lin+2][col-1].piece == HORSE && position[lin+2][col-1].color != myColor && position[lin+2][col-1].empty == false){
			return false;
		} else if(lin-2 >= 0 && col+1 < 8 && position[lin-2][col+1].piece == HORSE && position[lin-2][col+1].color != myColor && position[lin-2][col+1].empty == false){
			return false;
		} else if(lin-2 >= 0 && col-1 >= 0 && position[lin-2][col-1].piece == HORSE && position[lin-2][col-1].color != myColor && position[lin-2][col-1].empty == false){
			return false;
		}
		
		// Check for possible PAWN threats
		if(myColor == BLACK){
			if(lin+1 < 8 && col+1 < 8 && !position[lin+1][col+1].empty && position[lin+1][col+1].piece == PAWN && position[lin+1][col+1].color != myColor){
				return false;
			}
			if(lin+1 < 8 && col-1 >= 0 && !position[lin+1][col-1].empty && position[lin+1][col-1].piece == PAWN && position[lin+1][col+1].color != myColor){
				return false;
			}
		} else {
			if(lin-1 >= 0 && col+1 < 8 && !position[lin-1][col+1].empty && position[lin-1][col+1].piece == PAWN && position[lin-1][col+1].color != myColor){
				return false;
			}
			if(lin-1 >= 0 && col-1 >= 0 && !position[lin-1][col-1].empty && position[lin-1][col-1].piece == PAWN && position[lin-1][col+1].color != myColor){
				return false;
			}
		}
		
		// Check for HORIZONTAL and VERTICAL threats
		i=col-1;
		while(i >= 0 && position[lin][i].empty){
			i--;
		}
		if(i >= 0 && (position[lin][i].piece == QUEEN || position[lin][i].piece == TOWER || (position[lin][i].piece == KING && col-i == 1)) && position[lin][i].color != myColor)
			return false;
		
		i=col+1;
		while(i < 8 && position[lin][i].empty){
			i++;
		}
		if(i < 8 && (position[lin][i].piece == QUEEN || position[lin][i].piece == TOWER || (position[lin][i].piece == KING && col-i == -1)) && position[lin][i].color != myColor)
			return false;
			
		i=lin+1;
		while(i < 8 && position[i][col].empty){
			i++;
		}
		if(i < 8 && (position[i][col].piece == QUEEN || position[i][col].piece == TOWER || (position[i][col].piece == KING && lin-i == -1)) && position[i][col].color != myColor)
			return false;
			
		i=lin-1;
		while(i >= 0 && position[i][col].empty){
			i--;
		}
		if(i >= 0 && (position[i][col].piece == QUEEN || position[i][col].piece == TOWER || (position[i][col].piece == KING && lin-i == 1)) && position[i][col].color != myColor)
			return false;
			
		// Check for DIAGONAL threats
		i=1;
		while(col+i < 8 && lin+i < 8 && position[lin+i][col+i].empty){
			i++;
		}
		if(col+i < 8 && lin+i < 8 && (position[lin+i][col+i].piece == QUEEN || position[lin+i][col+i].piece == BISHOP || (position[lin+i][col+i].piece == KING && i == 1)) && position[lin+i][col+i].color != myColor)
			return false;
			
		i=1;
		while(col+i < 8 && lin-i >= 0 && position[lin-i][col+i].empty){
			i++;
		}
		if(col+i < 8 && lin-i >= 0 && (position[lin-i][col+i].piece == QUEEN || position[lin-i][col+i].piece == BISHOP || (position[lin-i][col+i].piece == KING && i == 1)) && position[lin-i][col+i].color != myColor)
			return false;
			
		i=1;
		while(col-i >= 0 && lin+i < 8 && position[lin+i][col-i].empty){
			i++;
		}
		if(col-i >= 0 && lin+i < 8 && (position[lin+i][col-i].piece == QUEEN || position[lin+i][col-i].piece == BISHOP || (position[lin+i][col-i].piece == KING && i == 1)) && position[lin+i][col-i].color != myColor)
			return false;
			
		i=1;
		while(col-i >= 0 && lin-i >= 0 && position[lin-i][col-i].empty){
			i++;
		}
		if(col-i >= 0 && lin-i >= 0 && (position[lin-i][col-i].piece == QUEEN || position[lin-i][col-i].piece == BISHOP || (position[lin-i][col-i].piece == KING && i == 1)) && position[lin-i][col-i].color != myColor)
			return false;
		
		return true;
	}
	
	/* Move King */
	bool Board::moveKing(int lin, int col, int lin_final, int col_final){
		if(lin < 0 || lin > 7 || lin_final < 0 || lin_final > 7)
			return false;
		if(col < 0 || col > 7 || col_final < 0 || col_final > 7)
			return false;
		if(position[lin][col].empty || position[lin][col].piece != KING)
			return false;
		if(lin == lin_final && col == col_final)
			return false;
		
		if((lin == lin_final+1 || lin == lin_final-1 || lin == lin_final) && (col == col_final+1 || col == col_final-1 || col == col_final)){
			if(position[lin_final][col_final].empty || position[lin_final][col_final].color != position[lin][col].color){
				if(safeKing(lin_final, col_final, position[lin][col].color)){
					position[lin_final][col_final] = position[lin][col];
					if(position[lin][col].color == BLACK){
						blackKing_x = lin_final;
						blackKing_y = col_final;
					} else {
						whiteKing_x = lin_final;
						whiteKing_y = col_final;
					}
					position[lin][col].empty = true;
					return true;
				}
			}
		}
		
		return false;
	}
}
