#include "Board.h"
#include "Player.h"

class Game {
    Player* white;
    Player* black;
    Player* currentTurn;
    Board* board;

    public:
        Game(Player* white, Player* black, Board* board);
        bool makeMove(float* whiteScore, float* blackScore);
        ChessColor turn();
        void setTurn(ChessColor c);
};
