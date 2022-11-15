/**
* @file roulette.hpp
* @brief This file contains the definition of the roulette class.
* @version 1.0
* @date 11/14/2022
* @author Agustin Baffo
*/

#ifndef ROULETTE_H
#define ROULETTE_H

#include <iostream>
#include <map>
#include <string>

#define ROULETTE_MAX_NUMBER 37
#define ROULETTE_MINMAX_LIMIT 19


/**
 * @class Roulette
 * @brief Roulette class used for casino roulette manipulations. <br>
 * Roulette is a casino game in which a player may choose to place a bet 
 * on a single number or in a different groupings of numbers. Then a wheel is 
 * spun and a random number in the range [0.36] is obtained. Finally, the 
 * corresponding players are paid. You can read more about roulettes here: 
 * https://en.wikipedia.org/wiki/Roulette.
 */class Roulette
{
public:

    /**
     * @enum BetsTypes
	 * @brief Enum that contains the different types of 
     * bets that can be made in roulette.
	 */
    enum BetsTypes{
        RED,
        BLACK,
        EVEN,
        ODD,
        LOW,
        HIGH
    };

    /**
     * @struct bet
	 * @brief It is a structure that contains a particular bet. 
     * Each bet is represented by:
     *  - Roulette::BetsTypes: is the type of the bet.
     *  - money: amount of money bet
     * 
     * @see Roulette::BetsTypes
	 */
    struct bet{
        BetsTypes betType;
        int money;
    };

    /**
     * @typedef BetTable
	 * @brief It is a data type that represents a bet table. The bets 
     * made by all the players are saved in the table in each round. <br>
     * Each bet table is represented as a map, where:
     *  - [int] Key: is the id of the player (Player::playerID) who made the bet.
     *  - [Roulette::bet] Value: bet made by a player.
     * 
     * @see Roulette::bet
     * @see Player
     * @see Player::playerID
	 */
    typedef std::map<int,bet> BetTable;

    /**
     * @brief Minimum bet a player can make in each round
     */
    static const int MIN_BET = 5;

    /**
     * @brief Maximum bet a player can make in each round
     */
    static const int MAX_BET = 4000;


    /**
     * @brief It converts Roulette::BetsTypes to a std::string which 
     * can be used for display.
     * @param type: one type from the Roulette::BetsTypes.
     * @return [std::string] name: string containing the name of the type of bet.
     */
    static std::string getBetTypeName(BetsTypes type);

    /**
     * @brief Roulette default constructor. <br>
     * Initializes random number generators. 
     * It also initializes the result of the last round.
     * @param displayLog If set to TRUE, the roulette will write log to screen every round. 
     * Otherwise he does not write.
     * @see Roulette::lastSpinResult
     * @see Roulette::betResult
     */
    Roulette(bool displayLog);

    /**
     * @brief Roulette default destructor.
     */
    ~Roulette();

    /**
     * @brief Spin the roulette. <br> It generates a random number in range 
     * [0,36] and writes the result in the Roulette::betResult table. It also updates 
     * the bet tables, by calling Roulette::updateBetTables(). If Roulette::displayLog 
     * is set, it also prints the information of the round.
     * @see Roulette::updateBetTables()
     * @see Roulette::setBetResult()
     * @see Roulette::printSpinResult()
     */
    void spin();

    /**
     * @brief The method is used every time a player wants to make a new bet. <br>
     * This updates the current bet table Roulette::currentBetTable.
     * @param playerID ID of the player who is betting.
     * @param betType type of the bet.
     * @param money amount of money bet.
     * @see Roulette::BetsTypes
     * @see Player::playerID
     * @see Player::playerID
     */
    void setBet(int playerID, BetsTypes betType, int money) const;


    /**
     * @brief Players can call this method to collect the money they won
     * in the last round. <br>
     * Use information from tables Roulette::lastBetTable and Roulette::betResult 
     * and from the playerID to know how much money to pay to a player.
     * @return [int] money: amount of money to pay to a Player.
     * @see Player::updateBets
     * @see Player::playerID
     * @see Roulette::lastBetTable
     * @see Roulette::betResult
     */
    int payPlayer(int playerID) const;

private:

    /**
	 * @brief A map that contains the result of each type of bet. 
     * The key of the map is the bet type from Roulette::BetsTypes and the 
     * value is a bool that indicates if this type of bet won or not 
     * in the previous round.
     * @see Roulette::BetsTypes
	 */
    std::map<BetsTypes,bool> betResult;

    /**
	 * @brief Updates results table values Roulette::betResult depending on the 
     * information of the current round, according to the number selected 
     * randomly in Roulette::spin().
     * @param number is the randomly selected value in Roulette::spin().
     * @see Roulette::spin()
     * @see Roulette::betResult
	 */
    void setBetResult(int number);

    /**
	 * @brief Resets the values in Roulette::betResult 
     * setting each value to the default value FALSE.
     * @see Roulette::betResult
	 */
    void resetBetResult();
    
    /**
     * @brief Stores the current bets of each Player. <br>
     * Each Player can place a bet using the Roulette::setBet() method.
     * @see Roulette::setBet()
     * @see Roulette::BetTable
     * @see Roulette::updateBetTables()
     */
    mutable BetTable currentBetTable;
    
    /**
     * @brief Stores the bets of each Player in the last round. <br>
     * It is updated after each spin with the information from 
     * Roulette::currentBetTable, in the Roulette::updateBetTables() method.
     * @see Roulette::BetTable
     * @see Roulette::currentBetTable
     * @see Roulette::updateBetTables()
     */
    BetTable lastBetTable;
    
    /**
     * @brief After each spin, it updates the result of the bet tables.
     * <br> The Roulette::lastBetTable is filled with the information of the 
     * round and Roulette::currentBetTable the table is emptied.
     * @see Roulette::BetTable
     * @see Roulette::currentBetTable
     * @see Roulette::lastBetTable
     */
    void updateBetTables();

    /**
     * @brief Stores the last number that was randomly selected on the Roulette.
     */
    int lastSpinResult;

    /**
     * @brief If Roulette::displayLog is set, it prints information about 
     * the last round of roulette. <br>
     * It shows the winning number and the winning bet types from the 
     * Roulette::betResult table.
     * @see Roulette::displayLog
     * @see Roulette::lastSpinResult
     * @see Roulette::betResult
     */
    void printSpinResult();

    /**
     * @brief If set to TRUE, the roulette will write log to screen every round. 
     * The assignment is done in the constructor of the Roulette class.
     * @see Roulette::Roulette()
     * @see Roulette::printSpinResult()
     */
    bool displayLog;

};

#endif