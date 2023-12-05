#ifndef BOARD_H
#define BOARD_H

#include "Square.h"

#include <ostream>
#include <vector>
#include <iostream>
#include <vector>


class Board: public PieceMovedObserver {    
    DisplayAggregator* g;

    bool isPieceCheckingTheKing(Square* s, AbstractPiece* king, ChessColor c);

    public:
        std::vector<Square> squares;
        Board(std::vector<AbstractPiece*> white, std::vector<AbstractPiece*> black, DisplayAggregator* g);
        void resetSquare(int index);
        void placePiece(AbstractPiece* piece, int square);
        std::vector<Square*> isInCheck(ChessColor c);
        bool isCheckmate(ChessColor c);
        bool isStalemate(ChessColor current_colour);
        bool isValidMove(AbstractPiece* target, int startLocation, int endLocation);
        bool handlePieceMoved(AbstractPiece* piece, bool overrideValidation = false) override;
        friend class GraphicsDisplay;

        virtual ~Board();
};

#endif 
