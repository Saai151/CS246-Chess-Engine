#ifndef ABSTRACTPIECE_H
#define ABSTRACTPIECE_H

#include <vector>
#include "Board.h"
#include <string>
#include <iostream>
#include "Location.h"
#include "Color.h"

using namespace std;

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
    bool isFirst;
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

        std::vector<Location> getValidMoves(){

        }

        void Move(int targetSquare, vector<AbstractPiece*> boardState){
            if (validMove(targetSquare, boardState)){
                this->setSquare(targetSquare);
            }
        }

        bool validMove(int targetSquare, vector<AbstractPiece*> boardState){
            ChessColor targetColor;
            if (this->getPieceColor() == ChessColor::White){
                targetColor = ChessColor::Black;
            } else{
                 targetColor = ChessColor::White;
            }
            int currSquare = this->getSquare();
            bool occupied1 = false;
            bool occupied2 = false;
            std::vector<int> moves;
            
            for ( auto piece : boardState) {
                if (piece->getSquare() == currSquare + 8) {
                    occupied1 = true;
                }
                else if (piece->getSquare() == currSquare + 16){
                    occupied2 = true;
                }
                else if(piece->getSquare() == currSquare + 9 && piece->getPieceColor() == targetColor){
                    moves.push_back(currSquare + 9);
                }
                else if (piece->getSquare() == currSquare - 9 && piece->getPieceColor() == targetColor){
                    moves.push_back(currSquare - 9);
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