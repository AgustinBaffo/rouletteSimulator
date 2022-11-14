#include <iostream>
#include <string.h>
#include <vector>
#include <chrono>

#include "roulette.hpp"
#include "player.hpp"

#define SPIN_NUMBER 10000

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
    Roulette roulette(verbose);
    
    // Initialize players vector.
    std::vector<Player*> players = {
        new Player("A", Roulette::RED, verbose),
        new Player("B", Roulette::BLACK, verbose),
        new Player("C", Roulette::HIGH, verbose),
        new Player("D", Roulette::LOW, verbose),
        new Player("E", Roulette::EVEN, verbose),
        new Player("F", Roulette::ODD, verbose),
    };

    // Save start time.
    auto start = std::chrono::high_resolution_clock::now();

    // Main loop: 
    // 1_ The players make their bets.
    // 2_ Then the roulette is spun.
    // 3_ Finally the player take their profits.
    for (int spinCounter = 1; spinCounter<=SPIN_NUMBER; spinCounter++){
        
        if(verbose){
            std::cout<<"------------------------------"<<std::endl;
            std::cout<<"* Spin number: "<<spinCounter<<std::endl;
        }

        // Make the bet.
        for(Player* p: players){
            p->betRoulette(roulette);
        }
    
        // Spin roulette.
        roulette.spin();

        // Take profit
        if(verbose){
            std::cout<<"* Players results: "<<std::endl;
        }
        for(Player* p: players){
            p->updateBets(roulette);
        }
    }

    // Calculate execution duration time.
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<
                            std::chrono::milliseconds>(stop - start);

    // Show balance result.
    std::cout<<"\n================================"<<std::endl;
    std::cout<<"Simulation end!"<<std::endl;
    std::cout<<"* Final balance for each player: "<<std::endl;
    int totalBalance = 0;
    for(Player const* p: players){
        int playerBalance = p->getBalance();
        totalBalance+=playerBalance;
        std::cout<<"\t- Player "<<p->getName()<<": "<<playerBalance<<std::endl;
    }

    std::cout<<"* Ending total balance (all the players together): "<<
                        totalBalance<<std::endl;

    // Show execution duration time:
    std::cout<<std::endl<<"execution duration time: "<<
                        duration.count()<<"ms"<<std::endl;

    return 0;
}

void help(){
    std::cout << "TODO: help!" << std::endl;
}

