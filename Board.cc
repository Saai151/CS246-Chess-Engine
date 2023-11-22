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