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
    int getBalance() const;

    void betRoulette(const Roulette& roulette);
    void updateBets(const Roulette& roulette);

    
private:

    static int playerCount;
    int playerID;
    std::string name;
    int balance;
    Roulette::BetsTypes defaultBetType;
    
    std::list<int> betList;
    int currentBet;

    void resetBetList();
    void updateBetList(bool hasWon);
    void updateCurrentBet();
    void printPlayerInfo(bool hasWon, int moneyBet, int balance) const;

};

#endif