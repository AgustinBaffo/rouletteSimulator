#include <iostream>
#include <string.h>
#include <vector>

#include "roulette.hpp"
#include "player.hpp"

#define SPIN_NUMBER 1

void help();

int main(int argc, char* argv[]){

    for (int i = 1; i < argc; ++i){
        if(!strcmp(argv[i], "-h")){
            help();
            std::exit(0);
        }
    }

    std::cout<<"*******************************"<<std::endl;
    std::cout<<"* STARTING ROULETTE SIMULATOR *"<<std::endl;
    std::cout<<"*******************************"<<std::endl;

    // Initialize players vector
    std::vector<Player> players = {
        Player("A", Roulette::RED),
        Player("B", Roulette::BLACK),
        Player("C", Roulette::HIGH),
        Player("D", Roulette::LOW),
        Player("E", Roulette::EVEN),
        Player("F", Roulette::ODD),
    };

    // Instance roulette
    Roulette roulette;

    // betTable.clear(); // TODO clear previous bets
    // Make the first bet
    for(auto p: players){
        p.betRoulette(roulette);
    }

    for (int spinCounter = 0; spinCounter<SPIN_NUMBER; spinCounter++){
        
        // Print output
        std::cout<<"------------------------------"<<std::endl;
        std::cout<<"* Spin number: "<<spinCounter<<std::endl;
        std::cout<<"* Players bets: "<<std::endl;
        Roulette::BetTable betTable = roulette.getBetTable();
        for(auto a: betTable){
            std::cout<<"\t - PlayerID: "<<a.first<<", betType: "<<roulette.getBetTypeName(a.second.betType)<<", Money = "<<a.second.money<< std::endl;
        }

        // Spin roulette
        roulette.spin();
    
        std::cout<<"* Players results: "<<std::endl;
        // Take profit and make and bet again
        for(auto p: players){
            // p.updateBets(roulette);
            roulette.payPlayer(p.getID());
        }
    }

    return 0;
}

void help(){
    std::cout << "TODO: help!" << std::endl;
}