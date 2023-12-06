#include "Board.h"

// returns true of we can castle
bool isCastling(std::vector<Square> squares, int startLocation, int endLocation)
{
    if (squares[startLocation].isOccupied() && squares[startLocation].getOccupant()->getName() == "King" && squares[startLocation].getOccupant()->getIsFirst() && squares[endLocation].isOccupied() && squares[endLocation].getOccupant()->getName() == "Rook" && squares[endLocation].getOccupant()->getIsFirst())
    {
        return true;
    }

    return false;
}

// returns the piece with the name, name within pieces
std::vector<AbstractPiece *> getPieces(std::string name, std::vector<AbstractPiece *> pieces)
{
    std::vector<AbstractPiece *> result;

    for (auto &p : pieces)
    {
        if (p->getName() == name)
            result.push_back(p);
    }

    return result;
}

// Constructs a game board, initializing squares based on ranks and files. 
// If hardCode is false, it populates the board with the given white and black pieces.
// If hardCode is true, it selectively places predefined pieces (pawn, rook, knight, bishop, king, queen) 
// for both white and black on specific squares to set up the initial chess board configuration.
Board::Board(std::vector<AbstractPiece *> white, std::vector<AbstractPiece *> black, DisplayAggregator *g, bool hardCode)
{
    std::vector<AbstractPiece *> selectedPieces;
    squares.reserve(64); // Reserve space for 64 squares

    for (int rank = 7; rank >= 0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            bool isWhite = (file + rank) % 2 != 0;
            ChessColor currColor = (isWhite) ? ChessColor::White : ChessColor::Black;
            Location loc(rank, static_cast<File>(file));
            Square mySquare(loc, currColor, nullptr, g);
            squares.push_back(mySquare);
        }
    }

    if (!hardCode)
    {
        for (auto &p : white)
        {
            int s = p->getSquare();
            squares[s].setOccupant(p);
        }

        for (auto &b : black)
        {
            int s = b->getSquare();
            squares[s].setOccupant(b);
        }
        return;
    }
    /* Place down white pieces */
    selectedPieces = getPieces("Pawn", white);
    for (int i = 48; i < 56; i++)
    {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = getPieces("Rook", white);
    squares[63].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[56].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Knight", white);
    squares[62].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[57].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Bishop", white);
    squares[61].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[58].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("King", white);
    squares[60].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("Queen", white);
    squares[59].setOccupant(selectedPieces.back());

    /* Place down black pieces */
    selectedPieces = getPieces("Pawn", black);
    for (int i = 8; i < 16; i++)
    {
        squares[i].setOccupant(selectedPieces.back());
        selectedPieces.pop_back();
    }

    selectedPieces = getPieces("Rook", black);
    squares[0].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[7].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Knight", black);
    squares[1].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[6].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();

    selectedPieces = getPieces("Bishop", black);
    squares[2].setOccupant(selectedPieces.back());
    selectedPieces.pop_back();
    squares[5].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("King", black);
    squares[4].setOccupant(selectedPieces.back());

    selectedPieces = getPieces("Queen", black);
    squares[3].setOccupant(selectedPieces.back());
}


// Resets the board
void Board::reset()
{
    for (auto &s : squares)
    {
        s.setOccupant(nullptr);
    }
}

// checks if a piece can block a check and then returns true if it can
bool Board::blockCheck(AbstractPiece *curr_piece, AbstractPiece *king, int move)
{
    // Basic Idea:
    // Create a copy of the board.
    // make the desired move in the copy of the board.
    // check if the king is still in check.

    // Create a copy of the board.
    //  Generate white->pieces and black->pieces;
    std::vector<AbstractPiece *> white_pieces;
    std::vector<AbstractPiece *> black_pieces;
    for (Square s : squares)
    {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() == ChessColor::White)
        {
            // Create copy;
            AbstractPiece *new_p = parsePieceSymbolAndCopy(s.getOccupant()->printable()[0], s.getOccupant());
            new_p->detachRemovedObserver();
            white_pieces.push_back(new_p);
        }
        else if (s.isOccupied())
        {
            AbstractPiece *new_p = parsePieceSymbolAndCopy(s.getOccupant()->printable()[0], s.getOccupant());
            new_p->detachRemovedObserver();
            black_pieces.push_back(new_p);
        }
    }
    // Generate cpy board.
    std::vector<DisplayObserver *> empty_displays = {};
    DisplayAggregator allDisplays = DisplayAggregator(empty_displays);
    Board *cpy_board = new Board(white_pieces, black_pieces, &allDisplays, false);
    // Pass cpy_board as an observer of each piece.
    for (AbstractPiece *p : white_pieces)
    {
        p->attachMoveObserver(cpy_board);
    }
    for (AbstractPiece *p : black_pieces)
    {
        p->attachMoveObserver(cpy_board);
    }

    // Locate the curr_piece in the cpy board.
    for (Square s : cpy_board->squares)
    {
        if (s.isOccupied() && s.getOccupant()->getSquare() == curr_piece->getSquare())
        {
            s.getOccupant()->move(move); // make the move on the copy board.
            break;
        }
    }
    // Check if the board is still in check.
    bool inCheck = true;
    if (isInCheck(king->getPieceColor()).size() == 0)
    {
        inCheck = false;
    }
    // Delete each piece.
    for (AbstractPiece *p : white_pieces)
    {
        delete p;
    }
    for (AbstractPiece *p : black_pieces)
    {
        delete p;
    }
    delete cpy_board;
    return inCheck;
}

// Returns true if a piece is checking the king
bool Board::isPieceCheckingTheKing(Square s, AbstractPiece *king, ChessColor c)
{
    return s.isOccupied() && s.getOccupant()->getPieceColor() != c && s.getOccupant()->validMove(king->getSquare()) && isValidMove(s.getOccupant(), s.getOccupant()->getSquare(), king->getSquare());
}

std::vector<AbstractPiece *> Board::isInCheck(ChessColor c)
{
    std::vector<AbstractPiece *> checked;
    AbstractPiece *king;
    for (auto &s : squares)
    {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c)
        {
            king = s.getOccupant();
        }
    }

    for (auto &s : squares)
    {
        if (isPieceCheckingTheKing(s, king, c))
        {
            checked.push_back(s.getOccupant());
        }
    }

    return checked;
}

// Returns true to the gamestate if the king is currently under checkmate, allows us to end a game
bool Board::isCheckmate(ChessColor c)
{
    // Basic Idea:
    // First Check if the King is in check.
    //  Next check if it has any valid moves
    //   Next Check if any exisiting piece on the same team can move in such a way to prevent check.

    // First locate the king;
    AbstractPiece *king;
    for (auto &s : squares)
    {
        if (s.isOccupied() && s.getOccupant()->getName() == "King" && s.getOccupant()->getPieceColor() == c)
        {
            king = s.getOccupant();
        }
    }

    // Check if the king is in check;
    if (isInCheck(c).size() == 0)
    {
        return false;
    }

    // Check if the king has any valid moves:
    for (int move : king->allMoves())
    {
        if (isValidMove(king, king->getSquare(), move))
        {
            return false;
        }
    }

    // Check if piece can block.
    // Loop through all pieces on the same team as king.
    for (Square s : squares)
    {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() == king->getPieceColor() && s.getOccupant()->getName() != "King")
        {   
            // Loop through all its moves. Pass to the blockCheck function.
            for (int move : s.getOccupant()->allMoves())
            {
                if (blockCheck(s.getOccupant(), king, move))
                { // i.e it is possible for a piece to block checkmate.
                    return false;
                }
            }
        }
    }
    return true;
}

// Checks for stalemate, returns true for a draw
bool Board::isStalemate(ChessColor current_colour)
{
    if (isInCheck(current_colour).size() > 0)
    {
        return false;
    }

    for (Square s : squares)
    {
        if (s.isOccupied() && s.getOccupant()->getPieceColor() == current_colour)
        {
            for (int move : s.getOccupant()->allMoves())
            {
                if (isValidMove(s.getOccupant(), s.getOccupant()->getSquare(), move))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

// Places a piece on the board
void Board::placePiece(AbstractPiece *piece, int square)
{
    if (squares[square].isOccupied())
    {
        squares[square].reset();
    }
    squares[square].setOccupant(piece);
}

void Board::resetSquare(int index)
{
    squares[index].reset();
}

bool Board::validState()
{
    int whiteKingCount = 0;
    int blackKingCount = 0;

    for (auto &s : squares)
    {
        if (s.isOccupied() && s.getOccupant()->getName() == "King")
        {
            if (s.getOccupant()->getPieceColor() == ChessColor::White)
            {
                whiteKingCount++;
            }
            else
            {
                blackKingCount++;
            }
        }
    }

    if (whiteKingCount > 1 || blackKingCount > 1)
        return false;

    if (isInCheck(ChessColor::White).size() > 0 || isInCheck(ChessColor::Black).size() > 0)
        return false;

    return true;
}

bool Board::handlePieceMoved(AbstractPiece *piece, bool overrideValidation)
{
    if (overrideValidation || isValidMove(piece, piece->getPreviousSquare(), piece->getSquare()))
    {
        if (isCastling(squares, piece->getPreviousSquare(), piece->getSquare()))
        {
            AbstractPiece *temp_1 = squares[piece->getPreviousSquare()].getOccupant();
            AbstractPiece *temp_2 = squares[piece->getSquare()].getOccupant();

            squares[piece->getSquare()].setOccupant(nullptr);
            squares[piece->getPreviousSquare()].setOccupant(nullptr);

            squares[piece->getSquare()].setOccupant(temp_1);
            temp_1->hasMoved();

            squares[piece->getPreviousSquare()].setOccupant(temp_2);
            temp_2->hasMoved();
        }
        else
        {
            squares[piece->getPreviousSquare()].setOccupant(nullptr);
            squares[piece->getSquare()].setOccupant(piece);

            if (piece->getName() == "Pawn" && ((7 - piece->getSquare() >= 0) || (63 - piece->getSquare()) <= 7))
            {
                std::string added;
                std::cin >> added;

                AbstractPiece *addedPiece = parsePieceSymbolAndCopy(added[0], piece);
                int ind = piece->getSquare();
                squares[ind].setOccupant(nullptr);

                piece->detachRemovedObserver();
                delete piece;

                piece = addedPiece;
                squares[ind].setOccupant(piece);
            }

            return true;
        }
    }

    return false;
}

bool Board::isValidMove(AbstractPiece *target, int startLocation, int endLocation)
{
    if (endLocation < 0 || endLocation > 63)
    {
        return false;
    }

    int delta = abs(endLocation - startLocation);
    ChessColor captureColor;
    if (target->getPieceColor() == ChessColor::Black)
    {
        captureColor = ChessColor::White;
    }
    else
    {
        captureColor = ChessColor::Black;
    }

    if (isCastling(squares, startLocation, endLocation))
    {
        for (int i = 1; i < delta; i++)
        {
            if (startLocation > endLocation)
            {
                if (squares[startLocation - i].isOccupied())
                    return false;
                for (auto &s : squares)
                {
                    if (s.isOccupied() && s.getColor() == captureColor && s.getOccupant()->validMove(startLocation - i) && isValidMove(s.getOccupant(), s.getLocation().getIndex(), startLocation - i))
                        return false;
                }
            }
            else
            {
                if (squares[startLocation + i].isOccupied())
                    return false;
                for (auto &s : squares)
                {
                    if (s.isOccupied() && s.getColor() == captureColor && s.getOccupant()->validMove(startLocation + i) && isValidMove(s.getOccupant(), s.getLocation().getIndex(), startLocation + i))
                        return false;
                }
            }
        }

        for (auto &s : squares)
        {
            if (startLocation > endLocation)
            {
                if (s.isOccupied() && s.getColor() == captureColor && s.getOccupant()->validMove(startLocation - delta) && isValidMove(s.getOccupant(), s.getLocation().getIndex(), startLocation - delta))
                    return false;
            }
            else
            {
                if (s.isOccupied() && s.getColor() == captureColor && s.getOccupant()->validMove(startLocation + delta) && isValidMove(s.getOccupant(), s.getLocation().getIndex(), startLocation + delta))
                    return false;
            }
        }

        return true;
    }

    if (squares[endLocation].isOccupied() && squares[endLocation].getOccupant()->getPieceColor() != captureColor)
    {
        return false;
    }

    if (target->getName() == "King")
    {
        for (auto &s : squares)
        {
            if (s.isOccupied() && s.getOccupant()->getPieceColor() == captureColor && s.getOccupant()->validMove(target->getSquare()) && isValidMove(s.getOccupant(), s.getLocation().getIndex(), target->getSquare()))
                return false;
        }
    }

    if (target->getName() == "Knight")
        return true;

    if (delta % 9 == 0 || delta % 7 == 0)
    {

        int x;

        if (delta % 9 == 0)
        {
            x = 9;
        }
        else if (delta % 7 == 0)
        {
            x = 7;
        }

        int steps = delta / x;
        for (int i = 1; i < steps; ++i)
        {
            int index = (startLocation < endLocation) ? startLocation + (i * x) : startLocation - (i * x);
            if (squares[index].isOccupied())
                return false;
        }

        if (target->getName() == "Pawn")
        {
            if (squares[endLocation].isOccupied())
                return true;
            else
                return false;
        }
    }
    else if (delta % 8 == 0)
    { // veritcal move
        if (target->getName() == "Pawn")
        {
            if (squares[endLocation].isOccupied())
                return false;
        }
        if (startLocation > endLocation)
        {
            for (int i = 1; i < (delta / 8); i++)
            {
                if (squares[startLocation - (i * 8)].isOccupied())
                    return false;
            }
        }
        else
        {
            for (int i = 1; i < (delta / 8); i++)
            {
                if (squares[startLocation + (i * 8)].isOccupied())
                    return false;
            }
        }
    }
    else
    {
        if (startLocation > endLocation)
        {
            for (int i = 1; i < delta; i++)
            {
                if (squares[startLocation - i].isOccupied())
                    return false;
            }
        }
        else
        {
            for (int i = 1; i < delta; i++)
            {
                if (squares[startLocation + i].isOccupied())
                    return false;
            }
        }
    }

    return true;
}

Board::~Board() {}
