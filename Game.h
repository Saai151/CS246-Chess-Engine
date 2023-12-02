#include "Board.h"

class Game {
    Player* white;
    Player* black;
    Player* currentTurn;
    Board* board;

    public:
        Game(Player* white, Player* black, Board* board);
        void makeMove();
        ~Game();
};