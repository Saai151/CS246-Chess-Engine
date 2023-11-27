#include <string>
#include "Square.h"

enum class pieceColor{
    White, Black
};

class AbstractPiece{
    private:
        Square currSquare;
        pieceColor color;
        std::string name;
    public:
        AbstractPiece(Square currSquare, pieceColor color, std::string name): currSquare{currSquare}, color{color}, name{name}{}

};