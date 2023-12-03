#include "AbstractPiece.h"

AbstractPiece::~AbstractPiece()
{
    pieceRemovedObserver->handlePieceRemoved(this);
}

void AbstractPiece::move(int newIndex)
{
    previousSquareIndex = squareIndex;
    squareIndex = newIndex;
    pieceMovedObserver->handlePieceMoved(this);
    std::cout << "MOVING" << std::endl;
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

// bool Pawn::validMove(int targetSquare, vector<AbstractPiece*> boardState){
//         ChessColor targetColor;
//         if (this->getPieceColor() == ChessColor::White){
//             targetColor = ChessColor::Black;
//         } else{
//                 targetColor = ChessColor::White;
//         }
//         int currSquare = this->getSquare();
//         bool occupied1 = false;
//         bool occupied2 = false;
//         std::vector<int> moves;
        
//         for ( auto piece : boardState) {
//             if (piece->getSquare() == currSquare + 8) {
//                 occupied1 = true;
//             }
//             else if (piece->getSquare() == currSquare + 16){
//                 occupied2 = true;
//             }
//             else if(piece->getSquare() == currSquare + 9 && piece->getPieceColor() == targetColor){
//                 moves.push_back(currSquare + 9);
//             }
//             else if (piece->getSquare() == currSquare - 9 && piece->getPieceColor() == targetColor){
//                 moves.push_back(currSquare - 9);
//             }

//         if (isFirst && !occupied2){
//             moves.push_back(currSquare+16);
//         }
//         else if (!occupied1){
//             moves.push_back(currSquare+8);
//         }

//         for (int i = 0; i < moves.size(); ++i){
//             if (targetSquare == moves[i]){
//                 return true;
//             }
//         }
//         return false;    
//     }        
// }

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

bool Queen::validMove(int targetSquare, vector<AbstractPiece *> boardState)
{
        int currSquare = this->getSquare();

    vector<int> moves;
    int i = 8;
    int j = 8;
    int a = 1;
    int b = 1;
    while (true)
    {
        if (i + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            i += i;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - i >= 0)
        {
            moves.push_back(currSquare - i);
            j += j;
        }
    }
    while (true)
    {
        if (b + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            b += b;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - a >= 0)
        {
            moves.push_back(currSquare - a);
            a += a;
        }
    }

    int currSquare = this->getSquare();

    i = 9;
    j = 9;
    a = 7;
    b = 7;
    while (true)
    {
        if (i + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            i += i;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - i >= 0)
        {
            moves.push_back(currSquare - i);
            j += j;
        }
    }
    while (true)
    {
        if (b + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            b += b;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - a >= 0)
        {
            moves.push_back(currSquare - a);
            a += a;
        }
    }


    for (int i = 0; i < moves.size(); ++i)
    {
        if (targetSquare == moves[i])
        {
            return true;
        }
    }
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

bool King::validMove(int targetSquare, vector<AbstractPiece *> boardState)
{
    int currSquare = this->getSquare();
    vector<int> moves = {currSquare + 8, currSquare - 8, currSquare + 9, currSquare - 9};

    for (int i = 0; i < moves.size(); ++i)
    {
        if (targetSquare == moves[i])
        {
            return true;
        }
    }
    return false;
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

bool Knight::validMove(int targetSquare, vector<AbstractPiece *> boardState)
{
    int currSquare = this->getSquare();
    vector<int> moves = {currSquare + 17, currSquare + 15, currSquare - 17,
                         currSquare - 15, currSquare + 10, currSquare - 10, currSquare + 6, currSquare - 6};

    for (int i = 0; i < moves.size(); ++i)
    {
        if (targetSquare == moves[i])
        {
            return true;
        }
    }
    return false;
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

bool Rook::validMove(int targetSquare, vector<AbstractPiece *> boardState)
{
    int currSquare = this->getSquare();

    vector<int> moves;
    int i = 8;
    int j = 8;
    int a = 1;
    int b = 1;
    while (true)
    {
        if (i + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            i += i;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - i >= 0)
        {
            moves.push_back(currSquare - i);
            j += j;
        }
    }
    while (true)
    {
        if (b + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            b += b;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - a >= 0)
        {
            moves.push_back(currSquare - a);
            a += a;
        }
    }

    for (int i = 0; i < moves.size(); ++i)
    {
        if (targetSquare == moves[i])
        {
            return true;
        }
    }
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

bool Bishop::validMove(int targetSquare, vector<AbstractPiece *> boardState)
{
    int currSquare = this->getSquare();

    vector<int> moves;
    int i = 9;
    int j = 9;
    int a = 7;
    int b = 7;
    while (true)
    {
        if (i + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            i += i;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - i >= 0)
        {
            moves.push_back(currSquare - i);
            j += j;
        }
    }
    while (true)
    {
        if (b + currSquare <= 63)
        {
            moves.push_back(i + currSquare);
            b += b;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        if (currSquare - a >= 0)
        {
            moves.push_back(currSquare - a);
            a += a;
        }
    }

    for (int i = 0; i < moves.size(); ++i)
    {
        if (targetSquare == moves[i])
        {
            return true;
        }
    }

    return false;
}
