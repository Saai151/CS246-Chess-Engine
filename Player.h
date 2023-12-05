#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include "AbstractPiece.h"
#include "Square.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
//#include <random>

class Player: public PieceRemovedObserver {
    ChessColor c;

    public:
        std::vector<AbstractPiece*> pieces;

    public:
        Player(Player&& p);
        Player(ChessColor c);

        void addPiece(AbstractPiece* piece);
        void clearPieces();

        void handlePieceRemoved(AbstractPiece* p) override;
        void attachBoardToPieces(PieceMovedObserver* board);

        ChessColor getColor();
        virtual void move(Board* board = nullptr) = 0;
        virtual ~Player();
};

class HumanPlayer: public Player {
    public:
        HumanPlayer(Player&& p);
        HumanPlayer(ChessColor c);
        void move(Board* b = nullptr) override;
};

class ComputerPlayer_1: public Player {
    public:
        ComputerPlayer_1(Player&& p);
        ComputerPlayer_1(ChessColor c);
        void move(Board* b = nullptr) override;
};

class ComputerPlayer_2: public Player {
    public:
        ComputerPlayer_2(Player&& p);
        ComputerPlayer_2(ChessColor c);
        void move(Board* b = nullptr) override;
};

class ComputerPlayer_3: public Player {
    bool canBeCaptured(AbstractPiece* curr_piece, Board* b);
    bool checkFromMove(AbstractPiece* curr_piece, Board* b, int move);
    public:
        ComputerPlayer_3(Player&& p);
        ComputerPlayer_3(ChessColor c);
        void move(Board* b = nullptr) override;
};

#endif
