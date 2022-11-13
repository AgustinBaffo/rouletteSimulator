#ifndef ROULETTE_H
#define ROULETTE_H

#include <iostream>
#include <map>
#include <string>

class Roulette
{
public:

    enum BetsTypes{
        RED,
        BLACK,
        EVEN,
        ODD,
        LOW,
        HIGH
    };

    Roulette();
    ~Roulette();

    void spin();
    
private:

    std::map<BetsTypes,bool> betResult;
    void setBetResult(int number);
    void resetBetResult();
    
    std::string getBetTypeName(BetsTypes);


};

#endif