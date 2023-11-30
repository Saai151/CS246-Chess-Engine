#ifndef ABSTRACTPIECE_H
#define ABSTRACTPIECE_H

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
    public:
        Pawn(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Pawn"){}
        std::vector<Location> getValidMoves(){

        }

        void makeMove(Square targetSquare){

        }

        friend std::ostream& operator<<(std::ostream& out, const Pawn& pawn) {
        if (pawn.getPieceColor() == pieceColor::White){
            out << "P";
        }
        else {
            out << "p";
        }
        return out;
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

        friend std::ostream& operator<<(std::ostream& out, const King& king) {
        if (king.getPieceColor() == pieceColor::White){
            out << "K";
        }
        else {
            out << "k";
        }
        return out;
    }

};

class Knight : public AbstractPiece{
    public:
         Knight(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Knight"){}

         friend std::ostream& operator<<(std::ostream& out, const Knight& knight) {
        if (knight.getPieceColor() == pieceColor::White){
            out << "Kn";
        }
        else {
            out << "kn";
        }
        return out;
    }

};

class Rook : public AbstractPiece{
    public:
        Rook(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Rook"){}
        friend std::ostream& operator<<(std::ostream& out, const Rook& rook) {
        if (rook.getPieceColor() == pieceColor::White){
            out << "R";
        }
        else {
            out << "r";
        }
        return out;
    }

};

class Bishop : public AbstractPiece{
    public:
        Bishop(int squareIndex, pieceColor color): AbstractPiece(squareIndex, color, "Bishop"){}

        friend std::ostream& operator<<(std::ostream& out, const Bishop& bishop) {
        if (bishop.getPieceColor() == pieceColor::White){
            out << "B";
        }
        else {
            out << "b";
        }
        return out;
    }
};

#endif