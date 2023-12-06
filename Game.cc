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
        if (otherTurn == ChessColor::White)
        {
            cout << "Black wins! Checkmate!" << endl;
            *blackScore += 1;
        }
        else
        {
            cout << "White wins! Checkmate!" << endl;
            *whiteScore += 1;
        }
    }

    if (board->isStalemate(otherTurn))
    {
        cout << "Stalemate Draw!" << endl;
        *blackScore += 0.5;
        *whiteScore += 0.5;
        return true;
    }
    if (board->isCheckmate(currentTurn->getColor())) {
        if (currentTurn->getColor() == ChessColor::White) {
            *blackScore += 1;
        } else {
            *whiteScore += 1;
        }
        return true;
   }
    try {
        currentTurn->move(board);
    }
    catch (std::invalid_argument &e)
    {
        return false;
    }

    if (board->isCheckmate(otherTurn))
    {
        if (otherTurn== ChessColor::White)
        {
            cout << "Black wins! Checkmate!" << endl;
            *blackScore += 1;
        }
        else
        {
            cout << "White wins! Checkmate!" << endl;
            *whiteScore += 1;
        }
        return true;
    }

    if (board->isInCheck(ChessColor::White).size() > 0) {
        cout << "White is in check." << endl;
    } else if (board->isInCheck(ChessColor::Black).size() > 0) {
        cout << "Black is in check." << endl;
    }

    if (currentTurn == white)
        currentTurn = black;
    else
        currentTurn = white;

    return false;
}