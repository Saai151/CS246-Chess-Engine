#include "Board.h"

Board::Board() {
    squares.reserve(64); // Reserve space for 64 squares

        for (int file = 0; file < 8; ++file) {
            for (int rank = 0; rank < 8; ++rank) {
                bool isWhite = (file + rank) % 2 != 0;
                color currColor = (isWhite) ? color::light : color::dark;
                Location loc(rank + 1, static_cast<File>('A' + file));

                Square mySquare(loc, currColor, false);

                // Assign specific pieces to their starting positions
                if (rank == 1 || rank == 6) {
                    if (rank == 1) {
                        AbstractPiece piece = Pawn(file+rank, pieceColor::Black); // Instantiate a Black Pawn
                        pieces.push_back(piece);
                    } else {
                        AbstractPiece piece = Pawn(file+rank, pieceColor::White); // Instantiate a White Pawn
                        pieces.push_back(piece);
                    }
                } else if (rank == 0 || rank == 7) {
                // Other pieces in the back row
                pieceColor color = (rank == 0) ? pieceColor::Black : pieceColor::White;
                if (file == 0 || file == 7) {
                    // Rooks
                    AbstractPiece piece = Rook(file+rank, color);
                    pieces.push_back(piece);
                } else if (file == 1 || file == 6) {
                    // Knights
                    AbstractPiece piece = Knight(file+rank, color);
                    pieces.push_back(piece);
                } else if (file == 2 || file == 5) {
                    // Bishops
                    AbstractPiece piece = Bishop(file+rank, color);
                    pieces.push_back(piece);
                } else if (file == 3) {
                    // Queens
                    AbstractPiece piece = Queen(file+rank, color);
                    pieces.push_back(piece);
                } else if (file == 4) {
                    // Kings
                    AbstractPiece piece = King(file+rank, color);
                    pieces.push_back(piece);
                }
            }
                // Add the pieceAndSquare to the squares vector
                squares.push_back(mySquare);
            }
        }
    }

Square Board::getSquare(int index){
    return squares[index];
}

AbstractPiece Board::getPiece(int index){
    return pieces[index];
}

int Board::getNumPieces(){
    return pieces.size();
}

std::ostream& operator<<(std::ostream& out, Board& board) {
    for (size_t i = 0; i < 64; ++i) {
        if (i < board.getNumPieces() && i == board.getPiece(i).getSquare()){
            // out << board.getPiece(i); I'll change this in the text display class, this doesn't work yet
        } else{
            out << board.getSquare(i);
        }
        if ((i + 1) % 8 == 0) {
            out << '\n'; // Start a new line after printing 8 squares (end of a row)
        }
    }
    return out;
}
