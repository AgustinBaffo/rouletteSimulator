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

    std::string getName() const;

    void betRoulette(const Roulette& roulette) const;
    void updateBets(const Roulette& roulette);
    
private:

    static int playerCount;
    int playerID;
    std::string name;
    float balance;
    Roulette::BetsTypes defaultBetType;
    
    std::list<int> betList;
    int currentBet;

    void resetBetList();
    void updateBetList(bool hasWon);
    void updateCurrentBet();
    void printPlayerInfo(bool hasWon, float moneyBet) const;

};

#endif