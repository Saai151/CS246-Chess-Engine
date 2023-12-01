#include "Board.h"
Board::Board() {
    squares.reserve(64); // Reserve space for 64 squares

        for (int file = 0; file < 8; ++file) {
            for (int rank = 0; rank < 8; ++rank) {
                bool isWhite = (file + rank) % 2 != 0;
                color currColor = (isWhite) ? color::light : color::dark;
                Location loc(rank + 1, static_cast<File>('A' + file));

                Square mySquare(loc, currColor, false);
                squares.push_back(mySquare);
            }
        }

        for (int i = 8; i <= 15; ++i){
            AbstractPiece piece = Pawn(i, pieceColor::Black);
            pieces.push_back(piece);
        }

        for (int i = 48; i <= 55; ++i){
            AbstractPiece piece = Pawn(i, pieceColor::White);
            pieces.push_back(piece);
        }
        
        pieces.push_back(Rook(0, pieceColor::Black));
        pieces.push_back(Rook(7, pieceColor::Black));
        pieces.push_back(Knight(1, pieceColor::Black));
        pieces.push_back(Knight(6, pieceColor::Black));
        pieces.push_back(Bishop(2, pieceColor::Black));
        pieces.push_back(Bishop(5, pieceColor::Black));
        pieces.push_back(Queen(3, pieceColor::Black));
        pieces.push_back(King(4, pieceColor::Black));
        pieces.push_back(Rook(56, pieceColor::White));
        pieces.push_back(Rook(63, pieceColor::White));
        pieces.push_back(Knight(57, pieceColor::White));
        pieces.push_back(Knight(62, pieceColor::White));
        pieces.push_back(Bishop(58, pieceColor::White));
        pieces.push_back(Bishop(61, pieceColor::White));
        pieces.push_back(Queen(59, pieceColor::White));
        pieces.push_back(King(60, pieceColor::White));
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
        bool pieceFound = false;
        for ( auto piece : board.pieces) {
            if (piece.getSquare() == i) {
                pieceFound = true;
                if (piece.getName() == "Pawn") {
                    out << (piece.getPieceColor() == pieceColor::White ? "P" : "p");
                } else if (piece.getName() == "Queen") {
                    out << (piece.getPieceColor() == pieceColor::White ? "Q" : "q");
                } else if (piece.getName() == "King") {
                    out << (piece.getPieceColor() == pieceColor::White ? "K" : "k");
                } else if (piece.getName() == "Knight") {
                    out << (piece.getPieceColor() == pieceColor::White ? "N" : "n");
                } else if (piece.getName() == "Bishop") {
                    out << (piece.getPieceColor() == pieceColor::White ? "B" : "b");
                } else if (piece.getName() == "Rook") {
                    out << (piece.getPieceColor() == pieceColor::White ? "R" : "r");
                }
                break; // Found the piece at this square, move to the next square
            }
        }
        if (!pieceFound) {
            out << board.getSquare(i);
        }
        if ((i + 1) % 8 == 0) {
            out << '\n'; // Start a new line after printing 8 squares (end of a row)
        }
    }
    return out;
}

