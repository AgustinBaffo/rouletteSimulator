/**
* @file roulette.cpp
* @brief This file contains the definition of the roulette class.
* @version 1.0
* @date 11/14/2022
* @author Agustin Baffo
*/

#include "roulette.hpp"
#include "player.hpp"

Roulette::Roulette(bool displayLog):
    displayLog(displayLog)
{
    // Initialize random number generators.
    srand((unsigned int)time(NULL));

    // Reset roulette result.
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

    // Print result.
    if(displayLog){
        printSpinResult();
    }
}

void Roulette::setBetResult(int spinResult){

    // Set all values to false.
    resetBetResult();

    // Update last result.
    lastSpinResult = spinResult;

    // If resilt is 0, nobody wins.
    if(spinResult==0){
        return;
    }
    
    // Set result for low or high bet.
    if(spinResult<ROULETTE_MINMAX_LIMIT){
        betResult[LOW] = true;
    } else { 
        betResult[HIGH] = true;
    }


    // Set result even or odd bet and also for color bet.
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

void Roulette::setBet(int playerID, BetsTypes betType, int money) const{
    
    // Check the amount of money is valid.
    if(money<=0){
        return;
    }

    // Update current bet table.
    currentBetTable[playerID] = bet{betType,money};
}

int Roulette::payPlayer(int playerID) const{
    int moneyWon = 0;
    
    // Check if player with playerID has bet in the last round.
    if (!(lastBetTable.find(playerID) == lastBetTable.end())) {


        // Check if the player won and pay him with with double the money he bet.
        if(betResult.at(lastBetTable.at(playerID).betType)){
            moneyWon = 2 * lastBetTable.at(playerID).money;
        }

    } else {
        std::cout<<"[Warning] Player "<< playerID <<" asked about a missing bet"<<std::endl;
    }

    return moneyWon;
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
