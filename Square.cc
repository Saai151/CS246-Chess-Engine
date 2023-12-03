#include "Square.h"

Square::Square(Location location, ChessColor squareColor, AbstractPiece* occupant, DisplayAggregator* g)
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

std::string Square::printable() const {
    if (isOccupied()) {
        return getOccupant()->printable();
    } else {
        return (getColor() == ChessColor::White ? " " : "_");
    }
}

AbstractPiece* Square::getOccupant() const {
    return occupant;
}

DisplayAggregator::DisplayAggregator(std::vector<DisplayObserver*> displays) : displays{displays} {}

void DisplayAggregator::handleStateChange(Square* s) {
    for (auto& d : displays) {
        d->handleStateChange(s);
    }
}

void DisplayAggregator::render() {
    for (auto& d : displays) {
        d->render();
    }
}