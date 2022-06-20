#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

class Piece;
enum class Piece_type;
enum class color;

#include "piece.h"
#include "board.h"
#include "pgnParser.h"

class Game
{
public:
    Board board;
    Color turn;
    Color player;

    Game();

    void render();
    bool move(std::string);
};