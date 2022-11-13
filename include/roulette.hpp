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

    struct bet{
        BetsTypes betType;
        float money;
    };

    typedef std::map<int,bet> BetTable;

    Roulette();
    ~Roulette();

    void spin();
    
    BetTable getBetTable() const;
    void setBet(int playID, BetsTypes betType, float money) const;

    float payPlayer(int playerID);
    std::string getBetTypeName(BetsTypes);

private:

    std::map<BetsTypes,bool> betResult;
    void setBetResult(int number);
    void resetBetResult();
    
    mutable BetTable betTable;
};

#endif