#include "Game.h"

Game::Game(Player* white, Player* black, Board* board) : white{white}, black{black}, board{board} {
    currentTurn = white;
    white->attachBoardToPieces(board);
    black->attachBoardToPieces(board);
}

void Game::makeMove() {
    try {
        currentTurn->move();
    } catch (std::invalid_argument& _) {
        std::cout << "NOT VALID" << std::endl;
        return;
    }

    if (!validBoard){
        std::cout << "Invalid move" << std::endl;
        // reverse the move
    }

    if (currentTurn == white) currentTurn = black;
    else currentTurn = white;

    if (board->isCheckmate(currentTurn->getColor())) {
        std::cout << (currentTurn->getColor() == ChessColor::White ? "White" : "Black") << " IS IN CHECKMATE" << std::endl; 
    }

    if (board->isStalemate()) {
        std::cout << "STALEMATE" << std::endl; 
    }
}

bool validBoard(){
    
}

Game::~Game() {
    //delete white;
    //delete black;
    //delete board;
}