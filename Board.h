#ifndef BOARD_H
#define BOARD_H

#include "Square.h"
#include "AbstractPiece.h"
#include "Player.h"

#include <ostream>
#include <vector>
#include <iostream>
#include <vector>


class Board: public PieceMovedObserver {    
    DisplayObserver* g;

    public:
        std::vector<Square> squares;
        Board(Player* white, Player* black, DisplayObserver* g);
        Board(Board& b); //copy constructor
        void resetSquare(int index);
        void placePiece(AbstractPiece* piece, int square);
        bool isInCheck(ChessColor c);
        bool isCheckmate(ChessColor c);
        bool isStalemate();
        bool handlePieceMoved(AbstractPiece* piece) override;
        friend std::ostream& operator<<(std::ostream& out, Board& board);
        friend class GraphicsDisplay;

        virtual ~Board();
};

std::ostream& operator<<(std::ostream& out, Board& board);

#endif 
