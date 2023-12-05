#include "AbstractPiece.h"

AbstractPiece::~AbstractPiece()
{
    pieceRemovedObserver->handlePieceRemoved(this);
}

void AbstractPiece::revertLastMove(int newSquare, int prevSquare) {
    if (this->getName() == "Pawn") {
        Pawn* p = (Pawn*)this;
        if (abs(squareIndex - previousSquareIndex) == 16) {
            //std::cout << abs(squareIndex - previousSquareIndex) << std::endl;
            p->reset();
        }
    }
    previousSquareIndex = squareIndex;
    squareIndex = newSquare;
    pieceMovedObserver->handlePieceMoved(this, true);
    previousSquareIndex = prevSquare;
}

std::string Pawn::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "P";
    }
    else
    {
        return "p";
    }
}

bool Pawn::validMove(int targetSquare)
{
    int currSquare = this->getSquare();

    int delta = targetSquare - currSquare;
    //std::cout << this->isFirst << std::endl;

    if (getPieceColor() == ChessColor::Black) {
        if ((delta == 8 || delta == 16) && isFirst) {
            isFirst = false; // Set isFirst to false after the initial move
            return true;
        } else if (delta == 8) {
            return true;
        } else if (delta == 7 || delta == 9) {
            return true;
        }
    } else { // For white pawns
        if ((delta == -8 || delta == -16) && isFirst) {
            isFirst = false; // Set isFirst to false after the initial move
            return true;
        } else if (delta == -8) {
            return true;
        } else if (delta == -7 || delta == -9) {
            return true;
        }
    }

    return false;
}

std::vector<int> Pawn::allMoves() {
    //std::cout << this->getSquare() << " GET SQUARE" << std::endl;
    int currSquare = this->getSquare();
    vector<int> moves = {};
    if (this->getPieceColor() == ChessColor::White){
        moves.push_back(currSquare - 8);
        moves.push_back(currSquare - 7);
        moves.push_back(currSquare - 9);
    } else{
        moves.push_back(currSquare + 8);
        moves.push_back(currSquare + 7);
        moves.push_back(currSquare + 9);
    }
    if (this->getPieceColor() == ChessColor::White && isFirst){
        moves.push_back(currSquare - 16);
    }
    if (this->getPieceColor() == ChessColor::Black && isFirst){
        moves.push_back(currSquare + 16);
    }

    return moves;
}

std::string Queen::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "Q";
    }
    else
    {
        return "q";
    }
}

bool Queen::validMove(int targetSquare)
{
    int currSquare = this->getSquare();

    // Calculate the difference between the target and current square
    int delta = targetSquare - currSquare;

    if ((delta % 8 == 0 && delta != 0) || (abs(delta) <= 7 && abs(delta) != 0) ||
        (abs(delta) % 9 == 0 || abs(delta) % 7 == 0)) {
        if (targetSquare >= 0 && targetSquare < 64) {
            return true;
        }
    }
    return false; 
}

std::vector<int> Queen::allMoves() {
    vector<int> validMoves = {};

    int currSquare = this->getSquare();
    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare + (i * 8));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare - (i * 8));
    }

    int currSquareCopy = currSquare;
    while (currSquareCopy % 8 != 0) {
        currSquareCopy--;
        validMoves.push_back(currSquareCopy);
    }

    currSquareCopy = currSquare;
    while (currSquareCopy % 8 != 0) {
        currSquareCopy++;
        validMoves.push_back(currSquareCopy);
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare + (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare - (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare + (i * 9));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare - (i * 9));
    }

    return validMoves;
}

std::string King::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "K";
    }
    else
    {
        return "k";
    }
}

bool King::validMove(int targetSquare)
{
    int currSquare = this->getSquare();
    vector<int> moves = {currSquare + 8, currSquare - 8, currSquare + 9, currSquare - 9};

    for (size_t i = 0; i < moves.size(); ++i)
    {
        if (targetSquare == moves[i])
        {
            return true;
        }
    }
    return false;
}

std::vector<int> King::allMoves() {
    vector<int> validMoves;

    // Define increments for horizontal, vertical, and diagonal movements
    vector<int> kingOffsets = { -9, -8, -7, -1, 1, 7, 8, 9 }; // All directions

    for (size_t i = 0; i < 8; ++i) {
        int newSquare = this->getSquare() + kingOffsets[i];
        validMoves.push_back(newSquare);  
    }

    return validMoves;
}

std::string Knight::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "N";
    }
    else
    {
        return "n";
    }
}

bool Knight::validMove(int targetSquare)
{
    std::vector<int> valid = {};
    int currSquare = targetSquare;
    int x = currSquare % 8;
    int y = currSquare / 8;

    if ((x % 8) == ((x + 2) % 8)) {
        valid.push_back((x + 2) + ((y + 1) * 8));
        valid.push_back((x + 2) + ((y - 1) * 8));
    } else if ((x % 8) == ((x - 2) % 8)) {
        valid.push_back((x - 2) + ((y + 1) * 8));
        valid.push_back((x - 2) + ((y - 1) * 8));
    } else if ((x % 8) == ((x - 1) % 8)) {
        valid.push_back((x - 1) + ((y + 2) * 8));
        valid.push_back((x - 1) + ((y - 2) * 8));
    } else if ((x % 8) == ((x + 1) % 8)) {
        valid.push_back((x + 1) + ((y + 1) * 8));
        valid.push_back((x + 1) + ((y - 2) * 8));
    }    

    for (size_t i = 0; i < valid.size(); ++i)
    {
        if (targetSquare == valid[i])
        {
            return true;
        }
    }
    return false;
}

std::vector<int> Knight::allMoves() {
    std::vector<int> validMoves = {};
    int currSquare = this->getSquare();
    
    

    return validMoves;
}

std::string Rook::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "R";
    }
    else
    {
        return "r";
    }
}

bool Rook::validMove(int targetSquare) {
    int currSquare = this->getSquare();
    int delta = targetSquare - currSquare;

    if ((delta % 8 == 0 && delta != 0) || (abs(delta) <= 7 && abs(delta) != 0)) {
        if (targetSquare >= 0 && targetSquare < 64) {
            return true;
        }
    }
    return false;
}

std::vector<int> Rook::allMoves() {
    vector<int> validMoves = {};

    int currSquare = this->getSquare();
    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare + (i * 8));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare - (i * 8));
    }

    int currSquareCopy = currSquare;
    while (currSquareCopy % 8 != 0) {
        currSquareCopy--;
        validMoves.push_back(currSquareCopy);
    }

    currSquareCopy = currSquare;
    while (currSquareCopy % 8 != 0) {
        currSquareCopy++;
        validMoves.push_back(currSquareCopy);
    }

    return validMoves;
}

std::string Bishop::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "B";
    }
    else
    {
        return "b";
    }
}

bool Bishop::validMove(int targetSquare)
{
     int currSquare = this->getSquare();

    int delta = targetSquare - currSquare;

    if (abs(delta) % 9 == 0 || abs(delta) % 7 == 0) {
        return true;      
    }
    return false;
}

std::vector<int> Bishop::allMoves() {
   vector<int> validMoves;

    int curr = this->getSquare();
    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(curr + (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(curr - (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(curr + (i * 9));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(curr - (i * 9));
    }

    return validMoves;
}

void AbstractPiece::move(int newIndex) {
    //std::cout << "H" << std::endl;
    if (!validMove(newIndex)) throw std::invalid_argument("Invalid move 5");
    //std::cout << "M" << std::endl;
    int previousSquareIndexCopy = previousSquareIndex;
    int squareIndexCopy = squareIndex;

    previousSquareIndex = squareIndex;
    squareIndex = newIndex;
    
    bool validatedByBoard = pieceMovedObserver->handlePieceMoved(this);
    if (!validatedByBoard) {
        previousSquareIndex = previousSquareIndexCopy;
        squareIndex = squareIndexCopy;
        throw std::invalid_argument("Invalid move 4");
    }
}
