#ifndef ABSTRACTPIECE_H
#define ABSTRACTPIECE_H

#include <string>
#include <iostream>
#include "Location.h"
#include "Color.h"

class PieceRemovedObserver;
class PieceMovedObserver;

class AbstractPiece {
    protected:
        ChessColor color;

    private:
        int squareIndex = -1;
        int previousSquareIndex = -1;
        std::string name;
        PieceRemovedObserver* pieceRemovedObserver;
        PieceMovedObserver* pieceMovedObserver;

    public:
        AbstractPiece(ChessColor color, std::string name, PieceRemovedObserver* pieceRemovedObserver) : 
            color{color}, name{name}, pieceRemovedObserver{pieceRemovedObserver} {}

        ChessColor getPieceColor() const{
            return color;
        }

        std::string getName(){
            return name;
        }

        void attachMoveObserver(PieceMovedObserver* board) {
            pieceMovedObserver = board;
        }

        int getSquare() {
            return squareIndex;
        }

        int getPreviousSquare() {
            return previousSquareIndex;
        }

        void setSquare(int index){
            squareIndex = index;
        }

        virtual std::string printable() const = 0;
        virtual void move(int newIndex);
        virtual ~AbstractPiece();
};

class PieceRemovedObserver {
    public:
        virtual void handlePieceRemoved(AbstractPiece* p) = 0;
};

class PieceMovedObserver {
    public:
        virtual void handlePieceMoved(AbstractPiece* p) = 0;
};


class Pawn : public AbstractPiece{
    public:
        Pawn(ChessColor color, PieceRemovedObserver* pieceRemovedObserver) : 
            AbstractPiece(color, "Pawn", pieceRemovedObserver) {}
        
        std::string printable() const override {
            if (getPieceColor() == ChessColor::White){
                return "P";
            }
            else {
                return "p";
            }
        }
};

class Queen : public AbstractPiece{
    public:
        Queen(ChessColor color, PieceRemovedObserver* pieceRemovedObserver) : 
                    AbstractPiece(color, "Queen", pieceRemovedObserver) {}

        std::string printable() const override {
            if (getPieceColor() == ChessColor::White){
                return "Q";
            }
            else {
                return "q";
            }
        }
};

class King : public AbstractPiece{
    public:
        King(ChessColor color, PieceRemovedObserver* pieceRemovedObserver) : 
            AbstractPiece(color, "King", pieceRemovedObserver) {}

        std::string printable() const override {
            if (getPieceColor() == ChessColor::White){
                return "K";
            }
            else {
                return "k";
            }
        }
};

class Knight : public AbstractPiece{
    public:
        Knight(ChessColor color, PieceRemovedObserver* pieceRemovedObserver) : 
            AbstractPiece(color, "Knight", pieceRemovedObserver) {}
        
        std::string printable() const override {
            if (getPieceColor() == ChessColor::White){
                return "N";
            }
            else {
                return "n";
            }
        }
};

class Rook : public AbstractPiece{
    public:
        Rook(ChessColor color, PieceRemovedObserver* pieceRemovedObserver) : 
            AbstractPiece(color, "Rook", pieceRemovedObserver) {}

        std::string printable() const override {
            if (getPieceColor() == ChessColor::White){
                return "R";
            }
            else {
                return "r";
            }
        }
};

class Bishop : public AbstractPiece{
    public:
        Bishop(ChessColor color, PieceRemovedObserver* pieceRemovedObserver) : 
            AbstractPiece(color, "Bishop", pieceRemovedObserver) {}

        std::string printable() const override {
            if (getPieceColor() == ChessColor::White){
                return "B";
            }
            else {
                return "b";
            }
        }
};

#endif