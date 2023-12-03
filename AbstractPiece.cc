#include "AbstractPiece.h"

AbstractPiece::~AbstractPiece()
{
    pieceRemovedObserver->handlePieceRemoved(this);
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
    return {};
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
    return {};
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
    return {};
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
    int currSquare = this->getSquare();
    vector<int> moves = {currSquare + 17, currSquare + 15, currSquare - 17,
                         currSquare - 15, currSquare + 10, currSquare - 10, currSquare + 6, currSquare - 6};

    for (size_t i = 0; i < moves.size(); ++i)
    {
        if (targetSquare == moves[i])
        {
            return true;
        }
    }
    return false;
}

std::vector<int> Knight::allMoves() {
    return {};
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

bool Rook::validMove(int targetSquare)
{
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
    return {};
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
    return {};
}

void AbstractPiece::move(int newIndex) {
    if (!validMove(newIndex)) throw std::invalid_argument("Invalid move");
    int previousSquareIndexCopy = previousSquareIndex;
    int squareIndexCopy = squareIndex;

    previousSquareIndex = squareIndex;
    squareIndex = newIndex;
    
    bool validatedByBoard = pieceMovedObserver->handlePieceMoved(this);
    if (!validatedByBoard) {
        previousSquareIndex = previousSquareIndexCopy;
        squareIndex = squareIndexCopy;
        throw std::invalid_argument("Invalid move");
    }
}
