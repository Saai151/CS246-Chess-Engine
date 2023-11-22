#include "Board.h"

Board::Board(){
    for (int file = 0; file < 8; ++file){
        for (int rank = 0; rank < 8; ++rank){
            bool isWhite = (file + rank) % 2 != 0;
            color currColor = (isWhite) ?  color::white : color::black;
            int index = file*8 + rank;
            Location loc(rank + 1, static_cast<File>('A' + file));

            squares[index] = new Square(loc, currColor, false );
        }
    }
}