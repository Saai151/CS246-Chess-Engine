#include "Board.h"

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

std::vector<Square*> Board::isInCheck2(ChessColor c, std::vector<Square> boardState) {
    std::vector<Square*> checked;
    AbstractPiece* king;
    for (auto& s : boardState) {
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
    cout << "in stalemate" << endl;
    if (isInCheck(current_colour).size() > 0) return false;
    
    cout << "oin" << endl;
    for (Square s : squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() == current_colour) {
            cout << s.getOccupant()->getName() << endl;
            cout << s.getOccupant()->getSquare() << endl;
            for (int move : s.getOccupant()->allMoves()) {
                cout << move << endl;
                if (isValidMove(s.getOccupant(), s.getOccupant()->getSquare(), move)) {
                    cout << s.getOccupant()->getName();
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
    cout << "handle piece moved" << endl;
    cout << "previous: " << piece->getPreviousSquare() << endl;
    cout << "squareindex " << piece->getSquare();

    if (overrideValidation || isValidMove(piece, piece->getPreviousSquare(), piece->getSquare())) {
        squares[piece->getPreviousSquare()].setOccupant(nullptr);
        std::cout << piece->getSquare() << std::endl;
        squares[piece->getSquare()].setOccupant(piece); // broken
        return true;
    }
    
    return false;
}

bool Board::isValidMove(AbstractPiece* target, int startLocation, int endLocation) {
    if (endLocation < 0 || endLocation > 63){
        return false;
    }

    ChessColor captureColor;
    if (target->getPieceColor() == ChessColor::Black){
        captureColor = ChessColor::White;
    } else{
        captureColor = ChessColor::Black;
    }


    if (squares[endLocation].isOccupied() && squares[endLocation].getOccupant()->getPieceColor() != captureColor) {
        return false;
    }

    if (target->getName() == "King"){
        int previous = target->getPreviousSquare();
        std::vector<Square> boardState = squares;
        boardState[endLocation].setOccupant(target);
        //target->move(endLocation);
        if ((this->isInCheck2(target->getPieceColor(), boardState).size() == 0)){
           // target->revertLastMove(startLocation, previous);
           cout << "Moving to: " << endLocation << "causes a check" << endl;
            return false;
        }
    }
    if (target->getName() == "Knight") return true;

    /* CHECK FOR CASTLING */
    if (squares[startLocation].getOccupant()->getName() == "King" 
            && startLocation == 60 
            && squares[startLocation].getOccupant()->getIsFirst()
            && squares[endLocation].getOccupant()->getName() == "Rook"
            && startLocation == 63 || startLocation) {
        
    }

    int delta = abs(endLocation - startLocation);
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
