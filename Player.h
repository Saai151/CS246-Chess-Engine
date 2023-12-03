#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include "AbstractPiece.h"

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
        virtual void move() = 0;
        virtual ~Player();
};

class HumanPlayer: public Player {
    public:
        HumanPlayer(Player&& p);
        HumanPlayer(ChessColor c);
        void move() override;
};

class ComputerPlayer: public Player {
    public:
        ComputerPlayer(Player&& p);
        ComputerPlayer(ChessColor c);
        void move() override;
};

#endif