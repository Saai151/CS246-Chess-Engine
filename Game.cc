#include "Game.h"

Game::Game(Player* white, Player* black, Board* board) : white{white}, black{black}, board{board} {
    currentTurn = white;
    white->attachBoardToPieces(board);
    black->attachBoardToPieces(board);
}

void Game::makeMove() {
    /*if (board->isStalemate(currentTurn->getColor())) {
        std::cout << "STALEMATE" << std::endl; 
    }*/
    try {
        currentTurn->move(board);
    } catch (std::invalid_argument& e) {
        std::cout << "INVALID MOVE: " << e.what() << std::endl;
        return;
    }

    if (currentTurn == white) currentTurn = black;
    else currentTurn = white;

  //  if (board->isCheckmate(currentTurn->getColor())) {
  //      std::cout << (currentTurn->getColor() == ChessColor::White ? "White" : "Black") << " IS IN CHECKMATE" << std::endl; 
  //  }

    // if (board->isStalemate(currentTurn->getColor())) {
    //     std::cout << "STALEMATE" << std::endl; 
    // }
}

Game::~Game() {
    //delete white;
    //delete black;
    //delete board;
}