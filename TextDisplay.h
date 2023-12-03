#include "Square.h"

class TextDisplay: public DisplayObserver {
    std::vector<char> display;


    public:
        TextDisplay();
        void render() override;
        void handleStateChange(Square* s) override;
};