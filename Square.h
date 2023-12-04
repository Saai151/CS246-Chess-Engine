#ifndef SQUARE_H
#define SQUARE_H

#include "AbstractPiece.h"

#include <iostream>

class DisplayObserver;
class DisplayAggregator;

class Square {
    Location location;
    ChessColor squareColor;
    DisplayAggregator* g;
    AbstractPiece* occupant;
    
    public:
        Square(Location location, ChessColor squareColor, AbstractPiece* occupant, DisplayAggregator* g);
        ChessColor getColor() const;
        Location getLocation() const;
        void setOccupant(AbstractPiece* occupant);
        void reset();
        bool isOccupied() const;
        AbstractPiece* getOccupant() const;
        std::string printable() const;
};

class DisplayObserver {
    public:
        virtual void handleStateChange(Square* s) = 0;
        virtual void render() {};
};


class DisplayAggregator: DisplayObserver {
    std::vector<DisplayObserver*> displays;
    
    public:
        DisplayAggregator(std::vector<DisplayObserver*> displays);
        void handleStateChange(Square* s) override;
        void render() override;
};

#endif
