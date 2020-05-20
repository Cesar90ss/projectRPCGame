#include <iostream>
#include <string>
#include <stdlib.h> 
using namespace std;


enum objectType { rock = 1, paper = 2, scissors = 3 };
class object
{

public:

    static object* createObject(int choice);
    virtual void printObjectName() const = 0;
    virtual int getObjectType() const = 0;
    virtual ~object()
    {
    };
};


class Rock : public object
{
public:

    void printObjectName() const
    {
        cout << "I am a Rock" << endl;
    }

    int getObjectType() const
    {
        return rock;
    }

    virtual ~Rock()
    {
    };
};

class Paper : public object
{
public:

    void printObjectName() const
    {
        cout << "I am a Paper" << endl;
    }

    int getObjectType() const
    {
        return paper;
    }

    virtual ~Paper()
    {
    };
};


class Scissors : public object
{
public:

    void printObjectName() const
    {
        cout << "I am a Scissors" << endl;
    }

    int getObjectType() const
    {
        return scissors;
    }

    virtual ~Scissors()
    {
    };
};



object* object::createObject(const int choice)
{
    switch (choice)
    {
    case rock:
        return new Rock;
        break;

    case paper:
        return new Paper;
        break;

    case scissors:
        return new Scissors;
        break;

    default:
        return NULL;
        break;
    }
}

class RockPaperScissorGame
{

private:

    unsigned int lose_counter;
    unsigned int tie_counter;
    unsigned int win_counter;

    bool checkValidChoice(const unsigned int  choice)
    {
        if (choice == rock or choice == paper or choice == scissors)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    void printWinnerAndIncrementCounters(const unsigned int& computerObjectType, const unsigned int& userObjectType)
    {
        if (userObjectType == rock && computerObjectType == rock) {
            cout << "Rock meets Rock its a tie!" << endl;
            tie_counter++;
        }
        else if (userObjectType == rock && computerObjectType == paper) {
            cout << "Rock is covered by Paper the computer wins!." << endl;
            lose_counter++;
        }
        else if (userObjectType == rock && computerObjectType == scissors) {
            cout << "Rock crushes Scissors you win!" << endl;
            win_counter++;
        }
        else if (userObjectType == paper && computerObjectType == rock) {
            cout << "Paper covers Rock you win!" << endl;
            win_counter++;
        }
        else if (userObjectType == paper && computerObjectType == paper) {
            cout << "Paper meets Paper its a tie!" << endl;
            tie_counter++;
        }
        else if (userObjectType == paper && computerObjectType == scissors) {
            cout << "Paper is cut by Scissors the computer wins!" << endl;
            lose_counter++;
        }
        else if (userObjectType == scissors && computerObjectType == rock) {
            cout << "Scissors are crushed by Rock computer wins!" << endl;
            lose_counter++;
        }
        else if (userObjectType == scissors && computerObjectType == paper) {
            cout << "Scissors cuts Paper you win!" << endl;
            win_counter++;
        }
        else if (userObjectType == scissors && computerObjectType == scissors) {
            cout << "Scissors meet Scissors its a tie!" << endl;
            tie_counter++;
        }

        cout << "--------- End of round ---------" << endl;
    }



public:

    RockPaperScissorGame()
    {
        lose_counter = 0;
        tie_counter = 0;
        win_counter = 0;
    }
    void printGameInstructions()
    {
        cout << "-- Lets play Rock, Paper, Scissors! --" << endl;
        cout << "Press 1 for Rock, 2 for Paper, 3 for Scissors:" << endl;
        cout << "************************Game start ************************" << endl;
    }

    void printUserChoices(const object* computerPlayer, const object* userPlayer)
    {
        cout << "Computer Choice is :";
        computerPlayer->printObjectName();
        cout << endl;

        cout << "User Choice is :";
        userPlayer->printObjectName();
        cout << endl;
    }

    void play(const unsigned int computerChoice, const unsigned int userChoice)
    {

        if (!checkValidChoice(userChoice) or !checkValidChoice(computerChoice))
        {
            cout << "Invalid User Choice" << endl;
            return;
        }


        object* computerPlayer = object::createObject(computerChoice);
        object* userPlayer = object::createObject(userChoice);

        printUserChoices(computerPlayer, userPlayer);
        printWinnerAndIncrementCounters(computerPlayer->getObjectType(), userPlayer->getObjectType());

        delete computerPlayer;
        delete userPlayer;

    }

    void printGameResults()
    {
        cout << "Wins: " << win_counter << endl;
        cout << "Lose: " << lose_counter << endl;
        cout << "Tie: " << tie_counter << endl;
    }

    void endGame()
    {
        win_counter = lose_counter = tie_counter = 0;
    }
};



class GamePlayer
{
private:
    RockPaperScissorGame gameRPC;
    int numberOfTimes;

    void printGameMessageForRPC()
    {
        cout << "Please Enter number of times you want to play the game" << endl;
    }

    void printErrorMessageInCaseOfWrongNumberOfTimes()
    {
        cout << "Invalid Number of choice" << endl;
    }

    bool retreiveNumberOfTimesFromUserAndValidateIt()
    {
        int numberOfTimes_local;

        cin >> numberOfTimes_local;

        if (numberOfTimes_local < 0)
        {
            cout << "Invalid number , ending game" << endl;
            return false;

        }

        numberOfTimes = numberOfTimes_local;
    }

public:

    GamePlayer()
    {
        numberOfTimes = 0;
    }

    void playGame()
    {
        printGameMessageForRPC();

        if (retreiveNumberOfTimesFromUserAndValidateIt())
        {
            gameRPC.printGameInstructions();

            while (numberOfTimes > 0)
            {
                unsigned int computerChoice = rand() % 3 + 1;
                unsigned int userChoice;
                cout << "Enter Choice: ";
                cin >> userChoice;
                gameRPC.play(computerChoice, userChoice);

                numberOfTimes--;

            }

            gameRPC.printGameResults();
            gameRPC.endGame();
        }
        else
        {
            printErrorMessageInCaseOfWrongNumberOfTimes();
            gameRPC.endGame();
            return;
        }
    }

};