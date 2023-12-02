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

void HumanPlayer::move() {
    std::string start, end;
    std::cin >> start >> end;

    int startLocation = parseLocation(start);
    int endLocation = parseLocation(end);

    AbstractPiece* target = nullptr;
    for (auto& p : pieces) {
        if (p->getSquare() == startLocation) target = p;
    }
    if (target == nullptr) throw std::invalid_argument("Invalid start position");

    target->move(endLocation);
}

ComputerPlayer::ComputerPlayer(ChessColor c) : Player(c) {}
ComputerPlayer::ComputerPlayer(Player&& p) : Player(std::move(p)) {}

void ComputerPlayer::move() {

}