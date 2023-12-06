#include <string>
#include <iostream>

enum class File {
    A,B,C,D,E,F,G,H
};

class Location{
    private:
        int rank; // Rank from 1 to 8
        File file; 

    public:
        Location(int rank, File file);
        File getFile();
        int getRank();
        int getIndex();
};

int fileToInt(File file);  

int parseLocation(std::string location);
