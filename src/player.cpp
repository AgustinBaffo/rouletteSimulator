#include "player.hpp"
#include <string>

#define MIN_BET 4       // TODO: move to another class
#define MAX_BET 4000    // TODO: move to another class
    
int Player::playerCount = 0;

Player::Player(Roulette::BetsTypes defaultBetType):
    defaultBetType(defaultBetType)
{

    playerID = playerCount++;

    //****** TEST *****************
    resetBet();
    updateCurrentBet();

    // // TEST
    // // TODO: Delete it
    // std::list<bool> intentos = {false,false,false,true,true,true,false,false,true,true};
    // for(auto w: intentos){
    //     std::cout<<"betList = ";
    //     for(auto b: betList){std::cout<<b<<" ";}
    //     std::cout<<" | bet="<<currentBet;
    //     std::cout<<" | win="<<w;
    //     std::cout<<std::endl;

    //     updateBet(w);
    // }
    

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
    
    
}