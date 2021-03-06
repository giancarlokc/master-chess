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

#ifndef Included_gui_H
#define Included_gui_H

#include "chess.h"

using namespace chess;

namespace gui{
	class Interface{
		public:
			void showBoard(Board);
			void startBoard_nc(Board b);
			void possibleMove(Board, int, int, int, int);
			void endBoard_nc(Board b);
			void showBoard_nc(Board, int*, int*, int*, int *);
			void showBoard_nc_onlyshow(Board, int*, int*, int*, int *);
	};
}

#endif
