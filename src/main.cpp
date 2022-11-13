#include <iostream>
#include <string.h>
#include <vector>

#include "roulette.hpp"
#include "player.hpp"

#define SPIN_NUMBER 10

void help();

int main(int argc, char* argv[]){

    // Parse args.
    bool verbose = false;
    for (int i = 1; i < argc; ++i){
        if(!strcmp(argv[i], "-h")){
            help();
            std::exit(0);
        }
        
        if(!strcmp(argv[i], "-v")){
            verbose = true;
        }
    }

    std::cout<<"*******************************"<<std::endl;
    std::cout<<"* STARTING ROULETTE SIMULATOR *"<<std::endl;
    std::cout<<"*******************************"<<std::endl;


    // Instance roulette.
    Roulette roulette;
    
    // Initialize players vector.
    std::vector<Player> players = {
        Player("A", Roulette::RED),
        Player("B", Roulette::BLACK),
        Player("C", Roulette::HIGH),
        Player("D", Roulette::LOW),
        Player("E", Roulette::EVEN),
        Player("F", Roulette::ODD),
    };

    // Make the first bet.
    for(auto& p: players){
        p.betRoulette(roulette);
    }
    
    // Main loop: the roulette is spun and then the players update their bets.
    // They teke their profits based on the result of the roulette and make a new bet.
    for (int spinCounter = 1; spinCounter<=SPIN_NUMBER; spinCounter++){
        
        std::cout<<"------------------------------"<<std::endl;
        std::cout<<"* Spin number: "<<spinCounter<<std::endl;

        // Spin roulette.
        roulette.spin();

        // Take profit and make and bet again.
        std::cout<<"* Players results: "<<std::endl;
        for(auto& p: players){
            p.updateBets(roulette);
        }
    }

    std::cout<<"\n================================"<<std::endl;
    std::cout<<"Simulation end!"<<std::endl;
    std::cout<<"* Final balance for each player: "<<std::endl;
    int totalBalance = 0;
    for(auto const &p: players){
        int playerBalance = p.getBalance();
        totalBalance+=playerBalance;
        std::cout<<"\t- Player "<<p.getName()<<": "<<playerBalance<<std::endl;
    }

    std::cout<<"* Ending total balance (all the players together): "<<totalBalance<<std::endl;

    return 0;
}

void help(){
    std::cout << "TODO: help!" << std::endl;
}

