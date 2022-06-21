#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

class Piece;
enum class Piece_type;


#include "piece.h"
#include "board.h"
#include "pgnParser.h"

class Game
{
public:
    Board board;
    Turn turn;
    Color player;

    Game();

    bool gameOver();
    bool isMate();
    void render();
    bool move(std::string);
};