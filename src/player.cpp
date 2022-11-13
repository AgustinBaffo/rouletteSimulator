#include "player.hpp"
#include <string>
    
int Player::playerCount = 0;

Player::Player(std::string name, Roulette::BetsTypes defaultBetType):
    name(name),
    defaultBetType(defaultBetType)
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

void Player::resetBetList(){
    betList = {1,2,3,4};
}

void Player::betRoulette(const Roulette& roulette) const{
    roulette.setBet(playerID,defaultBetType,currentBet);
}

void Player::updateBets(const Roulette& roulette){
    // Take profit
    float moneyWon;
    bool hasWon = roulette.payPlayer(playerID,moneyWon);

    // Show player info
    printPlayerInfo(hasWon,currentBet);

    // Update betList and currentBet
    updateBetList(hasWon);

    // Make a new bet
    betRoulette(roulette);
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
        //Since updateCurrentBet is called after checking that betList is not empty, this case should not happen. 
        std::cout<<"[Warning] Invalid list received when trying to update current bet in player "<<name;
        resetBetList(); 
    }

    if(currentBet > Roulette::MAX_BET || currentBet < Roulette::MIN_BET){
        resetBetList();
        updateCurrentBet();
    }
    
}

void Player::printPlayerInfo(bool won, float moneyBet) const{
    std::cout<< "\t- PlayerName: "<<name<<
                ", betType: "<<Roulette::getBetTypeName(defaultBetType)<<
                ", betList = {";
                for(auto n: betList){
                    std::cout<<n<<",";
                }
                std::cout<<"}"<<
                ", moneyBet = "<<moneyBet<<
                ", result = "<<(won?"Won":"Lost")<<
                std::endl;
}