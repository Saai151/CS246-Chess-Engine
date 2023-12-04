#include "Board.h"

Board::Board(Player* white, Player* black, DisplayObserver* g) {
    std::vector<AbstractPiece*> selectedPieces;
    squares.reserve(64); // Reserve space for 64 squares

    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            bool isWhite = (file + rank) % 2 != 0;
            ChessColor currColor = (isWhite) ? ChessColor::White : ChessColor::Black;
            Location loc(rank, static_cast<File>(file));
            Square mySquare(loc, currColor, nullptr, g);
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

//copy constructor
Board::Board(Board& b) {
    this->squares = b.squares;
}

bool Board::isInCheck(ChessColor c) {
    AbstractPiece* king;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c) {
            king = s.getOccupant();
        }
    }

    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() != c && s.getOccupant()->validMove(king->getSquare())) {
            return true;
        }
    }

    return false;
}

bool Board::isCheckmate(ChessColor c) {
    AbstractPiece* king;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c) {
            king = s.getOccupant();
        }
    }

    bool canMakeMove = true;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() != c && s.getOccupant()->validMove(king->getSquare())) {
            for (int move : king->allMoves()) {
                canMakeMove = true;

                for (auto& s_ : squares) {
                    if (s_.isOccupied() && s_.getOccupant()->getPieceColor() != c && s_.getOccupant()->validMove(move)) {
                        canMakeMove = false;
                        break;
                    }
                }

                if (canMakeMove) return false; // not in checkmate
            }
        }
    }

    // CHECK IF WE CAN MOVE SOME OTHER PIECE IN FRONT OF THE KING

    return true;
}

bool Board::isStalemate() {
    if (isInCheck(ChessColor::White) || isInCheck(ChessColor::Black)) return false;

    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->allMoves().size() != 0) {
            return false;
        }
    }

    return true;
}

void Board::placePiece(AbstractPiece* piece, int square) {
    if (squares[square].isOccupied()) {
        squares[square].reset();
    }
    squares[square].setOccupant(piece);
}

void Board::resetSquare(int index) {
    squares[index].reset();
}

bool Board::handlePieceMoved(AbstractPiece* piece) {
    squares[piece->getPreviousSquare()].setOccupant(nullptr);
    squares[piece->getSquare()].setOccupant(piece); 
    // Validate isChecked, pieceHopping, isCheckMated, inBoardArea
    return true;
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

