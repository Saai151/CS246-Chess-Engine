#ifndef ABSTRACTPIECE_H
#define ABSTRACTPIECE_H

#include <vector>
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
        //virtual bool validMove(int targetSquare, vector<AbstractPiece*> boardState);
};

class PieceRemovedObserver
{
public:
    virtual void handlePieceRemoved(AbstractPiece *p) = 0;
};

class PieceMovedObserver
{
public:
    virtual void handlePieceMoved(AbstractPiece *p) = 0;
};

class Pawn : public AbstractPiece
{
    bool isFirst;

public:
    Pawn(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Pawn", pieceRemovedObserver) {}

    std::string printable() const override;

    std::vector<Location> getValidMoves()
    {
    }

    bool validMove(int targetSquare, vector<AbstractPiece *> boardState);
};

class Queen : public AbstractPiece
{
public:
    Queen(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Queen", pieceRemovedObserver) {}

    std::string printable() const override;

    bool validMove(int targetSquare, vector<AbstractPiece *> boardState);
};

class King : public AbstractPiece
{
public:
    King(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "King", pieceRemovedObserver) {}

    std::string printable() const override;

    bool validMove(int targetSquare, vector<AbstractPiece *> boardState);    
};

class Knight : public AbstractPiece
{
public:
    Knight(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Knight", pieceRemovedObserver) {}

    std::string printable() const override;
    bool validMove(int targetSquare, vector<AbstractPiece *> boardState);

};

class Rook : public AbstractPiece
{
public:
    Rook(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Rook", pieceRemovedObserver) {}

    std::string printable() const override;
    bool validMove(int targetSquare, vector<AbstractPiece *> boardState);

};

class Bishop : public AbstractPiece
{
public:
    Bishop(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Bishop", pieceRemovedObserver) {}

    std::string printable() const override;
    bool validMove(int targetSquare, vector<AbstractPiece *> boardState);

};

#endif