#include "chess.h"


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