#ifndef BOARD_H
#define BOARD_H

#include "Player.h"

#include <ostream>
#include <vector>
#include <iostream>
#include <vector>


class Board: public PieceMovedObserver {    
    DisplayAggregator* g;

    public:
        std::vector<Square> squares;
        Board(Player* white, Player* black, DisplayAggregator* g);
        void resetSquare(int index);
        void placePiece(AbstractPiece* piece, int square);
        bool isInCheck(ChessColor c);
        bool isCheckmate(ChessColor c);
        bool isStalemate();
        bool isValidMove(AbstractPiece* target, int startLocation, int endLocation);
        bool handlePieceMoved(AbstractPiece* piece) override;
        friend class GraphicsDisplay;

        virtual ~Board();
};

#endif 
