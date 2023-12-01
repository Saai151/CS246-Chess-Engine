#include <ostream>
#include <vector>
#include <iostream>
#include "Square.h"
#include "AbstractPiece.h"
#include <iomanip>
#include <vector>


class Board {    
    public:
        std::vector<Square> squares;
        std::vector<AbstractPiece> pieces;
        Board();
        Square getSquare(int index);
        AbstractPiece getPiece (int index);
        int getNumPieces();
};

std::ostream& operator<<(std::ostream& out, Board& board);