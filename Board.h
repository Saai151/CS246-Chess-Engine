#include "Square.h"
#include "AbstractPiece.h"
#include "Player.h"

#include <ostream>
#include <vector>
#include <iostream>
#include <vector>


class Board: public PieceMovedObserver {    
    public:
        Board(Player* white, Player* black);
        std::vector<Square> squares;
        Square* getSquare(int index);
        void placePiece(AbstractPiece* piece, int square);
        void handlePieceMoved(AbstractPiece* piece) override;

        virtual ~Board();
};

std::ostream& operator<<(std::ostream& out, Board& board);