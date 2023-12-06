#include "Game.h"
#include "window.h"
#include "TextDisplay.h"
#include <iostream>
#include <string>
#include <cstring>

class EmptyDisplay: public DisplayObserver {
    void handleStateChange(Square* s) override {
        return;
    }
};

int main(){
    srand(static_cast<unsigned int>(time(0))); // for generating random computer moves.
    float whiteScore = 0;
    float blackScore = 0;
    Player* white = nullptr;
    Player* black = nullptr;
    Game* game = nullptr;
    Xwindow w = Xwindow();
    GraphicsDisplay gd(w);
    TextDisplay td;

    std::vector<DisplayObserver*> displays = {&gd, &td}; // add back graphics display later.
    DisplayAggregator allDisplays = DisplayAggregator(displays);

    Board* board = nullptr;
    std::string command;

    while (std::cin >> command) {
        if (white == nullptr) {
            white = new HumanPlayer(ChessColor::White);
        }
        if (black == nullptr) {
            black = new HumanPlayer(ChessColor::Black);
        }
        if (board == nullptr) {
            board = new Board(white->pieces, black->pieces, &allDisplays);
        }

        // Refresh screen in case of white space.
        for (Square s : board->squares) {
            s.refresh();
        }

        if (command == "setup" && game == nullptr) {
            board->reset();
            white->clearPieces();
            black->clearPieces();
            std::string setupCommand = "";
            while (std::cin >> setupCommand) {
                if (setupCommand == "+") {
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
                } else if (setupCommand == "-") {
                    std::string location;
                    std::cin >> location;
                    int parsedLocation = parseLocation(location);
                    board->resetSquare(parsedLocation);
                } else if (setupCommand == "done") {
                    if (board->validState()) break;
                }

                allDisplays.render();
            }
        } else if (command == "game") {
            std::string whitePlayerType, blackPlayerType;
            std::cin >> whitePlayerType >> blackPlayerType;
            
            if (whitePlayerType == "computer[1]") {
                ComputerPlayer_1* newWhite = new ComputerPlayer_1(std::move(*white)); //change once more levels
                                                                                      //are implemented.
                delete white;
                //oldWhite = white;
                white = newWhite;
            } else if (whitePlayerType == "computer[2]") {
                ComputerPlayer_2* newWhite = new ComputerPlayer_2(std::move(*white)); //change once more levels
                                                                                      //are implemented.
                delete white;
                //oldWhite = white;
                white = newWhite;
            } else if (whitePlayerType == "computer[3]") {
                ComputerPlayer_3* newWhite = new ComputerPlayer_3(std::move(*white)); //change once more levels
                                                                                      //are implemented.
                delete white;
                white = newWhite;
            }

            if (blackPlayerType == "computer[1]") {
                ComputerPlayer_1* newBlack = new ComputerPlayer_1(std::move(*black));
                
                delete black;
                //oldBlack = black;
                black = newBlack;
            } else if (blackPlayerType == "computer[2]") {
                ComputerPlayer_2* newBlack = new ComputerPlayer_2(std::move(*black));

                delete black;
                //oldBlack = black;
                black = newBlack;
            } else if (blackPlayerType == "computer[3]") {
                ComputerPlayer_3* newBlack = new ComputerPlayer_3(std::move(*black));
                delete black;
                black = newBlack;
            }

            game = new Game(white, black, board);
        } else if (command == "move") {
            bool isOver = game->makeMove(&whiteScore, &blackScore);
            if (isOver) {
                delete game;
                game = nullptr;

                delete white;
                white = nullptr;

                delete black;
                black = nullptr;

                delete board;
                board = nullptr;
            }
        } else if (command == "color") {
            std::string t = "";
            std::cin >> t;
            if (t == "white") {
                game->setTurn(ChessColor::White);
            } else if (t == "black") {
                game->setTurn(ChessColor::Black);
            }
        } else if (command == "resign") {
            if (game->turn() == ChessColor::White) {
                blackScore += 1;
            } else {
                whiteScore += 1;
            }

            delete game;
            game = nullptr;

            delete white;
            white = nullptr;

            delete black;
            black = nullptr;

            delete board;
            board = nullptr;
        }

        allDisplays.render();
    }

    if (std::cin.eof()) {
        std::cout << "Final Score:" << std::endl;
        std::cout << "White: " << whiteScore << std::endl;
        std::cout << "Black: " << blackScore << std::endl;
    }

    delete game;
    delete white;
    delete black;
    delete board;
}