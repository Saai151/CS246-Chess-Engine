#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include "AbstractPiece.h"
#include "Square.h"
#include <cstdlib>

class Player: public PieceRemovedObserver {
    ChessColor c;

    protected:
        std::vector<AbstractPiece*> pieces;

    public:
        Player(Player&& p);
        Player(ChessColor c);

        std::vector<AbstractPiece*> getPieces(std::string type);
        void addPiece(AbstractPiece* piece);
        void addPieces(std::vector<AbstractPiece*> pieces);
        void clearPieces();

        void handlePieceRemoved(AbstractPiece* p) override;
        void attachBoardToPieces(PieceMovedObserver* board);

        ChessColor getColor();
        virtual void move(vector<Square> boardState) = 0;
        bool validBoard(vector<Square> boardState, AbstractPiece *target, int endLocation);
        virtual ~Player();
};

class HumanPlayer: public Player {
    public:
        HumanPlayer(Player&& p);
        HumanPlayer(ChessColor c);
        void move(vector<Square> boardState) override;
};

class ComputerPlayer_1: public Player {
    public:
        ComputerPlayer_1(Player&& p);
        ComputerPlayer_1(ChessColor c);
        void move(vector<Square> boardState) override;
};

#endif