/**
* @file main.cpp
* @brief Program entry point create to run a simulation
* of 6 players who bet on the same roulette wheel.
* @version 1.0
* @date 11/14/2022
* @author Agustin Baffo
*/

#include <iostream>
#include <string.h>
#include <vector>
#include <chrono>

#include "roulette.hpp"
#include "player.hpp"

#define DEFAULT_SPIN_NUMBER 10000
#define MAX_SPIN_NUMBER 999999

void help();

int main(int argc, char* argv[]){

    // Parse args.
    bool verbose = false;
    int spinNumber = DEFAULT_SPIN_NUMBER;

    for (int i = 1; i < argc; ++i){
        if(!strcmp(argv[i], "-h")){
            help();
            std::exit(0);
        }
        
        if(!strcmp(argv[i], "-v")){
            verbose = true;
        }

        if(!strcmp(argv[i], "-n")){
            spinNumber = std::atoi(argv[i+1]);
            if(spinNumber<1 || spinNumber>MAX_SPIN_NUMBER){
                std::cout<<"Invalid amount of round. "<<
                           "Must be between [0,"<<MAX_SPIN_NUMBER<<"]. "<<
                           "(Read: "<<spinNumber<<")."<<std::endl;
                std::exit(0);
            }
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
    // 1_ The players place their bets.
    // 2_ Then the roulette is spun.
    // 3_ Finally the player take their profits.
    for (int spinCounter = 1; spinCounter<=spinNumber; spinCounter++){
        
        if(verbose){
            std::cout<<"------------------------------"<<std::endl;
            std::cout<<"* Spin number: "<<spinCounter<<std::endl;
        }

        // Place the bet.
        for(Player* p: players){
            p->betRoulette(roulette);
        }
    
        // Spin roulette.
        roulette.spin();

        // Take profit.
        if(verbose){
            std::cout<<"* Players result: "<<std::endl;
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

    for(auto p: players){
        delete p;
    }

    return 0;
}

void help(){
    std::cout << "ROULETTE SIMULATOR" << std::endl<<std::endl;
    std::cout << "Roulette is a casino game in which a player may choose to place a bet on a single "
                 "number or in a different groupings of numbers. Then a wheel is spun and a random number "
                 "in the range [0.36] is obtained. Finally, the corresponding players are paid."
                 "You can read more about roulettes in this https://en.wikipedia.org/wiki/Roulette."<<std::endl<<std::endl;
    std::cout << "This simulator runs a number of roulette rounds (by default 10,000) and simulates 6 "
                 "players betting. Each player always makes the same bet, and at the end the personal and "
                 "joint balances are calculated. See more here: "
                 "https://github.com/abaffo/rouletteSimulator/blob/main/README.md"<<std::endl<<std::endl;
    std::cout << "The program can be executed with the following options:" << std::endl<<std::endl;
    std::cout << "\t-h\t\t Help." << std::endl<<std::endl;
    std::cout << "\t-v\t\t Vervosity. Writes a log on the screen in each round." << std::endl<<std::endl;
    std::cout << "\t-n <rounds>\t Change the number of rounds played (default 10,000)."
                 "rounds number must by in range [1,999999]." << std::endl<<std::endl;
}
