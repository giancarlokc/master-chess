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

#ifndef Included_chess_H
#define Included_chess_H

#define KING 5
#define QUEEN 4
#define BISHOP 3
#define HORSE 2
#define TOWER 1
#define PAWN 0

#define BLACK 0
#define WHITE 1

namespace chess{
	/* Each position in the board */
	class Position{
		public:
			bool empty;
			int  piece;
			int  color;
	};

	class Board{
		public:
			int blackKing_x, blackKing_y;
			int whiteKing_x, whiteKing_y;
			Position position[8][8];
		
			/* Reset board (To chess default) */
			void reset(void);
			
			/* Check if some movement (lin, col) is safe for the King */
			bool safeKing(int, int, int);
			
			/* Movement functions (line_initial, column_initial, line_final, column_final) */
			bool movePawn(int, int, int, int);
			bool moveHorse(int, int, int, int);
			bool moveTower(int, int, int, int);
			bool moveBishop(int, int, int, int);
			bool moveQueen(int, int, int, int);
			bool moveKing(int, int, int, int);
			
			bool checkMate(int);
	};
}

#endif
