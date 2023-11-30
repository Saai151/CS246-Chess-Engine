#include <ostream>
#include <vector>
#include <iostream>
#include "Square.h"
#include "AbstractPiece.h"
#include <iomanip>
#include <vector>


class Board{
    private:
        std::vector<Square> squares;
        std::vector<AbstractPiece> pieces;
    public:
        Board();
        Square getSquare(int index);
        AbstractPiece getPiece (int index);
        int getNumPieces();
};

std::ostream& operator<<(std::ostream& out, Board& board);