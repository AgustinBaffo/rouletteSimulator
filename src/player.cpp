#include "player.hpp"
#include <string>

#define MIN_BET 4       // TODO: move to another class
#define MAX_BET 4000    // TODO: move to another class
    
int Player::playerCount = 0;

Player::Player(std::string name, Roulette::BetsTypes defaultBetType):
    name(name),
    defaultBetType(defaultBetType)
{

    playerID = playerCount++;

    resetBet();
    updateCurrentBet();

    

}

Player::~Player()
{

}

void Player::updateBet(bool hasWon){
    if(hasWon){
        if(betList.size()<2){
            betList.push_back(betList.front());
        }
        else{
            betList.push_back(betList.front()+betList.back());
        }
    }
    else {
        if(betList.size()<=2){
            resetBet();
        } else{
            betList.pop_front();
            betList.pop_back();
        }
    }
    
    updateCurrentBet();
}

void Player::resetBet(){
    betList = {1,2,3,4};
}

void Player::updateCurrentBet(){

    int betListSize = betList.size();

    if(betListSize >= 2){
        currentBet = betList.front() + betList.back();
    }

    else if(betListSize==1){
        currentBet = betList.front();
    }
    
    else{
        //Since updateCurrentBet is called after checking that betList is not empty, this case should not happen. 
        std::cout<<"[Warning] Invalid list received when trying to update current bet in player "<<name;
        resetBet(); 
    }

    if(currentBet > MAX_BET || currentBet < MIN_BET){
        resetBet();
        updateCurrentBet();
    }
    
}

void Player::betRoulette(const Roulette& roulette){
    roulette.setBet(playerID,defaultBetType,currentBet);
}

void Player::updateBets(const Roulette& roulette){
    // Take profit
    float money;
    bool hasWon = roulette.payPlayer(playerID,money);

    // Make a new bet
    updateBet(hasWon);
    betRoulette(roulette);
}


std::string Player::getName() const{
    return name;
}

int Player::getID() const {
    return playerID;
}