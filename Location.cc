#include "Location.h"

Location::Location(int rank, File file) : rank{rank}, file{file} {}

File Location::getFile() {
    return this->file;
}

int Location::getRank() {
    return this->rank;
}

int Location::getIndex() {
    int row = getRank();
    int col;

    if (file == File::A) col = 0;
    else if (file == File::B) col = 1;
    else if (file == File::C) col = 2;
    else if (file == File::D) col = 3;
    else if (file == File::E) col = 4;
    else if (file == File::F) col = 5;
    else if (file == File::G) col = 6;
    else if (file == File::H) col = 7;

    return 64 - ((row * 8) + (8 - col));
}

int parseLocation(std::string location) {
    int col;
    int row = location[1] - 48 - 1;

    if (location[0] == 'a') col = 0;
    else if (location[0] == 'b') col = 1;
    else if (location[0] == 'c') col = 2;
    else if (location[0] == 'd') col = 3;
    else if (location[0] == 'e') col = 4;
    else if (location[0] == 'f') col = 5;
    else if (location[0] == 'g') col = 6;
    else if (location[0] == 'h') col = 7;

    return 64 - ((row * 8) + (8 - col));
}

int fileToInt(File file) {
    int col;
    if (file == File::A) col = 0;
    else if (file == File::B) col = 1;
    else if (file == File::C) col = 2;
    else if (file == File::D) col = 3;
    else if (file == File::E) col = 4;
    else if (file == File::F) col = 5;
    else if (file == File::G) col = 6;
    else if (file == File::H) col = 7;
    return col;
}
