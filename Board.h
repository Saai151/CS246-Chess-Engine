#include <ostream>
#include <vector>
#include <iostream>
#include "Square.h"
#include <iomanip>


class Board{
    private:
        std::vector<Square> squares;
    public:
        Board();
        Square getSquare(int index);
};

std::ostream& operator<<(std::ostream& out, Board& board);