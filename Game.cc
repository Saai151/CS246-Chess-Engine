#include "Game.h"

Game::Game(Player* white, Player* black, Board* board) : white{white}, black{black}, board{board} {
    currentTurn = white;
    white->attachBoardToPieces(board);
    black->attachBoardToPieces(board);
}

ChessColor Game::turn() {
    return this->currentTurn->getColor();
}

void Game::setTurn(ChessColor c) {
    if (c == ChessColor::White) {
        this->currentTurn = white;
    } else {
        this->currentTurn = black;
    }
}

bool Game::makeMove(float* whiteScore, float* blackScore) {
    if (board->isStalemate(currentTurn->getColor())) {
        *blackScore += 0.5;
        *whiteScore += 0.5;
        return true;
    }
    try {
        currentTurn->move(board);
    } catch (std::invalid_argument& e) {
        return false;
    }

    if (currentTurn == white) currentTurn = black;
    else currentTurn = white;

   if (board->isCheckmate(currentTurn->getColor())) {
        if (currentTurn->getColor() == ChessColor::White) {
            *blackScore += 1;
        } else {
            *whiteScore += 1;
        }
        return true;
   }

   return false;
}