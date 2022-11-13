#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <list>
#include "roulette.hpp"

class Player
{
public:
    Player(std::string name, Roulette::BetsTypes);
    ~Player();

    void betRoulette(const Roulette& roulette);
    void updateBets(const Roulette& roulette);
    std::string getName() const;
    int getID() const;
    
private:

    static int playerCount;
    int playerID;
    std::string name;   //TODO: initialize
    float balance;      //TODO: initialize
    
    std::list<int> betList;
    int currentBet;

    void updateBet(bool hasWon);
    void updateCurrentBet();
    void resetBet();
    Roulette::BetsTypes defaultBetType;
    

};

#endif