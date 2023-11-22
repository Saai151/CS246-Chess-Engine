#include "Board.h"

Board::Board() {
    squares.reserve(64); // Reserve space for 64 squares

    for (int file = 0; file < 8; ++file) {
        for (int rank = 0; rank < 8; ++rank) {
            bool isWhite = (file + rank) % 2 != 0;
            color currColor = (isWhite) ? color::white : color::black;
            Location loc(rank + 1, static_cast<File>('A' + file));

            squares.emplace_back(loc, currColor, false);
        }
    }
}

Square Board::getSquare(int index){
    return squares[index];
}

std::ostream& operator<<(std::ostream& out, Board& board) {
    for (size_t i = 0; i < 64; ++i) {
        out << std::setw(5) << board.getSquare(i); // Assuming Square has its operator<< defined
        if ((i + 1) % 8 == 0) {
            out << '\n'; // Start a new line after printing 8 squares (end of a row)
        }
    }
    return out;
}
