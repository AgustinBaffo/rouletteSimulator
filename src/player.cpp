#include "player.hpp"
#include <string>
    
int Player::playerCount = 0;

Player::Player(std::string name, Roulette::BetsTypes defaultBetType, bool displayLog):
    name(name)
    , defaultBetType(defaultBetType)
    , displayLog(displayLog)
{
    playerID = playerCount++;
    balance = 0;
    
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

    // Update betList and currentBet
    updateBetList(hasWon);
}

void Player::updateBetList(bool hasWon){
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
            resetBetList();
        } else{
            betList.pop_front();
            betList.pop_back();
        }
    }
    updateCurrentBet();
}

void Player::updateCurrentBet(){

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