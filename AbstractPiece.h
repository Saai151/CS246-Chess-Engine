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
    bool isFirst = true;
    bool lastMoveWasFirstMove = false;
    std::string name;
    PieceRemovedObserver *pieceRemovedObserver;
    PieceMovedObserver *pieceMovedObserver;

public:
    AbstractPiece(ChessColor color, std::string name, PieceRemovedObserver *pieceRemovedObserver) : color{color}, name{name}, pieceRemovedObserver{pieceRemovedObserver} {}
    AbstractPiece(AbstractPiece& p);

    bool getIsFirst() const {
        return isFirst;
    }

    PieceRemovedObserver* detachRemovedObserver() {
        PieceRemovedObserver* p = this->pieceRemovedObserver;
        this->pieceRemovedObserver = nullptr;
        return p;
    }

    void hasMoved() {
        isFirst = false;
    }

    void attachPieceRemovedObserver(PieceRemovedObserver* p) {
        this->pieceRemovedObserver = p;
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
    virtual bool validMove(int targetSquare);
    virtual std::vector<int> allMoves() = 0;
};

AbstractPiece* parsePieceSymbol(char p, ChessColor color, PieceRemovedObserver* owner);
AbstractPiece* parsePieceSymbolAndCopy(char p, AbstractPiece* toCopy);

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
        Pawn(AbstractPiece& p) : AbstractPiece(p) {};

        std::string printable() const override;
        std::vector<int> allMoves() override;
};



class Queen : public AbstractPiece
{
    public:
        Queen(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Queen", pieceRemovedObserver) {}
        Queen(AbstractPiece& p) : AbstractPiece(p) {}; 

        std::string printable() const override;
        std::vector<int> allMoves() override;
};

class King : public AbstractPiece
{
    public:
        King(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "King", pieceRemovedObserver) {}
        King(AbstractPiece& p) : AbstractPiece(p) {}; 

        std::string printable() const override;
        std::vector<int> allMoves() override;
};

class Knight : public AbstractPiece
{
    public:
        Knight(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Knight", pieceRemovedObserver) {}
        Knight(AbstractPiece& p) : AbstractPiece(p) {}; 

        std::string printable() const override;
        std::vector<int> allMoves() override;
};

class Rook : public AbstractPiece
{
    public:
        Rook(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Rook", pieceRemovedObserver) {}
        Rook(AbstractPiece& p) : AbstractPiece(p) {}; 

        std::string printable() const override;
        std::vector<int> allMoves() override;
};

class Bishop : public AbstractPiece
{
public:
    Bishop(ChessColor color, PieceRemovedObserver *pieceRemovedObserver) : AbstractPiece(color, "Bishop", pieceRemovedObserver) {}
    Bishop(AbstractPiece& p) : AbstractPiece(p) {}; 

    std::string printable() const override;
    std::vector<int> allMoves() override;
};

#endif
