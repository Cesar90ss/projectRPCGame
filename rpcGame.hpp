// Example program
#include <iostream>
#include <string>
#include <stdlib.h> 
using namespace std;


class object 
{
 
 public: 
 
 static object* createObject (int choice);
 virtual void printObjectName () = 0 ;
 virtual int getObjectType() = 0 ;
 virtual ~ object () 
 {
 };
};


class rock : public object
{
 public:
 
 void printObjectName()
 {
     cout<<"I am a rock"<<endl;
 }
 
 int getObjectType()
 {
     return 1;
 }
 
  virtual ~ rock () 
 {
 };
};

class paper : public object
{
 public:
 
 void printObjectName()
 {
     cout<<"I am a paper"<<endl;
 }
 
  int getObjectType()
 {
     return 2;
 }
 
  virtual ~ paper () 
 {
 };
};


class scissors : public object
{
 public:
 
 void printObjectName()
 {
     cout<<"I am a scissors"<<endl;
 }
 
  int getObjectType()
 {
     return 3;
 }
 
  virtual ~  scissors () 
 {
 };
};



 object* object::createObject (const int choice)
 {
        switch (choice) 
   {
        case 1:
        return new rock;
        break;
        
        case 2:
        return new paper;
        break;
        
        case 3:
        return new scissors ;
        break;
        
        default: 
        return NULL;
        break;
   }
 }

class RockPaperScissorGame 
{
    
private: 

int lose;
int tie;
int win;

bool validateChoice (const int choice)
{
   if (choice<1 || choice>3)
  {
      return false;
  }
 else
 {
     return true;
 }

}

void printWinnerAndIncrementCounters (const int computerObjectType , const int  userObjectType)
{
     if(userObjectType == 1 && computerObjectType == 1){
         cout << "Rock meets Rock its a tie!" << endl;
         tie++;
         }
    else if(userObjectType ==1 && computerObjectType== 2){
         cout << "Rock is covered by Paper the computer wins!." << endl;
         lose++;
         }
    else if(userObjectType == 1 && computerObjectType == 3){
         cout << "Rock crushes Scissors you win!" << endl;
         win++;
         }
    else if(userObjectType == 2 && computerObjectType == 1){
         cout << "Paper covers Rock you win!" << endl;
         win++;
         }
    else if(userObjectType == 2 && computerObjectType == 2){
         cout << "Paper meets Paper its a tie!" << endl;
         tie++;
         }
    else if(userObjectType == 2 && computerObjectType == 3){
         cout << "Paper is cut by Scissors the computer wins!" << endl;
         lose++;
         }
    else if( userObjectType == 3 && computerObjectType == 1){
         cout << "Scissors are crushed by Rock computer wins!" << endl;
         lose++;
         }
    else if( userObjectType == 3 && computerObjectType == 2){
         cout << "Scissors cuts Paper you win!" << endl;
         win++;
         }
    else if(userObjectType == 3 && computerObjectType == 3){
         cout << "Scissors meet Scissors its a tie!" << endl;
         tie++;
         }
}



public: 

RockPaperScissorGame ()
{
    lose=0;
    tie=0;
    win=0;
}
void printGameMessage ()
{
    cout << "-- Lets play Rock, Paper, Scissors! --" << endl;
    cout << "Press 1 for Rock, 2 for Paper, 3 for Scissors:" << endl;
    cout<<"************************Game start ************************" <<endl;
}

void play (const int userChoice)
{
  const int computerChoice = rand() % 3 + 1;     
  
  if(!validateChoice(userChoice))
  {
    cout<<"Invalid User Choice"<<endl;
    return;
  }
  
  object* computerPlayer = object::createObject(computerChoice);
  object* userPlayer = object::createObject(userChoice);
  
  cout<<"Computer Choice is :";
  computerPlayer->printObjectName();
  cout<<endl;
  
  cout<<"User Choice is :";
  userPlayer->printObjectName(); 
  cout<<endl;
  
  printWinnerAndIncrementCounters(computerPlayer->getObjectType(),userPlayer->getObjectType());
  
   
         
  cout<<"--------- End of game ---------"<<endl;
  
  delete computerPlayer;
  delete userPlayer;
  
}

void printFinalResults ()
{
  cout<<"Wins: "<<win<<endl;
  cout<<"Lose: "<<lose<<endl;
  cout<<"Tie: "<<tie<<endl;
}
};



