#include "Board.h"

bool isCastling(std::vector<Square> squares, int startLocation, int endLocation) {
    if (squares[startLocation].getOccupant()->getName() == "King" 
            && squares[startLocation].getOccupant()->getIsFirst()
            && squares[endLocation].isOccupied()
            && squares[endLocation].getOccupant()->getName() == "Rook"
            && squares[endLocation].getOccupant()->getIsFirst()) {
        return true;
    }

    return false;
}

std::vector<AbstractPiece*> getPieces(std::string name, std::vector<AbstractPiece*> pieces) {
    std::vector<AbstractPiece *> result;

    for (auto &p : pieces)
    {
        if (p->getName() == name)
            result.push_back(p);
    }

    return result;
}

Board::Board(std::vector<AbstractPiece*> white, std::vector<AbstractPiece*> black, DisplayAggregator* g) {
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
    selectedPieces = getPieces("Pawn", white);
    for (int i = 48; i < 56; i++) {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = getPieces("Rook", white);
    squares[63].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[56].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Knight", white);
    squares[62].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[57].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Bishop", white);
    squares[61].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[58].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("King", white);
    squares[60].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("Queen", white);
    squares[59].setOccupant(selectedPieces.back());

    /* Place down black pieces */
    selectedPieces = getPieces("Pawn", black);
    for (int i = 8; i < 16; i++) {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = getPieces("Rook", black);
    squares[0].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[7].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Knight", black);
    squares[1].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[6].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Bishop", black);
    squares[2].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[5].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("King", black);
    squares[4].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("Queen", black);
    squares[3].setOccupant(selectedPieces.back());
}

void Board::reset() {
    for (auto& s : squares) {
        s.setOccupant(nullptr);
    }
}

bool Board::isPieceCheckingTheKing(Square* s, AbstractPiece* king, ChessColor c) {
    return s->isOccupied() 
        && s->getOccupant()->getPieceColor() != c 
        && s->getOccupant()->validMove(king->getSquare())
        && isValidMove(s->getOccupant(), s->getOccupant()->getSquare(), king->getSquare());

}

std::vector<Square*> Board::isInCheck(ChessColor c) {
    std::vector<Square*> checked;
    AbstractPiece* king;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c) {
            king = s.getOccupant();
        }
    }

    for (auto& s : squares) {
        if (isPieceCheckingTheKing(&s, king, c)) {
            checked.push_back(&s);
        }
    }

    return checked;
}

bool Board::isCheckmate(ChessColor c) {
    AbstractPiece* king;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c) {
            king = s.getOccupant();
        }
    }


    std::vector<Square*> checkedPieces = isInCheck(c);
    if (!checkedPieces.size()) return false;

    bool canMakeMove = true;
    for (auto& s : checkedPieces) {
        for (int move : king->allMoves()) {
            canMakeMove = true;

            for (auto& s_ : squares) {
                if (isPieceCheckingTheKing(s, king, c)) {
                    canMakeMove = false;
                    break;
                }
            }

            if (canMakeMove) return false; // not in checkmate
        }
    }

    // CHECK IF WE CAN MOVE SOME OTHER PIECE IN FRONT OF THE KING

    return false;
}

bool Board::isStalemate(ChessColor current_colour) {
    if (isInCheck(current_colour).size() > 0) return false;
    
    for (Square s : squares) {
        if (s.isOccupied() && s.getColor() == current_colour) {
            for (int move : s.getOccupant()->allMoves()) {
                if (isValidMove(s.getOccupant(), s.getOccupant()->getSquare(), move)) {
                    return false;
                }
            }
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

bool Board::handlePieceMoved(AbstractPiece* piece, bool overrideValidation) {
    if (overrideValidation || isValidMove(piece, piece->getPreviousSquare(), piece->getSquare())) {

        if (isCastling(squares, piece->getPreviousSquare(), piece->getSquare())) {
            AbstractPiece* temp_1 = squares[piece->getPreviousSquare()].getOccupant();
            AbstractPiece* temp_2 = squares[piece->getSquare()].getOccupant();
            
            squares[piece->getSquare()].setOccupant(nullptr);
            squares[piece->getPreviousSquare()].setOccupant(nullptr);

            squares[piece->getSquare()].setOccupant(temp_1);
            temp_1->hasMoved();

            squares[piece->getPreviousSquare()].setOccupant(temp_2);
            temp_2->hasMoved();
        } else {
            squares[piece->getPreviousSquare()].setOccupant(nullptr);
            squares[piece->getSquare()].setOccupant(piece);

            if (piece->getName() == "Pawn" && ((7 - piece->getSquare() >= 0) || (63 - piece->getSquare()) <= 7)) {
                std::string added;
                std::cin >> added;

                AbstractPiece* addedPiece = parsePieceSymbolAndCopy(added[0], piece);
                int ind = piece->getSquare();
                squares[ind].setOccupant(nullptr);

                piece->detachRemovedObserver();
                delete piece;

                piece = addedPiece;
                squares[ind].setOccupant(piece);
                std::cout << "ADDR: " << piece << std::endl;
            } 

            return true;
        }
    }
    
    return false;
}

bool Board::isValidMove(AbstractPiece* target, int startLocation, int endLocation) {
    if (endLocation < 0 || endLocation > 63){
        return false;
    }

    int delta = abs(endLocation - startLocation);
    ChessColor captureColor;
    if (target->getPieceColor() == ChessColor::Black){
        captureColor = ChessColor::White;
    } else{
        captureColor = ChessColor::Black;
    }

    if (isCastling(squares, startLocation, endLocation)) {
        for (int i = 1; i < delta; i++) {
            if (startLocation > endLocation) {
                if (squares[startLocation - i].isOccupied()) return false;
            } else {
                if (squares[startLocation + i].isOccupied()) return false;
            }
        }
       return true;
        
    }

    if (squares[endLocation].isOccupied() && squares[endLocation].getOccupant()->getPieceColor() != captureColor) {
        return false;
    }

    if (target->getName() == "King"){
        int previous = target->getPreviousSquare();
        target->move(endLocation);
        if ((this->isInCheck(target->getPieceColor()).size() == 0)){
            target->revertLastMove(startLocation, previous);
            return false;
        }
    }
    
    if (target->getName() == "Knight") return true;

    if (delta % 9 == 0 || delta % 7 == 0) {

        int x;

        if (delta % 9 == 0) {
            x = 9;
        } else if (delta % 7 == 0) {
            x = 7;
        }

        int steps = delta / x;
        for (int i = 1; i < steps; ++i) {
            int index = (startLocation < endLocation) ? startLocation + (i * x) : startLocation - (i * x);
            if (squares[index].isOccupied()) return false;
        }

        if (target->getName() == "Pawn") {
            if (squares[endLocation].isOccupied()) return true;
            else return false;
        }
    } else if (delta % 8 == 0) { // veritcal move
        if (target->getName() == "Pawn") {
            if (squares[endLocation].isOccupied()) return false;
        }
        if (startLocation > endLocation) {
            for (int i = 1; i < (delta / 8); i++) {
                if (squares[startLocation - (i * 8)].isOccupied()) return false;
            }
         } else {
            for (int i = 1; i < (delta / 8); i++) {
                if (squares[startLocation + (i * 8)].isOccupied()) return false;
            }
         }
    } else {
        if (startLocation > endLocation) {
            for (int i = 1; i < delta; i++) {
                if (squares[startLocation - i].isOccupied()) return false;
            }
        } else {
            for (int i = 0; i < delta; i++) {
                if (squares[startLocation + i].isOccupied()) return false;
            }
        }
    }

    return true;
}

Board::~Board() {}
