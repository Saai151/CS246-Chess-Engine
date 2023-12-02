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