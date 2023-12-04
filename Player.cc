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

    target->move(endLocation);
}

ComputerPlayer_1::ComputerPlayer_1(ChessColor c) : Player(c) {}
ComputerPlayer_1::ComputerPlayer_1(Player&& p) : Player(std::move(p)) {}

void ComputerPlayer_1::move(vector<Square> boardState) {
    std::vector<AbstractPiece*> copy_pieces = pieces;
    
    while (copy_pieces.size() > 0) {
        int num_pieces = copy_pieces.size();
        int rand_index = rand() % num_pieces; // Generate random number
        cout << "Random index: " << rand_index << endl;
        AbstractPiece* curr_piece = copy_pieces[rand_index];
        cout << "Name: " << curr_piece->getName() << endl;
        // int index = 0;
        // for (AbstractPiece* cpy_p : copy_pieces) {
        //     if (index == rand_index) {
        //         curr_piece = cpy_p;
        //         break;
        //     }
        //     index++;
        // }
        // generate all moves vector all moves.
        std::vector<int>all_moves = curr_piece->allMoves();

        for (int move : all_moves) {
            if (validBoard(boardState, curr_piece, move)) {
                cout << "move: " << move << endl;
                curr_piece->move(move);
                //cout << "Works" << endl;
                return;
            }
        }
        // Else there are no valid moves for the given piece.
        // Remove piece from cpy_pices array. And keep looking.
        copy_pieces.erase(copy_pieces.begin() + rand_index);
    }
    //cout << "Didn't work" << endl;
}

ComputerPlayer_2::ComputerPlayer_2(ChessColor c) : Player(c) {}
ComputerPlayer_2::ComputerPlayer_2(Player&& p) : Player(std::move(p)) {}

void ComputerPlayer_2::move(vector<Square> boardState) {
    // How it works: 
    // Same functionality as ComputerPlayer_1 except for each valid move found, 
    // see if it checks the opposing king or captures a piece. If it does, complete
    // the move.
    // If no move is found that leads to a check or capture, choose the first piece and move that
    // is valid. i.e make the first random move available.
    std::vector<AbstractPiece*> copy_pieces = pieces;
    // For backup in case a better option is not found.
    AbstractPiece* valid_piece;
    int valid_move;
    
    while (copy_pieces.size() > 0) {
        int num_pieces = copy_pieces.size();
        int rand_index = rand() % num_pieces; // Generate random number
        //cout << "Random index: " << rand_index << endl;
        AbstractPiece* curr_piece = copy_pieces[rand_index];
        //cout << "Name: " << curr_piece->getName() << endl;
        std::vector<int>all_moves = curr_piece->allMoves();

        for (int move : all_moves) {
            if (validBoard(boardState, curr_piece, move)) {
                // Check if the move puts the opposing king in check.
                // Go through loop, find out index square of king.
                int opposing_king_index = -1;
                int original_square = curr_piece->getSquare();
                for (Square s : boardState) {
                    if (s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() != curr_piece->getPieceColor()) {
                        opposing_king_index = s.getOccupant()->getSquare();
                    }
                }
                // Move the piece to move.
                curr_piece->move(move);
                // try valid move to index of king 
                if (!curr_piece->validMove(opposing_king_index)) { // it is not valid move to king.
                    curr_piece->move(original_square); // Else, move it back to start location.
                } else {
                    return;
                }
                
                // Check if the move captures another piece.
                if (boardState[move].isOccupied()) {
                    curr_piece->move(move);
                    return;
                }
                valid_piece = curr_piece;
                valid_move = move;
            }
        }
        // Else there are no valid moves for the given piece.
        // Remove piece from cpy_pices array. And keep looking.
        copy_pieces.erase(copy_pieces.begin() + rand_index);
    }
    valid_piece->move(valid_move);
    //cout << "Didn't work" << endl;
}
