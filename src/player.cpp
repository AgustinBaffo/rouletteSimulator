/**
* @file player.cpp
* @brief This file contains the definition of the player class.
* @version 1.0
* @date 11/14/2022
* @author Agustin Baffo
*/

#include "player.hpp"
#include <string>

// Initialize player counter
int Player::playerCount = 0;

Player::Player(std::string name, Roulette::BetsTypes defaultBetType, bool displayLog):
    name(name)
    , defaultBetType(defaultBetType)
    , displayLog(displayLog)
{
    playerID = playerCount++;
    balance = 0;
    
    //Set betList and currentBet
    resetBetList();
    updateCurrentBet();
}

Player::~Player()
{

}

std::string Player::getName() const{
    return name;
}

int Player::getBalance() const{
    return balance;
}

void Player::resetBetList(){
    betList = {1,2,3,4};
}

void Player::betRoulette(const Roulette& roulette){
    // Remove the silver from the balance and place the bet.
    balance -= currentBet;
    roulette.setBet(playerID,defaultBetType,currentBet);
}

void Player::updateBets(const Roulette& roulette){
    // Take profit.
    int moneyWon = roulette.payPlayer(playerID);
    bool hasWon = moneyWon>0;

    // Update balance.
    balance += moneyWon;

    // Show player info.
    if(displayLog){
        printPlayerInfo(hasWon,currentBet,balance);
    }

    // Update betList and currentBet.
    updateBetList(hasWon);
}

void Player::updateBetList(bool hasWon){
    if(hasWon){
        // If won, the sum of the extreme elements in the list is added.
        // If there was only 1 item, that item is added
        if(betList.size()<2){
            betList.push_back(betList.front());
        }
        else{
            betList.push_back(betList.front() + betList.back());
        }
    }
    else {
        // If lost, the extreme elements are removed.
        // If there were 1 or 0 items in the list, it must be restarted.
        if(betList.size()<=2){
            resetBetList();
        } else{
            betList.pop_front();
            betList.pop_back();
        }
    }

    // Update current bet.
    updateCurrentBet();
}

void Player::updateCurrentBet(){

    // If there are 2 or more elements, the sum of the extremes is the bet.
    // If there is only 1 element, that is the bet.
    if(betList.size() >= 2){
        currentBet = betList.front() + betList.back();
    }

    else if(betList.size() == 1){
        currentBet = betList.front();
    }
    
    else{
        // Since updateCurrentBet is called after checking that betList is not empty, this case should not happen. 
        std::cout<<"[Warning] Invalid list received when trying to update current bet in player "<<name;
        resetBetList(); 
        updateCurrentBet();
    }
    
    // If the minimum or maximum bet is exceeded, the list must be restarted.
    if(currentBet > Roulette::MAX_BET || currentBet < Roulette::MIN_BET){
        resetBetList();
        updateCurrentBet();
    }
    
}

void Player::printPlayerInfo(bool won, int moneyBet, int bal) const{
    std::cout<< "\t- PlayerName: "<<name<<
                ", betType: "<<Roulette::getBetTypeName(defaultBetType)<<
                ", betList: {";
                for(auto n: betList){
                    std::cout<<n<<",";
                }
                std::cout<<"}"<<
                ", moneyBet: "<<moneyBet<<
                " | result: "<<(won?"Won":"Lost")<<
                " => balance = "<<bal<<
                std::endl;
}