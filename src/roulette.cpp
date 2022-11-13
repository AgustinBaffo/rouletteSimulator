#include "roulette.hpp"
#include "player.hpp"


Roulette::Roulette()
{
    srand((unsigned int)time(NULL));
    resetBetResult();
    lastSpinResult = 0;
}

Roulette::~Roulette()
{

}

void Roulette::spin(){
    
    // Get random number (spinning roulette).
    int spinResult = std::rand() % ROULETTE_MAX_NUMBER;
    setBetResult(spinResult);

    // Update bet result.
    updateBetTables();

    // Print results.
    printSpinResult();
}

void Roulette::setBetResult(int spinResult){

    resetBetResult();

    lastSpinResult = spinResult;

    if(spinResult==0){
        return;
    }
    
    if(spinResult<19){
        betResult[LOW] = true;
    } else { 
        betResult[HIGH] = true;
    }

    if(spinResult%2){
        betResult[ODD] = true;

        if (spinResult <= 10 || (spinResult > 18 && spinResult <= 28)){
            betResult[RED] = true;
        } else { 
            betResult[BLACK] = true;
        }

    } else {
        betResult[EVEN] = true;

        if (spinResult <= 10 || (spinResult > 18 && spinResult <= 28)){
            betResult[BLACK] = true;
        } else { 
            betResult[RED] = true;
        }
    }

}

void Roulette::resetBetResult(){
   betResult = {{RED, false}, 
                {BLACK, false}, 
                {EVEN, false}, 
                {ODD, false}, 
                {LOW, false}, 
                {HIGH, false}};
}

void Roulette::updateBetTables(){
    lastBetTable.clear();
    lastBetTable = currentBetTable;
    currentBetTable.clear();
}

void Roulette::printSpinResult(){
    std::cout<<"* Roulette result: "<<lastSpinResult;
    for(auto a: betResult){
        if(a.second){
            std::cout<<", "<<getBetTypeName(a.first);
        }
    }
    std::cout<<std::endl;
}

void Roulette::setBet(int playID, BetsTypes betType, float money) const{
    if(money<=0){
        return;
    }
    currentBetTable[playID] = bet{betType,money};
}

bool Roulette::payPlayer(int playerID, float &money) const{
    bool hasWon = false;
    money = 0;
    
    if (!(lastBetTable.find(playerID) == lastBetTable.end())) {
        if(betResult.at(lastBetTable.at(playerID).betType)){
            hasWon = true;
            money = betResult.at(lastBetTable.at(playerID).betType);
        }
    } else {
        std::cout<<"[Warning] Player "<< playerID <<" asked about a missing bet"<<std::endl;
    }

    return hasWon;
}

std::string Roulette::getBetTypeName(BetsTypes bet){
    std::string ret;
    switch (bet)
    {
    case RED:
        ret = "red";
        break;
    case BLACK:
        ret = "black";
        break;
    case EVEN:
        ret = "even";
        break;
    case ODD:
        ret = "odd";
        break;
    case LOW:
        ret = "low";
        break;
    case HIGH:
        ret = "high";
        break;
    default:
        ret = "unknown";
        break;
    }

    return ret;
}
