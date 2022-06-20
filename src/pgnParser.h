#ifndef PGNPARSER_H
#define PGNPARSER_H

#include <iostream>
// include <string> // Included in iostream, add if
// iostream is removed.
#include <vector>
#include <regex>
#include <iterator>

#define NOT_APPLICABLE "N/A"

enum class Winner{
    white, black, stalemate

};

enum class Promotion{
    None, Queen, Bishop, Knight, Rook
};

typedef struct Move{
    bool isCheckingMove; // is checking move (<src><target><+?>)
    // bool isCastlingMove; // due to how longalg works its not possible to detect if move is
    // castling based soley on position of piece.

    Promotion promotion; // Is Promotion move (<src><target><promotion?>)
    std::string longAlg; // Combined long algebraic notation.
    std::string source;
    std::string target;
} Move;

class PgnParser
{
public:
    Winner result;
    PgnParser();
    Move convertStringToMove(std::string);    
    PgnParser(std::string);
    std::vector<Move> moves;
};



#endif // PGNPARSER_H