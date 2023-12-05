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

void Player::clearPieces() {
    pieces.clear();
}

Player::Player(Player &&p) : c{p.getColor()}
{
    std::vector<AbstractPiece*> pieces_ = {};

    for (AbstractPiece *p : p.pieces) {
        p->attachPieceRemovedObserver(this);
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
    std::cout << "LEN: " << pieces.size() << std::endl;
    for (auto &p : pieces)
    {
        std::cout << p->getName() << " : LOC :" << p->getSquare() << " addr: " << p << std::endl;
        if (p->getSquare() == startLocation) {
            target = p;
        }
    }
    if (target == nullptr) {
        throw std::invalid_argument("Invalid start position");
    }

    std::cout << "TARGET; " << target->getName() << std::endl;
    for (auto& i : target->allMoves()) {
        std::cout << i << std::endl;
    }
    target->move(endLocation);
}

ComputerPlayer_1::ComputerPlayer_1(ChessColor c) : Player(c) {}
ComputerPlayer_1::ComputerPlayer_1(Player &&p) : Player(std::move(p)) {}

void ComputerPlayer_1::move(Board* b) {
    std::vector<int>piece_indexs = {};
    int s = pieces.size();
    for (int i = 0; i < s; i++) {
        piece_indexs.push_back(i);
    }
    
    while (piece_indexs.size() > 0) {
        size_t num_pieces = piece_indexs.size();
        int random_val = rand() % num_pieces; // Generate random number
        int rand_index = piece_indexs[random_val];

        AbstractPiece* curr_piece = pieces[rand_index];
        cout << curr_piece->getName() << endl;
        std::vector<int>all_moves = curr_piece->allMoves();

        for (int move : all_moves) {
            cout << move << endl;
            if (b->isValidMove(curr_piece, curr_piece->getSquare(), move)) {
                std::cout << "SELECTED: " << curr_piece->getName() << std::endl;
                std::cout << "FROM: " << curr_piece->getSquare() << " , TO: " << move << std::endl;
                curr_piece->move(move);
                return;
            }
        }
        // Else there are no valid moves for the given piece.
        // Remove piece from cpy_pices array. And keep looking.
        piece_indexs.erase(piece_indexs.begin() + random_val);
        cout << "erased" << endl;
    }
}

ComputerPlayer_2::ComputerPlayer_2(ChessColor c) : Player(c) {}
ComputerPlayer_2::ComputerPlayer_2(Player &&p) : Player(std::move(p)) {}

bool ComputerPlayer_2::checkFromMove(AbstractPiece* curr_piece, Board* b, int move) {
    //Basic Idea:
    // Create a copy of the board built from the white->pieces, black->pieces, and a nullptr display.
    // Make the move on the built board.
    // delete the board.

    // Generate white->pieces and black->pieces;
    std::vector<AbstractPiece*>white_pieces;
    std::vector<AbstractPiece*>black_pieces;
    for (Square s : b->squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() == ChessColor::White) {
            // Create copy;
            AbstractPiece* new_p = parsePieceSymbolAndCopy(s.getOccupant()->printable()[0], s.getOccupant());
            new_p->detachRemovedObserver();
            white_pieces.push_back(new_p);
        } else if (s.isOccupied()) {
            AbstractPiece* new_p = parsePieceSymbolAndCopy(s.getOccupant()->printable()[0], s.getOccupant());
            new_p->detachRemovedObserver();
            black_pieces.push_back(new_p);
        }
    }
    cout << "pieces successfully copied" << endl;
    // Generate cpy board.
    std::vector<DisplayObserver*> empty_displays = {};
    DisplayAggregator allDisplays = DisplayAggregator(empty_displays);
    Board* cpy_board = new Board(white_pieces, black_pieces, &allDisplays, false);
    // Pass cpy_board as an observer of each piece.
    for (AbstractPiece* p : white_pieces) {
        p->attachMoveObserver(cpy_board);
    }
    for (AbstractPiece* p : black_pieces) {
        p->attachMoveObserver(cpy_board);
    }

    // Locate the curr_piece in the cpy board.
    for (Square s : cpy_board->squares) {
        if (s.isOccupied() && s.getOccupant()->getSquare() == curr_piece->getSquare()) {
            std::cout << "BEFORE" << std::endl;
            std::cout << "Name: " << s.getOccupant()->getName() << " Move: " << move << std::endl;
            s.getOccupant()->move(move); //make the move on the copy board.
            std::cout << "AFter" << std::endl;
            break;
        }
    }
    // Check if the board is in check.
    bool isInCheck = false;
    ChessColor opposing_king = curr_piece->getPieceColor() == ChessColor::White ? ChessColor::Black : ChessColor::White;
    for (Square *s : cpy_board->isInCheck(opposing_king)) {
        if (s->getOccupant()->getSquare() == move) {
            isInCheck = true; // The move did lead to a check.
        }
    }

    // Delete each piece.
    for (AbstractPiece* p : white_pieces) {
        delete p;
    }
    for (AbstractPiece* p : black_pieces) {
        delete p;
    }
    delete cpy_board;
    return isInCheck;
}

void ComputerPlayer_2::move(Board* b) {
    // How it works: 
    // Same functionality as ComputerPlayer_1 except for each valid move found, 
    // see if it checks the opposing king or captures a piece. If it does, complete
    // the move.
    // If no move is found that leads to a check or capture, choose the first piece and move that
    // is valid. i.e make the first random move available.
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
                // TESTING NEW FUNCTION:
                if (checkFromMove(curr_piece, b, move)) {
                    curr_piece->move(move);
                    return;
                }

                // ChessColor opposing_king_color = curr_piece->getPieceColor() == ChessColor::White ? ChessColor::Black : ChessColor::White;
                // int original_square = curr_piece->getSquare();
                // int previous_square = curr_piece->getPreviousSquare();
                // curr_piece->move(move);
                // // Loop through all the squares on the board checking the opposing king currently.
                // for (Square* s : b->isInCheck(opposing_king_color)) {
                //     if (s->getOccupant()->getSquare() == move) { // Check if the piece we just moved is checking the king.
                //         return; // nothing is to be done, a move was just made that placed the opposing king in check.
                //     }
                // }
                // // Else, the move did not result in a check. Revert move back to original square.
                // curr_piece->revertLastMove(original_square,previous_square);
            }
        }
        // Else there are no valid moves for the given piece.
        // Remove piece from cpy_pices array. And keep looking.
        piece_indexs.erase(piece_indexs.begin() + random_val);
        cout << "erased once" << endl;
    }
    backup->move(backup_move);
}

ComputerPlayer_3::ComputerPlayer_3(ChessColor c) : Player(c) {}
ComputerPlayer_3::ComputerPlayer_3(Player &&p) : Player(std::move(p)) {}

bool ComputerPlayer_3::checkFromMove(AbstractPiece* curr_piece, Board* b, int move) {
    //Basic Idea:
    // Create a copy of the board built from the white->pieces, black->pieces, and a nullptr display.
    // Make the move on the built board.
    // delete the board.

    // Generate white->pieces and black->pieces;
    std::vector<AbstractPiece*>white_pieces;
    std::vector<AbstractPiece*>black_pieces;
    for (Square s : b->squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() == ChessColor::White) {
            // Create copy;
            AbstractPiece* new_p = parsePieceSymbolAndCopy(s.getOccupant()->printable()[0], s.getOccupant());
            new_p->detachRemovedObserver();
            white_pieces.push_back(new_p);
        } else if (s.isOccupied()) {
            AbstractPiece* new_p = parsePieceSymbolAndCopy(s.getOccupant()->printable()[0], s.getOccupant());
            new_p->detachRemovedObserver();
            black_pieces.push_back(new_p);
        }
    }
    cout << "pieces successfully copied" << endl;
    // Generate cpy board.
    std::vector<DisplayObserver*> empty_displays = {};
    DisplayAggregator allDisplays = DisplayAggregator(empty_displays);
    Board* cpy_board = new Board(white_pieces, black_pieces, &allDisplays, false);
    // Pass cpy_board as an observer of each piece.
    for (AbstractPiece* p : white_pieces) {
        p->attachMoveObserver(cpy_board);
    }
    for (AbstractPiece* p : black_pieces) {
        p->attachMoveObserver(cpy_board);
    }

    // Locate the curr_piece in the cpy board.
    for (Square s : cpy_board->squares) {
        if (s.isOccupied() && s.getOccupant()->getSquare() == curr_piece->getSquare()) {
            std::cout << "BEFORE" << std::endl;
            std::cout << "Name: " << s.getOccupant()->getName() << " Move: " << move << std::endl;
            s.getOccupant()->move(move); //make the move on the copy board.
            std::cout << "AFter" << std::endl;
            break;
        }
    }
    // Check if the board is in check.
    bool isInCheck = false;
    ChessColor opposing_king = curr_piece->getPieceColor() == ChessColor::White ? ChessColor::Black : ChessColor::White;
    for (Square *s : cpy_board->isInCheck(opposing_king)) {
        if (s->getOccupant()->getSquare() == move) {
            isInCheck = true; // The move did lead to a check.
        }
    }

    // Delete each piece.
    for (AbstractPiece* p : white_pieces) {
        delete p;
    }
    for (AbstractPiece* p : black_pieces) {
        delete p;
    }
    delete cpy_board;
    return isInCheck;
}

bool ComputerPlayer_3::canBeCaptured(AbstractPiece* curr_piece, Board* b) {
    //Basic idea:
    // Loop through all squares on the board, weeding out all the squares which are occupied by opposing colour pieces.
    //      For each of the opponents pieces, loop through it's all moves, and check if a move to the end location (curr_piece square)
    //      is valid. If it is, then it can eat the current_piece. Then return true.
    for (Square s : b->squares) {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() != curr_piece->getPieceColor()) {
            for (int move : s.getOccupant()->allMoves()) {
                if (b->isValidMove(s.getOccupant(), s.getOccupant()->getSquare(), curr_piece->getSquare())) {
                    return true;
                }
            }
        }
    }
    return false;
}

void ComputerPlayer_3::move(Board* b) {
    // How it works: 
    // Mostly same functionality as level 2, however...
    // All pieces are checked to see if they can avoid capture first.
    // Along the way of checking, if a piece-move combo leads to a capture or 
    // leads to checking the opposing king, that move combo is saved as next_best combo.
    // next_best combo is initially the first viable random move.
    // After checking all pieces if they can avoid capture, the next_best combo is chosen as the move.
    // MoveRank is introduced in this level of computer. Where,
    // 1 = equivalent to a random move.
    // 2 = equivalent to a capture or a move that leads to a check.
    // 3 = equivalent to a move that avoids capture. ** This level will not be used as any move 
    //     equivalent to a level 3 will be chosen immediately. 
    // At the end of the program, if no level 3 moves are found then the next highest ranking move
    // will be chosen.

    std::vector<int>piece_indexs = {};
    int s = pieces.size();
    for (int i = 0; i < s; i++) {
        piece_indexs.push_back(i);
    }

    // Initialize next best piece, move and rank.
    AbstractPiece* backup;
    int backup_move;
    int MoveRank = 1;
    
    while (piece_indexs.size() > 0) {
        size_t num_pieces = piece_indexs.size();
        int random_val = rand() % num_pieces; // Generate random number
        int rand_index = piece_indexs[random_val];

        AbstractPiece* curr_piece = pieces[rand_index];
        std::vector<int>all_moves = curr_piece->allMoves();

        for (int move : all_moves) {
            if (b->isValidMove(curr_piece, curr_piece->getSquare(), move)) {
                // Check if the move avoids capture
                if (canBeCaptured(curr_piece, b)) {
                    curr_piece->move(move);
                    return;
                } 

                // Else check if the move captures another piece.
                if (b->squares[move].isOccupied() && MoveRank < 2) { // If the move does lead to a capture, ensure that the backup move is 
                                                                     // worst than a Rank 2 move. i.e a random move.
                    backup = curr_piece;
                    backup_move = move;
                    MoveRank = 2;
                }

                // Else check if move results in a check to the king: only if rank is smaller than 2.
                if (MoveRank < 2 && checkFromMove(curr_piece, b, move)) {
                    backup = curr_piece;
                    backup_move = move; 
                    MoveRank = 2;

                    // Move the piece to move.
                    // ChessColor opposing_king_color = curr_piece->getPieceColor() == ChessColor::White ? ChessColor::Black : ChessColor::White;
                    // int original_square = curr_piece->getSquare();
                    // int previous_square = curr_piece->getPreviousSquare();
                    // curr_piece->move(move);
                    // // Loop through all the squares on the board checking the opposing king currently.
                    // for (Square* s : b->isInCheck(opposing_king_color)) {
                    //     if (s->getOccupant()->getSquare() == move) { // Check if the piece we just moved is checking the king.
                    //         // move leads to a check. We already know backup move is worst han a rank 2 move. 
                    //         // Revert move back to original square;
                    //         curr_piece->revertLastMove(original_square,previous_square);
                    //         // Now set it as the backup.
                    //         backup = curr_piece;
                    //         backup_move = move; 
                    //         MoveRank = 2;
                    //         break;       
                    //     }
                    // }
                }
            }
        }
        // Else there are no rank 3 moves for the given piece.
        // Remove piece from cpy_pices array. And keep looking.
        piece_indexs.erase(piece_indexs.begin() + random_val);
    }
    backup->move(backup_move); // If no rank 3 moves are found, move next best move combo.
}

