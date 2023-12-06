#include "TextDisplay.h"

TextDisplay::TextDisplay() {
    display.reserve(64);
}

void TextDisplay::render() {
    for (size_t i = 0; i < 64; ++i) {
        if (i == 0) std::cout << "8 ";
        if (i == 8) std::cout << "7 ";
        if (i == 16) std::cout << "6 ";
        if (i == 24) std::cout << "5 ";
        if (i == 32) std::cout << "4 ";
        if (i == 40) std::cout << "3 ";
        if (i == 48) std::cout << "2 ";
        if (i == 56) std::cout << "1 ";

        std::cout << display[i];

        if ((i + 1) % 8 == 0) {
            std::cout << '\n'; // Start a new line after printing 8 squares (end of a row)
        }
    }

    std::cout << "\n" << "  abcdefgh" << std::endl;
}

void TextDisplay::handleStateChange(Square* s) {
    display[s->getLocation().getIndex()] = s->printable()[0];
}
