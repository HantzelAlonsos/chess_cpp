#include "game.h"

Game::Game()
{
    player = Color::white;
    turn = Turn::god;
}

void Game::render()
{
    board.render(player);
}

bool Game::isMate(){
    if(board.boardIsInMate() != Turn::god){
        return true;
    }
    return false;
}

bool Game::gameOver(){
    return isMate();
}

bool Game::move(std::string moveStr)
{
    // Bör komma på något sätt att göra "Live chess". dvs att
    // När det är live så ska inte motsidans pjäser kunnas röras
    // men annars så ska det vara frittfram att göra vad du vill.

    // annars är det bara att passa ned Move till Board och låt den ta hand om det.
    // Bör nog också börjar returnera enums från board.move().
    PgnParser parser;
    Move move = parser.convertStringToMove(moveStr);
    if(move.longAlg == NOT_APPLICABLE){
        return false; // This means parsing has failed somehow.
    }
    if (!board.process(move))
    {
        std::cout << "Move is not legal" << std::endl;
        return false;
    }
    return true;
}

