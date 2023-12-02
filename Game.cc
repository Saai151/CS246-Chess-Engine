#include "Game.h"

Game::Game(Player* white, Player* black, Board* board) : white{white}, black{black}, board{board} {
    currentTurn = white;
    white->attachBoardToPieces(board);
    black->attachBoardToPieces(board);
}

void Game::makeMove() {
    currentTurn->move();

    if (currentTurn == white) currentTurn = black;
    else currentTurn = white;
}

Game::~Game() {
    //delete white;
    //delete black;
    //delete board;
}