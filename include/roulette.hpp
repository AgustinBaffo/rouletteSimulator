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
    
    void setBet(int playID, BetsTypes betType, float money) const;

    bool payPlayer(int playerID, float &money) const;
    static std::string getBetTypeName(BetsTypes);


    BetTable getLastBetTable() const;

private:

    std::map<BetsTypes,bool> betResult;
    void setBetResult(int number);
    void resetBetResult();
    
    mutable BetTable currentBetTable;
    BetTable lastBetTable;
    void updateBetTables();

    int lastSpinResult;
    void printSpinResult();

};

#endif