#ifndef BOARD_H
#define BOARD_H

#include "Square.h"

#include <ostream>
#include <vector>
#include <iostream>
#include <vector>

class Board : public PieceMovedObserver
{
    DisplayAggregator *g;

    bool isPieceCheckingTheKing(Square s, AbstractPiece *king, ChessColor c);
    bool blockCheck(AbstractPiece *curr_piece, AbstractPiece *king, int blocking_move);

public:
    std::vector<Square> squares;
    Board(std::vector<AbstractPiece *> white, std::vector<AbstractPiece *> black, DisplayAggregator *g, bool hardCode = true);
    void resetSquare(int index);
    void reset();
    void placePiece(AbstractPiece *piece, int square);
    std::vector<AbstractPiece *> isInCheck(ChessColor c);
    bool isInCheck2(AbstractPiece *king, int move);
    bool isCheckmate(ChessColor c);
    bool isStalemate(ChessColor current_colour);
    bool validState();
    bool isValidMove(AbstractPiece *target, int startLocation, int endLocation);
    bool handlePieceMoved(AbstractPiece *piece, bool overrideValidation = false) override;
    friend class GraphicsDisplay;

    virtual ~Board();
};

#endif
