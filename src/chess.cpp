#include "chess.h"

Game::Game()
{
    player = Color::white;
    turn = Color::white;
}

void Game::render()
{
    board.render(player);
}

bool Game::move(std::string moveStr)
{
    // jag slutade ganska hastigt idag pga sc2 med kolmar. Men
    // Min tanke är att vi ersätter hela move flödet med Move.
    // Bör komma på något sätt att göra "Live chess". dvs att
    // När det är live så ska inte motsidans pjäser kunnas röras
    // men annars så ska det vara frittfram att göra vad du vill.

    // annars är det bara att passa ned Move till Board och låt den ta hand om det.
    // Bör nog också börjar returnera enums från board.move(). Typ som att
    // om du flyttar en bonde till sista raden och du inte inputtat e7e8q tex
    // så måste det frågas (Eller göra queen per default).
    PgnParser parser;
    Move move = parser.convertStringToMove(moveStr);
    if (!board.move(move))
    {
        std::cout << "Move is not legal" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    std::cout << "Chess simulator deluxe" << std::endl;
    
    Game myGame;
    myGame.render();
    
    if(argc > 1){
        //std::cout << "Test white pawn: \u2659" << std::endl;

        std::ifstream file("test/test1Game.pgn");
        std::stringstream buffer;
        buffer << file.rdbuf();
        PgnParser game = PgnParser(buffer.str());

        for (Move& move : game.moves){

            std::cout<<"move is: "<<move.longAlg<<std::endl;

            if(!myGame.move(move.longAlg)){
                break;
            }
            myGame.render();
            sleep(1);
        }
        exit(0);
    }
    else{
        while (1)
        {
            std::string input;
            std::cin >> input;
            myGame.move(input);
            myGame.render();
            if(input == std::string("exit")){
                exit(0);
            }
        }
    }
    



    

}