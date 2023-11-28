#include <string>
#include "Square.h"

enum class pieceColor{
    White, Black
};

class AbstractPiece{
    private:
        pieceColor color;
        std::string name;
        Square currSquare;
    public:
        AbstractPiece(Square currSquare, pieceColor color, std::string name):  currSquare{currSquare}, color{color}, name{name}{}
        pieceColor getPieceColor(){
            return color;
        }
        std::string getName(){
            return name;
        }
        Square getSquare(){
            return currSquare;
        }
        void setSquare(Square square){
            currSquare = square;
        }

        virtual std::vector<Location> getValidMoves() const = 0;

};

class Pawn : public AbstractPiece{
    Pawn(Square currSquare, pieceColor color): AbstractPiece(currSquare, color, "Pawn"){}

};

class Queen : public AbstractPiece{
    Queen(Square currSquare, pieceColor color): AbstractPiece(currSquare, color, "Queen"){}

};

class King : public AbstractPiece{
    King(Square currSquare, pieceColor color): AbstractPiece(currSquare, color, "King"){}

};

class Knight : public AbstractPiece{
    Knight(Square currSquare, pieceColor color): AbstractPiece(currSquare, color, "Knight"){}

};

class Rook : public AbstractPiece{
    Rook(Square currSquare, pieceColor color): AbstractPiece(currSquare, color, "Rook"){}

};

class Bishop : public AbstractPiece{
    Bishop(Square currSquare, pieceColor color): AbstractPiece(currSquare, color, "Bishop"){}

};