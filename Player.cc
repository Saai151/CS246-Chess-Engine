#include "Player.h"

Player::~Player() {
    std::vector<AbstractPiece*> shallow = pieces;
    for (auto& p : shallow) {
        delete p;
    }
}

Player::Player(ChessColor c) : c{c} {
    AbstractPiece* p;

    p = new Rook(c, this);
    pieces.push_back(p);

    p = new Knight(c, this);
    pieces.push_back(p);

    p = new Bishop(c, this);
    pieces.push_back(p);

    p = new Queen(c, this);
    pieces.push_back(p);

    p = new King(c, this);
    pieces.push_back(p);

    p = new Bishop(c, this);
    pieces.push_back(p);

    p = new Knight(c, this);
    pieces.push_back(p);

    p = new Rook(c, this);
    pieces.push_back(p);

    for (int i = 0; i < 8; i++) {
        p = new Pawn(c, this);
        pieces.push_back(p);
    }
}

void Player::clearPieces() {
    pieces.clear();
}

Player::Player(Player&& p) : c{p.getColor()} {
    addPieces(p.getPieces("Pawn"));
    addPieces(p.getPieces("Rook"));
    addPieces(p.getPieces("Knight"));
    addPieces(p.getPieces("Bishop"));
    addPieces(p.getPieces("King"));
    addPieces(p.getPieces("Queen"));

    p.clearPieces();
}

ChessColor Player::getColor() { 
    return c; 
}

void Player::addPieces(std::vector<AbstractPiece*> pieces) {
    auto it = std::next(pieces.begin(), pieces.size());
    std::move(pieces.begin(), it, std::back_inserter(this->pieces));
}

std::vector<AbstractPiece*> Player::getPieces(std::string type) {
    std::vector<AbstractPiece*> result;

    for (auto& p : pieces) {
        if (p->getName() == type) result.push_back(p);
    }

    return result;
}

void Player::addPiece(AbstractPiece* piece) {
    pieces.push_back(piece);
}

void Player::handlePieceRemoved(AbstractPiece* piece) {
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i]->getSquare() == piece->getSquare()) {
            pieces.erase(pieces.begin() + i);
            return;
        }
    }
}

void Player::attachBoardToPieces(PieceMovedObserver* board) {
    for (auto& p : pieces) {
        p->attachMoveObserver(board);
    }
}

HumanPlayer::HumanPlayer(ChessColor c) : Player(c) {}
HumanPlayer::HumanPlayer(Player&& p) : Player(std::move(p)) {}

bool Player::validBoard(vector<Square> boardState, AbstractPiece* target, int endLocation){
    // Check for obstacles

    ChessColor captureColor;

    if (target->getPieceColor() == ChessColor::Black){
        captureColor == ChessColor::White;
    }
    else{
        captureColor == ChessColor::Black;
    }


    if(target->getName() == "Pawn"){
        int startLocation = target->getSquare();

        if (endLocation == startLocation + 8 || endLocation == startLocation - 8){
            if (!boardState[endLocation].isOccupied()){
                return true;
            }
        }

        else if (endLocation == startLocation + 16 || endLocation == startLocation - 16){
            int inBetweenSquare = (startLocation + endLocation) / 2;
            if (!(boardState[endLocation].isOccupied()) && !(boardState[inBetweenSquare]).isOccupied()){
                return true;
            }            
        }
        return false;
    }

    else if(target->getName() == "Queen"){
        int startLocation = target->getSquare();

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
            if (index == endLocation && boardState[index].isOccupied() && boardState[index].getColor() == captureColor) {
                return true; // Capture possible on the last square of the path
            }
            if (boardState[index].isOccupied()) {
                return false; // Obstacle found in the path
            }
        }

        return true; // No obstacles in the rank, file, or diagonal path

    }

    else if(target->getName() == "King"){
        int startLocation = target->getSquare();

            // Check if the movement is within one square horizontally, vertically, or diagonally
            if (abs(endLocation / 8 - startLocation / 8) > 1 || abs(endLocation % 8 - startLocation % 8) > 1) {
                // Invalid movement for a King (more than one square away)
                return false;
            }

            // Calculate the number of steps (which is always 1 for the King)
            int steps = 1;

            // Check for obstacles or capture along the path
            if (boardState[endLocation].isOccupied() && boardState[endLocation].getColor() == captureColor) {
                return true; // Capture possible at the end location
            }

        return !boardState[endLocation].isOccupied();
    }

    else if(target->getName() == "Bishop"){
        // Current location of the bishop
        int startLocation = target->getSquare();
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
            if (index == endLocation && boardState[index].isOccupied() && boardState[index].getColor() == captureColor){
                return true;
            }
            if (boardState[index].isOccupied()) {
                return false; 
            }
        }

        return true;
        
    }
    else if(target->getName() == "Rook"){
        int startLocation = target->getSquare();
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
            if (index == endLocation && boardState[index].isOccupied() && boardState[endLocation].getColor() == boardState[startLocation].getColor()){
                return true;
            }
            if (boardState[index].isOccupied()) {
                return false; 
            }
        }

        return true;

    }
    else if(target->getName() == "Knight"){

        if (boardState[endLocation].isOccupied() && boardState[endLocation].getColor() == captureColor) {
            return true; // Capture possible at the end location
        }

        return !boardState[endLocation].isOccupied();
    }
    cout << "board validation didn't work" << std::endl;
    return false;
    }

void HumanPlayer::move(vector<Square> boardState) {
    std::string start, end;
    std::cin >> start >> end;

    int startLocation = parseLocation(start);
    int endLocation = parseLocation(end);

    AbstractPiece* target = nullptr;
    for (auto& p : pieces) {
        if (p->getSquare() == startLocation) target = p;
    }
    if (target == nullptr) throw std::invalid_argument("Invalid start position");

    if (endLocation < 0 || endLocation >= 64){
        throw std::invalid_argument("invalid target square");
    }

    if (!validBoard(boardState, target, endLocation)){
        cout << "not board valid" << endl;
    }

    target->move(endLocation);
}

ComputerPlayer::ComputerPlayer(ChessColor c) : Player(c) {}
ComputerPlayer::ComputerPlayer(Player&& p) : Player(std::move(p)) {}

void ComputerPlayer::move(vector<Square> boardState) {

}