#include "AbstractPiece.h"

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

AbstractPiece::~AbstractPiece()
{
    if (pieceRemovedObserver != nullptr) {
        pieceRemovedObserver->handlePieceRemoved(this);
    }
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
    //std::cout << this->getSquare() << " GET SQUARE" << std::endl;
    int currSquare = this->getSquare();
    vector<int> moves = {};
    if (this->getPieceColor() == ChessColor::White) {
        moves.push_back(currSquare - 8);
        moves.push_back(currSquare - 7);
        moves.push_back(currSquare - 9);
    } else{
        moves.push_back(currSquare + 8);
        moves.push_back(currSquare + 7);
        moves.push_back(currSquare + 9);
    }
    if (this->getPieceColor() == ChessColor::White && isFirst){
        moves.push_back(currSquare - 16);
    }
    if (this->getPieceColor() == ChessColor::Black && isFirst){
        moves.push_back(currSquare + 16);
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
    vector<int> kingOffsets = { -9, -8, -7, -1, 1, 7, 8, 9 }; // All directions

    for (size_t i = 0; i < 8; ++i) {
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

    int currRow = currSquare % 8;
    int currCol = currSquare / 8;

    std::vector<int> rows = {2, 2, -2, -2, 1, 1, -1, -1};
    std::vector<int> cols = {1, -1, 1, -1, 2, -2, 2, -2};

    std::vector<int> newRows;
    std::vector<int> newCols;
    std::vector<int> moves;

    for (int i = 0; i < 8; ++i){
        int newRow = currRow + rows[i];
        int newCol = currCol + cols[i];

        newRows.push_back(newRow);
        newCols.push_back(newCol);
        
    }

    for (int i =0; i < 8; ++i){
        if (newCols[i] >= 8){
            newCols.erase(newCols.begin() + i);
            newRows.erase(newRows.begin() + i);
        }
        else if (newRows[i] >= 8){
            newCols.erase(newCols.begin() + i);
            newRows.erase(newRows.begin() + i);
        }
    }

    for (size_t i = 0; i < newRows.size(); ++i){
        int move = newCols[i]*8 + newRows[i];
        moves.push_back(move);
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

    if (isFirst) {
        if (color == ChessColor::White) {
            validMoves.push_back(60);
        } else {
            validMoves.push_back(4);
        }
    }

    return validMoves;
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
    if (!validMove(newIndex)) throw std::invalid_argument("Invalid move 5, " + this->getName());

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
