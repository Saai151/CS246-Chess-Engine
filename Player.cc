#include "Player.h"

Player::~Player()
{
    std::vector<AbstractPiece *> shallow = pieces;
    for (auto &p : shallow)
    {
        delete p;
    }
}

Player::Player(ChessColor c) : c{c}
{
    AbstractPiece *p;

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

    for (int i = 0; i < 8; i++)
    {
        p = new Pawn(c, this);
        pieces.push_back(p);
    }
}

Player::Player(Player &&p) : c{p.getColor()}
{
    std::vector<AbstractPiece*> pieces_ = {};

    for (AbstractPiece *p : p.pieces) {
        pieces_.push_back(p);
    }

    p.pieces.clear();
    pieces = pieces_;
}

ChessColor Player::getColor()
{
    return c;
}

void Player::addPiece(AbstractPiece *piece)
{
    pieces.push_back(piece);
}

void Player::handlePieceRemoved(AbstractPiece *piece)
{
    for (size_t i = 0; i < pieces.size(); i++)
    {
        if (pieces[i]->getSquare() == piece->getSquare())
        {
            pieces.erase(pieces.begin() + i);
            return;
        }
    }
}

void Player::attachBoardToPieces(PieceMovedObserver *board)
{
    for (auto &p : pieces)
    {
        p->attachMoveObserver(board);
    }
}

HumanPlayer::HumanPlayer(ChessColor c) : Player(c) {}
HumanPlayer::HumanPlayer(Player &&p) : Player(std::move(p)) {}

void HumanPlayer::move(Board* b)
{
    std::string start, end;
    std::cin >> start >> end;

    int startLocation = parseLocation(start);
    int endLocation = parseLocation(end);

    AbstractPiece *target = nullptr;
    for (auto &p : pieces)
    {
        if (p->getSquare() == startLocation)
            target = p;
    }
    if (target == nullptr)
        throw std::invalid_argument("Invalid start position");

    target->move(endLocation);
}

ComputerPlayer_1::ComputerPlayer_1(ChessColor c) : Player(c) {}
ComputerPlayer_1::ComputerPlayer_1(Player &&p) : Player(std::move(p)) {}

void ComputerPlayer_1::move(Board* b) {
    std::cout << pieces.size() << " : SIZE" << std::endl;
    std::vector<int>piece_indexs = {};
    int s = pieces.size();
    for (int i = 0; i < s; i++) {
        piece_indexs.push_back(i);
    }
    
    while (piece_indexs.size() > 0) {
        size_t num_pieces = piece_indexs.size();
        int random_val = rand() % num_pieces; // Generate random number
        //cout << "Random index: " << rand_index << endl;
        int rand_index = piece_indexs[random_val];

        AbstractPiece* curr_piece = pieces[rand_index];
        //std::cout << "Name: " << curr_piece->getName();

        cout << curr_piece->getName() << " -> DECIDED PIECE" << endl;
        std::vector<int>all_moves = curr_piece->allMoves();

        cout << "ALL MOVES START" << endl;
        for (auto& m : all_moves) {
            cout << m << endl;
        }
        cout << "ALL MOVES END : " << endl;

        for (int move : all_moves) {
            std::cout << move << std::endl;
            if (b->isValidMove(curr_piece, curr_piece->getSquare(), move)) {
                std::cout << "DECIDED MOVE: " << move << ", CURR SQUARE: " << curr_piece->getSquare() << std::endl;
                curr_piece->move(move);
                return;
            }
        }
        // Else there are no valid moves for the given piece.
        // Remove piece from cpy_pices array. And keep looking.
        piece_indexs.erase(piece_indexs.begin() + random_val);
    }
}

ComputerPlayer_2::ComputerPlayer_2(ChessColor c) : Player(c) {}
ComputerPlayer_2::ComputerPlayer_2(Player &&p) : Player(std::move(p)) {}

void ComputerPlayer_2::move(Board* b) {
    // How it works: 
    // Same functionality as ComputerPlayer_1 except for each valid move found, 
    // see if it checks the opposing king or captures a piece. If it does, complete
    // the move.
    // If no move is found that leads to a check or capture, choose the first piece and move that
    // is valid. i.e make the first random move available.
    //std::cout << pieces.size() << " : SIZE" << std::endl;
    std::vector<int>piece_indexs = {};
    int s = pieces.size();
    for (int i = 0; i < s; i++) {
        piece_indexs.push_back(i);
    }

    // Initialize backup random piece and move;
    AbstractPiece* backup;
    int backup_move;
    
    while (piece_indexs.size() > 0) {
        size_t num_pieces = piece_indexs.size();
        int random_val = rand() % num_pieces; // Generate random number
        //cout << "Random index: " << rand_index << endl;
        int rand_index = piece_indexs[random_val];

        AbstractPiece* curr_piece = pieces[rand_index];
        //std::cout << "Name: " << curr_piece->getName();

        //cout << curr_piece->getName() << " -> DECIDED PIECE" << endl;
        std::vector<int>all_moves = curr_piece->allMoves();

        for (int move : all_moves) {
            //std::cout << move << std::endl;
            if (b->isValidMove(curr_piece, curr_piece->getSquare(), move)) {
                //std::cout << "DECIDED MOVE: " << move << ", CURR SQUARE: " << curr_piece->getSquare() << std::endl;

                //initialize backup moves;
                backup = curr_piece;
                backup_move = move;

                // // Check if the move captures another piece.
                if (b->squares[move].isOccupied()) {
                    curr_piece->move(move);
                    return;
                }

                // Else check if move results in a check to the king:
                // Move the piece to move.
                ChessColor opposing_king_color = curr_piece->getPieceColor() == ChessColor::White ? ChessColor::Black : ChessColor::White;
                curr_piece->move(move);
                // Loop through all the squares on the board checking the opposing king currently.
                for (Square* s : b->isInCheck(opposing_king_color)) {
                    if (s->getOccupant()->getSquare() == move) { // Check if the piece we just moved is checking the king.
                        return; // nothing is to be done, a move was just made that placed the opposing king in check.
                    }
                }
                // Else, the move did not result in a check. Revert move back to original square.
                // INPUT REVERT FUNCTION HERE.
            }
        }
        // Else there are no valid moves for the given piece.
        // Remove piece from cpy_pices array. And keep looking.
        piece_indexs.erase(piece_indexs.begin() + random_val);
    }
    backup->move(backup_move);
}
