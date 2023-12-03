#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "AbstractPiece.h"

class DisplayObserver;

class Square {
    private:
        Location location;
        ChessColor squareColor;
        AbstractPiece* occupant;
        DisplayObserver* g;
    public:
        Square(Location location, ChessColor squareColor, AbstractPiece* occupant, DisplayObserver* g);
        bool isOccupied() const;
        ChessColor getColor() const;
        Location getLocation() const;
        void setOccupant(AbstractPiece* occupant);
        void reset();
        AbstractPiece* getOccupant() const;
};

class DisplayObserver {
    public:
        virtual void handleStateChange(Square* s) = 0;
};

std::ostream& operator<<(std::ostream& out, const Square& square);

#endif
