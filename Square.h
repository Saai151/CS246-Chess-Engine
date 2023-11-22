#include <iostream>


enum class File {
    A,B,C,D,E,F,G,H
};

enum class color{
    white,black
};

class Location{
    private:
        int rank;
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
};

inline std::ostream& operator<<(std::ostream& out, const Square& square) {
    out << "Square at " << square.getLocation().getRank() << static_cast<char>(square.getLocation().getFile())
        << " | Color: " << (square.getColor() == color::white ? "White" : "Black")
        << " | Occupied: " << (square.isOccupied() ? "Yes" : "No");
    return out;
}