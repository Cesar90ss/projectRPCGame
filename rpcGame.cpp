#include "rpcGame.hpp"



int main()
{

    RockPaperScissorGame game1;
    char continueToPlay;
    int userChoice;

    game1.printGameMessage();

    do
    {
        cout << "Enter Choice: ";
        cin >> userChoice;
        game1.play(userChoice);

        cout << "continue to play: y/n ";
        cin>>continueToPlay;
    } while (continueToPlay == 'y');
    game1.printFinalResults();
    return 0;
}