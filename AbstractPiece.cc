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
    int currSquare = this->getSquare();
    vector<int> moves = {currSquare + 8};
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
    vector<int> validMoves;

    vector<int> horizontalOffsets = { -1, 1, 0, 0, -9, -7, 7, 9 }; //combining capabiliies of rook and bishop

    for (size_t i = 0; i < 8; ++i) {
        int newSquare = this->getSquare();
        while (true) {
            newSquare += horizontalOffsets[i];

            if (newSquare < 0 || newSquare >= 64) {
                break;
            }
            validMoves.push_back(newSquare);
        }
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

    std::cout << "INSIDE 1" << std::endl;
    this->getSquare();
    std::cout << "INSIDE 2" << std::endl;

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

    // Doesn't check for out of bounds in moves yet

    int currSquare = this->getSquare();

    vector<int> moves = {currSquare + 17, currSquare + 15, currSquare - 17,
                         currSquare - 15, currSquare + 10, currSquare - 10, currSquare + 6, currSquare - 6};
    
    return moves;
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
    vector<int> validMoves;

    vector<int> horizontalOffsets = { -1, 1, 0, 0 }; // Left, Right, Up, Down
    vector<int> verticalOffsets = { 0, 0, -8, 8 };   // Left, Right, Up, Down

    for (size_t i = 0; i < 4; ++i) {
        int newSquare = this->getSquare();
        while (true) {
            newSquare += (i < 2) ? horizontalOffsets[i] : verticalOffsets[i];

            if (newSquare < 0 || newSquare >= 64) {
                break; // Move is out of bounds
            }


            // Empty square, continue in the same direction
            validMoves.push_back(newSquare);
        }
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

    vector<int> diagonalOffsets = { -9, -7, 7, 9 }; 

    for (size_t i = 0; i < 4; ++i) {
        int newSquare = this->getSquare();
        while (true) {
            newSquare += diagonalOffsets[i];

            if (newSquare < 0 || newSquare >= 64) {
                break; // Move is out of bounds
            }
            validMoves.push_back(newSquare);
        }
    }

    return validMoves;}

void AbstractPiece::move(int newIndex) {
    if (!validMove(newIndex)) throw std::invalid_argument("Invalid move 5");
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
