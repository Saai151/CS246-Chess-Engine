#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "AbstractPiece.h"

class DisplayObserver;
class DisplayAggregator;

class Square {
    private:
        Location location;
        ChessColor squareColor;
        AbstractPiece* occupant;
        DisplayAggregator* g;
    public:
        Square(Location location, ChessColor squareColor, AbstractPiece* occupant, DisplayAggregator* g);
        bool isOccupied() const;
        ChessColor getColor() const;
        Location getLocation() const;
        void setOccupant(AbstractPiece* occupant);
        void reset();
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
