#include "Game.h"

Game::Game(Player *white, Player *black, Board *board) : white{white}, black{black}, board{board}
{
    currentTurn = white;
    white->attachBoardToPieces(board);
    black->attachBoardToPieces(board);
}

ChessColor Game::turn()
{
    return this->currentTurn->getColor();
}

void Game::setTurn(ChessColor c)
{
    if (c == ChessColor::White)
    {
        this->currentTurn = white;
    }
    else
    {
        this->currentTurn = black;
    }
}

bool Game::makeMove(float *whiteScore, float *blackScore)
{
    ChessColor otherTurn = ((currentTurn->getColor() == ChessColor::Black) ? ChessColor::White : ChessColor::Black);
    if (board->isCheckmate(otherTurn))
    {
        std::cout << "Checkmate" << std::endl;
        if (currentTurn->getColor() == ChessColor::White)
        {
            *blackScore += 1;
        }
        else
        {
            *whiteScore += 1;
        }
        return true;
    }

    if (board->isStalemate(otherTurn))
    {
        *blackScore += 0.5;
        *whiteScore += 0.5;
        return true;
    }
<<<<<<< HEAD
    if (board->isCheckmate(currentTurn->getColor())) {
        if (currentTurn->getColor() == ChessColor::White) {
            *blackScore += 1;
        } else {
            *whiteScore += 1;
        }
        return true;
   }
    try {
=======

    try
    {
>>>>>>> 659f63a5b2f70bc4a15c4a7e443bf3938e863d25
        currentTurn->move(board);
    }
    catch (std::invalid_argument &e)
    {
        return false;
    }

<<<<<<< HEAD
    if (currentTurn == white) currentTurn = black;
    else currentTurn = white;

   return false;
}
=======
    if (board->isCheckmate(otherTurn)) {
        cout << "CheckMated";
    }
    if (board->isCheckmate(otherTurn))
    {
        if (currentTurn->getColor() == ChessColor::White)
        {
            *blackScore += 1;
        }
        else
        {
            *whiteScore += 1;
        }
        return true;
    }

    if (currentTurn == white)
        currentTurn = black;
    else
        currentTurn = white;

    return false;
}
>>>>>>> 659f63a5b2f70bc4a15c4a7e443bf3938e863d25
