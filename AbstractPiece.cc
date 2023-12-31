#include "AbstractPiece.h"

AbstractPiece::~AbstractPiece()
{
    if (pieceRemovedObserver != nullptr) {
        pieceRemovedObserver->handlePieceRemoved(this);
    }
}

AbstractPiece* parsePieceSymbol(char p, ChessColor color, PieceRemovedObserver* owner) {
    if (tolower(p) == 'p') return new Pawn(color, owner);
    else if (tolower(p) == 'q') return new Queen(color, owner);
    else if (tolower(p) == 'k') return new King(color, owner);
    else if (tolower(p) == 'n') return new Knight(color, owner);
    else if (tolower(p) == 'r') return new Rook(color, owner);
    else return new Bishop(color, owner);
}

AbstractPiece* parsePieceSymbolAndCopy(char p, AbstractPiece* toCopy) {
    if (tolower(p) == 'p') return new Pawn(*toCopy);
    else if (tolower(p) == 'q') return new Queen(*toCopy);
    else if (tolower(p) == 'k') return new King(*toCopy);
    else if (tolower(p) == 'n') return new Knight(*toCopy);
    else if (tolower(p) == 'r') return new Rook(*toCopy);
    else return new Bishop(*toCopy);
}

AbstractPiece::AbstractPiece(AbstractPiece& p) {
    this->color = p.getPieceColor();
    this->pieceMovedObserver = p.pieceMovedObserver;
    this->pieceRemovedObserver = p.pieceRemovedObserver;
    this->name = p.getName();
    this->squareIndex = p.getSquare();
    this->previousSquareIndex = p.getPreviousSquare();
    this->isFirst = p.getIsFirst();
}

bool AbstractPiece::validMove(int targetSquare) {
    for (auto& i : allMoves()) {
        if (i == targetSquare) return true;
    }
    return false;
}

void AbstractPiece::revertLastMove(int newSquare, int prevSquare) {
    if (this->lastMoveWasFirstMove) {
        this->isFirst = true;
    }

    previousSquareIndex = squareIndex;
    squareIndex = newSquare;
    pieceMovedObserver->handlePieceMoved(this, true);
    previousSquareIndex = prevSquare;
}

std::string Pawn::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "P";
    }
    else
    {
        return "p";
    }
}

std::vector<int> Pawn::allMoves() {
    int currSquare = this->getSquare();
    vector<int> moves = {};

    if (this->getPieceColor() == ChessColor::White && isFirst) {
        moves.push_back(currSquare - 16);
    } else if(isFirst && this->getPieceColor() == ChessColor::Black){
        moves.push_back(currSquare + 16);
    }
    if (this->getPieceColor() == ChessColor::White) {
        moves.push_back(currSquare - 8);
            
        if (currSquare % 8 == 0){
            moves.push_back(currSquare - 7);
        } else if (currSquare % 8 == 7){
            moves.push_back(currSquare - 9);
        }  else{
            moves.push_back(currSquare - 7);
                moves.push_back(currSquare - 9);
        }
        
        
    } else{
        moves.push_back(currSquare + 8);

        if (currSquare % 8 == 0){
            moves.push_back(currSquare + 9);
        } else if (currSquare % 8 == 7){
            moves.push_back(currSquare + 7);
        }  else{
            moves.push_back(currSquare - 7);
             moves.push_back(currSquare - 9);
        }
    }

    
    return moves;
}

std::string Queen::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "Q";
    }
    else
    {
        return "q";
    }
}

std::vector<int> Queen::allMoves() {
    vector<int> validMoves = {};

    int currSquare = this->getSquare();
    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare + (i * 8));
    }

    for (int i = 1; i <= 8; i++) {
        validMoves.push_back(currSquare - (i * 8));
    }

    int currSquareCopy = currSquare;
    while (currSquareCopy % 8 != 0) {
        currSquareCopy--;
        validMoves.push_back(currSquareCopy);
    }

    currSquareCopy = currSquare;
    while (currSquareCopy % 8 != 0) {
        currSquareCopy++;
        validMoves.push_back(currSquareCopy);
    }

    for (int i = 1; i <= 8; i++) {
        if ((currSquare + (i*7)) % 8 == 0){
            break;
        }
        validMoves.push_back(currSquare + (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        if ((currSquare - (i*7)) % 8 == 0){
            break;
        }
        validMoves.push_back(currSquare - (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        if ((currSquare + (i*9)) % 8 == 0){
            break;
        }
        validMoves.push_back(currSquare + (i * 9));
    }

    for (int i = 1; i <= 8; i++) {
        if ((currSquare - (i*9)) % 8 == 0){
            break;
        }
        validMoves.push_back(currSquare - (i * 9));
    }

    return validMoves;
}

std::string King::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "K";
    }
    else
    {
        return "k";
    }
}

std::vector<int> King::allMoves() {
    vector<int> validMoves = {};

    // Define increments for horizontal, vertical, and diagonal movements
    vector<int> kingOffsets; // All directions
    int currSquare = this->getSquare();
    if (currSquare % 8){
        kingOffsets = { -8, -7, -1, 1, 8, 9 };
    }
    else if (currSquare % 8 == 7){
        kingOffsets = { -9, -8, -1, 1, 7, 8 };
    } else{
        kingOffsets = { -9, -8, -7, -1, 1, 7, 8, 9 }; 
    }

    size_t size = kingOffsets.size();
    for (size_t i = 0; i < size; ++i) {
        int newSquare = this->getSquare() + kingOffsets[i];
        validMoves.push_back(newSquare);  
    }

    if (isFirst) {
        if (color == ChessColor::White) {
            validMoves.push_back(63);
            validMoves.push_back(56);
        } else {
            validMoves.push_back(0);
            validMoves.push_back(7);
        }
    }

    return validMoves;
}

std::string Knight::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "N";
    }
    else
    {
        return "n";
    }
}

std::vector<int> Knight::allMoves() {

    int currSquare = this->getSquare();

    vector<int> knightOffsets;
    vector<int> moves;
    if (currSquare %8 == 0){
        knightOffsets = {-15, 17, -6, 10};
    } else if (currSquare %8 == 7){
        knightOffsets = {15, -17, +6, -10};
    } else if(currSquare % 8 ==1){
        knightOffsets = {-15, 17, -6, 10, 15, -17};
    } else if (currSquare % 8 == 6){
        knightOffsets = {15, -17, +6, -10, -15, 17};
    }


    size_t size = knightOffsets.size();
    for (size_t i = 0; i < size; ++i){
        moves.push_back(currSquare + knightOffsets[i]);
    }
    

    return moves;
}

std::string Rook::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "R";
    }
    else
    {
        return "r";
    }
}

std::vector<int> Rook::allMoves() {
    std::vector<int> validMoves;

    int currSquare = this->getSquare();
    int currRow = currSquare / 8; // Row index
    int currCol = currSquare % 8; // Column index

    // Generate vertical moves (up and down)
    for (int i = currRow + 1; i < 8; ++i) {
        if (i >= 8 || i < 0){
            break;
        }
        int move = i * 8 + currCol;
        validMoves.push_back(move);
    }
    for (int i = currRow - 1; i >= 0; --i) {
        if (i >= 8 || i < 0){
            break;
        }
        int move = i * 8 + currCol;
        validMoves.push_back(move);
    }

    // Generate horizontal moves (left and right)
    for (int i = currCol + 1; i < 8; ++i) {
        if (i >= 8 || i < 0){
            break;
        }
        int move = currRow * 8 + i;
        validMoves.push_back(move);
    }
    for (int i = currCol - 1; i >= 0; --i) {
        if (i >= 8 || i < 0){
            break;
        }
        int move = currRow * 8 + i;
        validMoves.push_back(move);
    }

    if (isFirst) {
        if (color == ChessColor::White) {
            validMoves.push_back(60);
        } else {
            validMoves.push_back(4);
        }
    }

    return validMoves;
    // for (int i = 1; i <= 8; i++) {
    //     validMoves.push_back(currSquare + (i * 8));
    // }

    // for (int i = 1; i <= 8; i++) {
    //     validMoves.push_back(currSquare - (i * 8));
    // }

    // int currSquareCopy = currSquare;
    // while (currSquareCopy % 8 != 0) {
    //     currSquareCopy--;
    //     validMoves.push_back(currSquareCopy);
    // }

    // currSquareCopy = currSquare;
    // while (currSquareCopy % 8 != 0) {
    //     currSquareCopy++;
    //     validMoves.push_back(currSquareCopy);
    // }

    
}

std::string Bishop::printable() const
{
    if (getPieceColor() == ChessColor::White)
    {
        return "B";
    }
    else
    {
        return "b";
    }
}

std::vector<int> Bishop::allMoves() {
   vector<int> validMoves;

    int curr = this->getSquare();
    for (int i = 1; i <= 8; i++) {
        if ((curr + (i*7)) % 8 == 0){
            break;
        }
        validMoves.push_back(curr + (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        if ((curr - (i*7)) % 8 == 0){
            break;
        }
        validMoves.push_back(curr - (i * 7));
    }

    for (int i = 1; i <= 8; i++) {
        if ((curr + (i*9)) % 8 == 0){
            break;
        }
        validMoves.push_back(curr + (i * 9));
    }

    for (int i = 1; i <= 8; i++) {
        if ((curr - (i*9)) % 8 == 0){
            break;
        }
        validMoves.push_back(curr - (i * 9));
    }

    return validMoves;
}

void AbstractPiece::move(int newIndex) {
    if (!validMove(newIndex)) throw std::invalid_argument("Invalid move 5");
    int previousSquareIndexCopy = previousSquareIndex;
    int squareIndexCopy = squareIndex;

    previousSquareIndex = squareIndex;
    squareIndex = newIndex;

    bool validatedByBoard = pieceMovedObserver->handlePieceMoved(this);
    if (!validatedByBoard) {
        previousSquareIndex = previousSquareIndexCopy;
        squareIndex = squareIndexCopy;
        throw std::invalid_argument("Invalid move 4");
    }

    if (isFirst) {
        isFirst = false;
        lastMoveWasFirstMove = true;
    } else {
        lastMoveWasFirstMove = false;
    }
}
