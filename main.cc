#include "Game.h"
#include "window.h"
#include <iostream>
#include <string>

class EmptyDisplay: public DisplayObserver {
    void handleStateChange(Square* s) override {
        return;
    }
};

AbstractPiece* parsePieceSymbol(char p, ChessColor color, PieceRemovedObserver* owner) {
    if (tolower(p) == 'p') return new Pawn(color, owner);
    else if (tolower(p) == 'q') return new Queen(color, owner);
    else if (tolower(p) == 'k') return new King(color, owner);
    else if (tolower(p) == 'n') return new Knight(color, owner);
    else if (tolower(p) == 'r') return new Rook(color, owner);
    else return new Bishop(color, owner);
}

int main(){
    Player* white = new HumanPlayer(ChessColor::White);
    Player* black = new HumanPlayer(ChessColor::Black);
    Game* game = nullptr;
    Xwindow w = Xwindow();
    GraphicsDisplay gd(w);
    Board* board = new Board(white, black, &gd);
    std::string command;

    while (std::cin >> command) {
        if (command == "+") {
            std::string piece, location;
            std::cin >> piece >> location;

            ChessColor color;
            Player* owner;
            AbstractPiece* newPiece;

            isupper(piece[0]) ? color = ChessColor::White : color = ChessColor::Black;
            isupper(piece[0]) ? owner = white : owner = black;

            newPiece = parsePieceSymbol(piece[0], color, owner);
            owner->addPiece(newPiece);
            board->placePiece(newPiece, parseLocation(location));
            
        } else if (command == "game") {
            std::string whitePlayerType, blackPlayerType;
            std::cin >> whitePlayerType >> blackPlayerType;
            
            if (whitePlayerType != "human") {
                ComputerPlayer_1* newWhite = new ComputerPlayer_1(std::move(*white)); //change once more levels
                                                                                      //are implemented.
                delete white;
                white = newWhite;
            }

            if (blackPlayerType != "human") {
                ComputerPlayer_1* newBlack = new ComputerPlayer_1(std::move(*black));
                delete black;
                black = newBlack;
            }

            game = new Game(white, black, board);
        } else if (command == "done") {
            break;
        } else if (command == "-") {
            std::string location;
            std::cin >> location;
            int parsedLocation = parseLocation(location);
            board->resetSquare(parsedLocation);
        } else if (command == "move") {
            game->makeMove();
        }

        std::cout << *board;
    }

    delete game;
    delete white;
    delete black;
    delete board;
}