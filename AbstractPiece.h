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
            if (validMove(targetSquare, board)){
                this->setSquare(targetSquare);
            }
        }

        bool validMove(int targetSquare, Board board){
            pieceColor targetColor;
            if (this->getPieceColor() == pieceColor::White){
                targetColor = pieceColor::Black;
            } else{
                 targetColor = pieceColor::White;
            }
            int currSquare = this->getSquare();
            bool occupied1 = false;
            bool occupied2 = false;
            std::vector<int> moves;
            

            for (int i = 0; i < moves.size(); ++i){
                for ( auto piece : board.pieces) {
                    if (piece.getSquare() == currSquare + 8) {
                        occupied1 = true;
                    }
                    else if (piece.getSquare() == currSquare + 16){
                        occupied2 = true;
                    }
                    else if(piece.getSquare() == currSquare + 9 && piece.getPieceColor() == targetColor){
                        moves.push_back(currSquare + 9);
                    }
                    else if (piece.getSquare() == currSquare - 9 && piece.getPieceColor() == targetColor){
                        moves.push_back(currSquare - 9);
                    }
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