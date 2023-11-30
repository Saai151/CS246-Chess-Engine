#ifndef ABSTRACTPIECE_H
#define ABSTRACTPIECE_H

#include "Board.h"
#include <string>
#include "Square.h"


enum class pieceColor{
    White, Black
};

class AbstractPiece{
    private:
        int squareIndex;
        pieceColor color;
        std::string name;
    public:
        AbstractPiece(int squareIndex, pieceColor color, std::string name):  squareIndex{squareIndex}, color{color}, name{name}{}
        pieceColor getPieceColor() const{
            return color;
        }
        std::string getName(){
            return name;
        }
        int getSquare(){
            return squareIndex;
        }
        void setSquare(int index){
            squareIndex = index;
        }
};

class Pawn : public AbstractPiece{
    bool isFirst;
    public:
        Pawn(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Pawn"), isFirst{false}{}
        std::vector<Location> getValidMoves(){

        }

        void Move(int targetSquare, Board board){
            this->setSquare(targetSquare);
        }

        bool validMove(int targetSquare, Board board){
            int currSquare = this->getSquare();
            std::vector<int> moves;
            if (isFirst){
                moves.push_back(currSquare+16);
            }

            for (int i = 0; i < board.pieces.size(); ++i){
                if (board.pieces[i].getSquare() && board.pieces[i].getPieceColor() == this->getPieceColor()){

                }
            }
        }

};

class Queen : public AbstractPiece{
    public:
        Queen(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Queen"){}

        friend std::ostream& operator<<(std::ostream& out, const Queen& queen) {
        if (queen.getPieceColor() == pieceColor::White){
            out << "Q";
        }
        else {
            out << "q";
        }
        return out;
    }

};

class King : public AbstractPiece{
    public:
        King(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "King"){}


};

class Knight : public AbstractPiece{
    public:
         Knight(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Knight"){}


};

class Rook : public AbstractPiece{
    public:
        Rook(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Rook"){}

};

class Bishop : public AbstractPiece{
    public:
        Bishop(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Bishop"){}

};

#endif