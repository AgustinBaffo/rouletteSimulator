#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <list>

class Player
{
public:
    Player();
    ~Player();

private:

    std::string name;   //TODO: initialize
    float balance;      //TODO: initialize
    
    std::list<int> betList;
    int currentBet;

    void updateBet(bool hasWon);
    void updateCurrentBet();
    void resetBet();
    

};

#endif