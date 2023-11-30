#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

enum class File {
    A,B,C,D,E,F,G,H
};

enum class color{
    light,dark
};

class Location{
    private:
        int rank; // Rank from 1 to 8
        File file; 
    public:
        Location(int rank, File file) : rank{rank}, file{file} {}
        File getFile(){
            return this->file;
        }
        int getRank(){
            return this->rank;
        }
};

class Square {
    private:
        Location location;
        color squareColor;
        bool occupied;
    public:
        Square(Location location, color squareColor, bool occupied)
            : location{location}, squareColor{squareColor}, occupied{occupied} {}

        bool isOccupied() const {
            return occupied;
        }

        color getColor() const {
            return squareColor;
        }

        Location getLocation() const {
            return location; 
        }

        void reset(){
            occupied = false;
        }

};

inline std::ostream& operator<<(std::ostream& out, const Square& square) {
    out << (square.getColor() == color::light ? " " : "_");
    return out;
}

#endif