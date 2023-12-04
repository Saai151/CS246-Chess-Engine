#include "TextDisplay.h"

TextDisplay::TextDisplay() {
    display.reserve(64);
}

void TextDisplay::render() {
    for (size_t i = 0; i < 64; ++i) {
        std::cout << display[i];

        if ((i + 1) % 8 == 0) {
            std::cout << '\n'; // Start a new line after printing 8 squares (end of a row)
        }
    }
}

void TextDisplay::handleStateChange(Square* s) {
    display[s->getLocation().getIndex()] = s->printable()[0];
}