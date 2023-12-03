#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "AbstractPiece.h"

class Square {
    private:
        Location location;
        ChessColor squareColor;
        AbstractPiece* occupant;
    public:
        Square(Location location, ChessColor squareColor, AbstractPiece* occupant);
        bool isOccupied() const;
        ChessColor getColor() const;
        Location getLocation() const;
        void setOccupant(AbstractPiece* occupant);
        void reset();
        AbstractPiece* getOccupant() const;
};

std::ostream& operator<<(std::ostream& out, const Square& square);

#endif
