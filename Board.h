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
        Location(int rank, char file) : rank{rank}, file{file} {}
        File getFile(){
            return this->file;
        }
        int getRank(){
            return this->rank;
        }
};

class Square{
    private:
        Location location;
        color squareColor;
        bool occupied;
    public:
        Square(Location location, color squareColor, bool occupied) : location{location}, squareColor{squareColor}, occupied{occupied} {}
        bool isOccupied(){
            return occupied;
        }
        color getColor(){
            return squareColor;
        }
        Location getLocation(){
            return location;
        }  
};

class Board{
    private:
        Square *squares[64];
    public:
        Board();
        ~Board(){
            delete [] squares;
        }
};  