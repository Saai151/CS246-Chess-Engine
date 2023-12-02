#include "AbstractPiece.h"

AbstractPiece::~AbstractPiece(){
    pieceRemovedObserver->handlePieceRemoved(this);
}

void AbstractPiece::move(int newIndex) {
    previousSquareIndex = squareIndex;
    squareIndex = newIndex;
    pieceMovedObserver->handlePieceMoved(this);
    std::cout << "MOVING" << std::endl;
}

std::string Pawn::printable() const{
    if (getPieceColor() == ChessColor::White){
        return "P";
    }
    else {
        return "p";
    }
}

bool Pawn::validMove(int targetSquare, vector<AbstractPiece*> boardState){
        ChessColor targetColor;
        if (this->getPieceColor() == ChessColor::White){
            targetColor = ChessColor::Black;
        } else{
                targetColor = ChessColor::White;
        }
        int currSquare = this->getSquare();
        bool occupied1 = false;
        bool occupied2 = false;
        std::vector<int> moves;
        
        for ( auto piece : boardState) {
            if (piece->getSquare() == currSquare + 8) {
                occupied1 = true;
            }
            else if (piece->getSquare() == currSquare + 16){
                occupied2 = true;
            }
            else if(piece->getSquare() == currSquare + 9 && piece->getPieceColor() == targetColor){
                moves.push_back(currSquare + 9);
            }
            else if (piece->getSquare() == currSquare - 9 && piece->getPieceColor() == targetColor){
                moves.push_back(currSquare - 9);
            }

        if (isFirst && !occupied2){
            moves.push_back(currSquare+16);
        }
        else if (!occupied1){
            moves.push_back(currSquare+8);
        }

        for (int i = 0; i < moves.size(); ++i){
            if (targetSquare == moves[i]){
                return true;
            }
        }
        return false;    
    }        
}

std::string Queen::printable() const  {
    if (getPieceColor() == ChessColor::White){
        return "Q";
    }
    else {
        return "q";
    }
}

std::string King::printable() const {
    if (getPieceColor() == ChessColor::White){
        return "K";
    }
    else {
        return "k";
    }
}

std::string Knight::printable() const {
    if (getPieceColor() == ChessColor::White){
        return "N";
    }
    else {
        return "n";
    }
}

std::string Rook::printable() const {
    if (getPieceColor() == ChessColor::White){
        return "R";
    }
    else {
        return "r";
    }
}

std::string King::printable() const {
    if (getPieceColor() == ChessColor::White){
        return "B";
    }
    else {
        return "b";
    }
}