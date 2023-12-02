#include "Board.h"

Board::Board(Player* white, Player* black) {
    std::vector<AbstractPiece*> selectedPieces;
    squares.reserve(64); // Reserve space for 64 squares

    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            bool isWhite = (file + rank) % 2 != 0;
            ChessColor currColor = (isWhite) ? ChessColor::White : ChessColor::Black;
            Location loc(rank, static_cast<File>(file));
            Square mySquare(loc, currColor, nullptr);
            squares.push_back(mySquare);
        }
    }

    /* Place down white pieces */
    selectedPieces = white->getPieces("Pawn");
    for (int i = 48; i < 56; i++) {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = white->getPieces("Rook");
    squares[63].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[56].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = white->getPieces("Knight");
    squares[62].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[57].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = white->getPieces("Bishop");
    squares[61].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[58].setOccupant(selectedPieces.back());

    selectedPieces = white->getPieces("King");
    squares[60].setOccupant(selectedPieces.back());

    selectedPieces = white->getPieces("Queen");
    squares[59].setOccupant(selectedPieces.back());

    /* Place down black pieces */
    selectedPieces = black->getPieces("Pawn");
    for (int i = 8; i < 16; i++) {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = black->getPieces("Rook");
    squares[0].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[7].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = black->getPieces("Knight");
    squares[1].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[6].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = black->getPieces("Bishop");
    squares[2].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[5].setOccupant(selectedPieces.back());

    selectedPieces = black->getPieces("King");
    squares[4].setOccupant(selectedPieces.back());

    selectedPieces = black->getPieces("Queen");
    squares[3].setOccupant(selectedPieces.back());
}

void Board::placePiece(AbstractPiece* piece, int square) {
    if (squares[square].isOccupied()) {
        squares[square].reset();
    }
    squares[square].setOccupant(piece);
}

Square* Board::getSquare(int index){
    return &squares[index];
}

void Board::handlePieceMoved(AbstractPiece* piece) {
    squares[piece->getPreviousSquare()].setOccupant(nullptr);
    squares[piece->getSquare()].setOccupant(piece); 
    // Validate isChecked, pieceHopping, isCheckMated, inBoardArea
}

Board::~Board() {}

std::ostream& operator<<(std::ostream& out, Board& board) {
    for (size_t i = 0; i < 64; ++i) {
        out << board.squares[i];

        if ((i + 1) % 8 == 0) {
            out << '\n'; // Start a new line after printing 8 squares (end of a row)
        }
    }
    return out;
}

