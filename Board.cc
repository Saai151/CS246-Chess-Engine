#include "Board.h"

Board::Board(Player* white, Player* black, DisplayAggregator* g) {
    std::vector<AbstractPiece*> selectedPieces;
    squares.reserve(64); // Reserve space for 64 squares

    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            bool isWhite = (file + rank) % 2 != 0;
            ChessColor currColor = (isWhite) ? ChessColor::White : ChessColor::Black;
            Location loc(rank, static_cast<File>(file));
            Square mySquare(loc, currColor, nullptr, g);
            squares.push_back(mySquare);
        }
    }

    /* Place down white pieces */
    selectedPieces = white->getPieces("Pawn");
    for (int i = 48; i < 56; i++) {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = white->getPieces("Rook");
    squares[63].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[56].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = white->getPieces("Knight");
    squares[62].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[57].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = white->getPieces("Bishop");
    squares[61].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[58].setOccupant(selectedPieces.back());

    selectedPieces = white->getPieces("King");
    squares[60].setOccupant(selectedPieces.back());

    selectedPieces = white->getPieces("Queen");
    squares[59].setOccupant(selectedPieces.back());

    /* Place down black pieces */
    selectedPieces = black->getPieces("Pawn");
    for (int i = 8; i < 16; i++) {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = black->getPieces("Rook");
    squares[0].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[7].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = black->getPieces("Knight");
    squares[1].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[6].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = black->getPieces("Bishop");
    squares[2].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[5].setOccupant(selectedPieces.back());

    selectedPieces = black->getPieces("King");
    squares[4].setOccupant(selectedPieces.back());

    selectedPieces = black->getPieces("Queen");
    squares[3].setOccupant(selectedPieces.back());
}

bool Board::isInCheck(ChessColor c) {
    AbstractPiece* king;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c) {
            king = s.getOccupant();
        }
    }

    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() != c && s.getOccupant()->validMove(king->getSquare())) {
            return true;
        }
    }

    return false;
}

bool Board::isCheckmate(ChessColor c) {
    AbstractPiece* king;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c) {
            king = s.getOccupant();
        }
    }

    bool canMakeMove = true;
    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() != c && s.getOccupant()->validMove(king->getSquare())) {
            for (int move : king->allMoves()) {
                canMakeMove = true;

                for (auto& s_ : squares) {
                    if (s_.isOccupied() && s_.getOccupant()->getPieceColor() != c && s_.getOccupant()->validMove(move)) {
                        canMakeMove = false;
                        break;
                    }
                }

                if (canMakeMove) return false; // not in checkmate
            }
        }
    }

    // CHECK IF WE CAN MOVE SOME OTHER PIECE IN FRONT OF THE KING

    return true;
}

bool Board::isStalemate() {
    if (isInCheck(ChessColor::White) || isInCheck(ChessColor::Black)) return false;

    for (auto& s : squares) {
        if (s.isOccupied() && s.getOccupant()->allMoves().size() != 0) {
            return false;
        }
    }

    return true;
}

void Board::placePiece(AbstractPiece* piece, int square) {
    if (squares[square].isOccupied()) {
        squares[square].reset();
    }
    squares[square].setOccupant(piece);
}

void Board::resetSquare(int index) {
    squares[index].reset();
}

bool Board::handlePieceMoved(AbstractPiece* piece) {
    if (isValidMove(piece, piece->getPreviousSquare(), piece->getSquare())) {
        squares[piece->getPreviousSquare()].setOccupant(nullptr);
        squares[piece->getSquare()].setOccupant(piece); 
        // Validate isChecked, pieceHopping, isCheckMated, inBoardArea
        return true;
    }
    
    return false;
}

bool Board::isValidMove(AbstractPiece* target, int startLocation, int endLocation) {
    std::cout << "HERE 1" << std::endl;
    std::cout << startLocation << ", " << endLocation << std::endl;
    if (endLocation < 0 || endLocation >= 64){
        throw std::invalid_argument("invalid target square");
    }

     ChessColor captureColor;

    
    if (target->getPieceColor() == ChessColor::Black){
        captureColor = ChessColor::White;
    } else{
        captureColor = ChessColor::Black;
    }

    if (squares[endLocation].isOccupied() && squares[endLocation].getOccupant()->getPieceColor() != captureColor) {
        return false;
    }

    if(target->getName() == "Pawn"){
        if (endLocation == startLocation + 8 || endLocation == startLocation - 8){
            if (!squares[endLocation].isOccupied()){
                return true;
            }
        } else if (endLocation == startLocation + 16 || endLocation == startLocation - 16){
            int inBetweenSquare = (startLocation + endLocation) / 2;
            if (!(squares[endLocation].isOccupied()) && !(squares[inBetweenSquare]).isOccupied()){
                return true;
            }            
        }

        int delta = abs(endLocation - startLocation);
        std::cout << delta << std::endl;
        if (delta == 9 || delta == 7) {
            if (squares[endLocation].isOccupied() && squares[endLocation].getOccupant()->getPieceColor() == captureColor) {
                return true;
            }
        }

        return false;
    }

    else if(target->getName() == "Queen"){
        int startRank = startLocation / 8;
        int startFile = startLocation % 8;
        int endRank = endLocation / 8;
        int endFile = endLocation % 8;

        // Check if the movement is along a rank, file, or diagonal
        if ((startRank != endRank) && (startFile != endFile) && (abs(startRank - endRank) != abs(startFile - endFile))) {
            // Invalid movement for a Queen (not along a rank, file, or diagonal)
            return false;
        }

        int x = (startRank == endRank) ? 1 : ((startFile == endFile) ? 8 : ((endLocation - startLocation) / abs(endLocation - startLocation)));
        int steps = abs(endLocation - startLocation) / abs(x);

        // Check for obstacles or capture along the path
        for (int i = 1; i <= steps; ++i) {
            int index = startLocation + (i * x);
            if (index == endLocation && squares[index].isOccupied() && squares[index].getColor() == captureColor) {
                return true; // Capture possible on the last square of the path
            }
            if (squares[index].isOccupied()) {
                return false; // Obstacle found in the path
            }
        }

        return true; // No obstacles in the rank, file, or diagonal path

    }

    else if(target->getName() == "King"){
            // Check if the movement is within one square horizontally, vertically, or diagonally
            if (abs(endLocation / 8 - startLocation / 8) > 1 || abs(endLocation % 8 - startLocation % 8) > 1) {
                // Invalid movement for a King (more than one square away)
                return false;
            }

            // Calculate the number of steps (which is always 1 for the King)
            int steps = 1;

            // Check for obstacles or capture along the path
            if (squares[endLocation].isOccupied() && squares[endLocation].getColor() == captureColor) {
                return true; // Capture possible at the end location
            }

        return !squares[endLocation].isOccupied();
    }

    else if(target->getName() == "Bishop"){
        // Current location of the bishop
        int diff = abs(endLocation - startLocation);
        int x;

        // Determine if the movement is along a diagonal
        if (diff % 9 == 0) {
            x = 9;
        } else if (diff % 7 == 0) {
            x = 7;
        } else {
            return false;
        }

        int steps = diff / x;

        for (int i = 1; i <= steps; ++i) {
            int index = (startLocation < endLocation) ? startLocation + (i * x) : startLocation - (i * x);
            if (index == endLocation && squares[index].isOccupied() && squares[index].getColor() == captureColor){
                return true;
            }
            if (squares[index].isOccupied()) {
                return false; 
            }
        }

        return true;
        
    }
    else if(target->getName() == "Rook"){
        int diff = abs(endLocation - startLocation);
        int x = 0;

        // Determine if the movement is along a diagonal
        if (diff % 8 == 0) {
            x = 8;
        } else if (diff % 1 == 0) {
            x = 1;
        } else {
            return false;
        }

        int steps = diff / x;

        for (int i = 1; i <= steps; ++i) {
            int index = (startLocation < endLocation) ? startLocation + (i * x) : startLocation - (i * x);
            if (index == endLocation && squares[index].isOccupied() && squares[endLocation].getColor() == squares[startLocation].getColor()){
                return true;
            }
            if (squares[index].isOccupied()) {
                return false; 
            }
        }

        return true;

    }
    else if(target->getName() == "Knight"){

        if (squares[endLocation].isOccupied() && squares[endLocation].getColor() == captureColor) {
            return true; // Capture possible at the end location
        }

        return !squares[endLocation].isOccupied();
    }

    cout << "board validation didn't work" << std::endl;
    return false;
}

Board::~Board() {}