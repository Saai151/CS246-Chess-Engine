#include "Square.h"

Square::Square(Location location, ChessColor squareColor, AbstractPiece* occupant, DisplayObserver* g)
            : location{location}, squareColor{squareColor}, occupant{occupant}, g{g} {
        g->handleStateChange(this);
    }

bool Square::isOccupied() const {
    return occupant != nullptr;
}

ChessColor Square::getColor() const {
    return squareColor;
}

Location Square::getLocation() const {
    return location; 
}

void Square::reset() {
    if (isOccupied()) {
        delete occupant;
        occupant = nullptr;
    }
    g->handleStateChange(this);
}

void Square::setOccupant(AbstractPiece* occupant) {
    if (occupant != nullptr) {
        occupant->setSquare(location.getIndex());
        delete this->occupant;
    }

    this->occupant = occupant;
    g->handleStateChange(this);
}

AbstractPiece* Square::getOccupant() const {
    return occupant;
}

std::ostream& operator<<(std::ostream& out, const Square& square) {
    if (square.isOccupied()) {
        out << square.getOccupant()->printable();
    } else {
        out << (square.getColor() == ChessColor::White ? " " : "_");
    }
    return out;
}