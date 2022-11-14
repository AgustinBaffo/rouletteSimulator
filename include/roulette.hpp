#ifndef ROULETTE_H
#define ROULETTE_H

#include <iostream>
#include <map>
#include <string>

#define ROULETTE_MAX_NUMBER 37
#define ROULETTE_MINMAX_LIMIT 19

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
        int money;
    };

    typedef std::map<int,bet> BetTable;

    static const int MIN_BET = 5;
    static const int MAX_BET = 4000;
    static std::string getBetTypeName(BetsTypes);

    Roulette(bool displayLog);
    ~Roulette();

    void spin();
    void setBet(int playID, BetsTypes betType, int money) const;
    int payPlayer(int playerID) const;

private:

    bool displayLog;

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