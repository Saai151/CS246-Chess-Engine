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

class AbstractPiece
{
protected:
    ChessColor color;

protected:
    int squareIndex = -1;
    int previousSquareIndex = -1;
    int prevPrevSquareIndex = -1;
    bool isFirst = true;
    bool lastMoveWasFirstMove = false;
    std::string name;
    PieceRemovedObserver *pieceRemovedObserver;
    PieceMovedObserver *pieceMovedObserver;

public:
    AbstractPiece(ChessColor color, std::string name, PieceRemovedObserver *pieceRemovedObserver) : color{color}, name{name}, pieceRemovedObserver{pieceRemovedObserver} {}
    AbstractPiece(const AbstractPiece &other);

    bool getIsFirst() const {
        return isFirst;
    }

    void hasMoved() {
        isFirst = false;
    }

    ChessColor getPieceColor() const
    {
        return color;
    }

    std::string getName()
    {
        return name;
    }

    void attachMoveObserver(PieceMovedObserver *board)
    {
        pieceMovedObserver = board;
    }

    int getSquare()
    {
        return squareIndex;
    }

    int getPreviousSquare()
    {
        return previousSquareIndex;
    }

    void setSquare(int index)
    {
        squareIndex = index;
    }

    void move(int newIndex);
    void revertLastMove(int newSquare, int prevSquare);
    
    virtual ~AbstractPiece();
    virtual std::string printable() const = 0;
    virtual bool validMove(int targetSquare) = 0;
    virtual std::vector<int> allMoves() = 0;
};

class PieceRemovedObserver
{
public:
    virtual void handlePieceRemoved(AbstractPiece *p) = 0;
};

class PieceMovedObserver
{
public:
    virtual bool handlePieceMoved(AbstractPiece *p, bool overrideValidation = false) = 0;
};

class Pawn : public AbstractPiece
{

    public:
        Pawn(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Pawn", pieceRemovedObserver) {}

        std::string printable() const override;
        std::vector<int> allMoves() override;
        bool validMove(int targetSquare) override;
};



class Queen : public AbstractPiece
{
    public:
        Queen(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Queen", pieceRemovedObserver) {}

        std::string printable() const override;
        std::vector<int> allMoves() override;
        bool validMove(int targetSquare) override;
};

class King : public AbstractPiece
{
    public:
        King(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "King", pieceRemovedObserver) {}

        std::string printable() const override;
        std::vector<int> allMoves() override;
        bool validMove(int targetSquare) override;
};

class Knight : public AbstractPiece
{
    public:
        Knight(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Knight", pieceRemovedObserver) {}

        std::string printable() const override;
        std::vector<int> allMoves() override;
        bool validMove(int targetSquare) override;

};

class Rook : public AbstractPiece
{
    public:
        Rook(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Rook", pieceRemovedObserver) {}

        std::string printable() const override;
        std::vector<int> allMoves() override;
        bool validMove(int targetSquare) override;
};

class Bishop : public AbstractPiece
{
public:
    Bishop(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Bishop", pieceRemovedObserver) {}

    std::string printable() const override;
    std::vector<int> allMoves() override;
    bool validMove(int targetSquare) override;
};

#endif