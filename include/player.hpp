/**
* @file player.hpp
* @brief This file contains the definition of the player class.
* @version 1.0
* @date 11/14/2022
* @author Agustin Baffo
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <list>
#include "roulette.hpp"

/**
 * @class Player
 * @brief Player class used for casino player manipulations.
 * Each player object has a default bet that can be made in any roulette. 
 * Each player manages his own list of numbers to bet, and his own balance.
 */
class Player
{
public:

    /**
     * @brief Player default constructor. <br>
     * In addition to the variables passed as parameters, it assigns a playerID value 
     * and initializes the values of the list of bets (\ref betList) and the current bet (\ref currentBet).
     * @param name Player's name.
     * @param defaultBetType Player's default bet.
     * @param displayLog If set to TRUE, the player will write log to screen every round. 
     * Otherwise he does not write.
     * @see Player::betList
     * @see Player::currentBet
     * @see Player::name
     * @see Player::defaultBetType
     * @see Player::displayLog
     */
    Player(std::string name, Roulette::BetsTypes defaultBetType, bool displayLog);

    /**
     * @brief Player default destructor.
     */
    ~Player();

    /**
     * @brief Returns the \ref name of the Player object.
     * @return [std::string] \ref name
     */ 
    std::string getName() const;

    /**
     * @brief Returns the \ref balance of the Player object.
     * @return [int] \ref balance
     */ 
    int getBalance() const;

    /**
     * @brief Make the default bet (\ref defaultBetType) in a certain \ref Roulette.
     * Update the balance by withdrawing the money bet.
     * @param roulette Is the \ref Roulette in which the player is going to bet.
     */ 
    void betRoulette(const Roulette& roulette);

    /**
     * @brief Ask about the pay at \ref Roulette. Then updates the \ref balance.
     * It calls \ref updateBetList to update the \ref betList and the \ref currentBet.
     * Depending on the value set for \ref displayLog, it prints information on the screen.
     * @param roulette Is the \ref roulette in which the player asks for his pay.
     * @see Player::updateBetList()
     * @see Roulette::setBet()
     * @see Roulette::payPlayer()
     */ 
    void updateBets(const Roulette& roulette);

    
private:

	/**
	 * @brief It is a static variable that keeps track of the number
     * of players. Then it is possible to assign a unique value to \ref playerID.
     * @see Player::playerID
	 */
    static int playerCount;

	/**
	 * @brief Is a number that uniquely identifies each player.
     * @see Player::playerCount
	 */
    int playerID;

	/**
	 * @brief Name assigned to the player. 
     * The assignment is done in the constructor of the Player class.
     * @see Player::Player()
	 */
    std::string name;

	/**
	 * @brief It is the player's current balance. 
     * It is updated in each round adding the losses and gains of money.
     * @see Player::getBalance()
     * @see Player::betRoulette()
     * @see Player::updateBets()
	 */
    int balance;

    /**
     * @brief Default bet type for the player.
     * The assignment is done in the constructor of the Player class.
     * @see Player::Player()
     * @see Player::betRoulette
    */
    Roulette::BetsTypes defaultBetType;

    /**
     * @brief Each player has a list of numbers written down on a piece of paper
     * that starts with the values: [1,2,3,4]. The amount of money bet is 
     * the sum of the ends of the list. The initial value is [1,2,3,4].
     * So the initial bet is 1 + 4 = 5.
     * @see Player::updateBetList()
     * @see Player::currentBet
    */
    std::list<int> betList;

    /**
     * @brief Bet made by the player.
     * The amount of money bet is the sum of the ends of the \ref betList.
     * @see Player::betList
     * @see Player::updateBetList()
    */
    int currentBet;

    /**
     * @brief Reset \ref betList to default value [1,2,3,4].
     * @see Player::betList
     */ 
    void resetBetList();
    
    /**
     * @brief Update \ref betList based on the result of the previous bet.
     * If the player wins, he add the amount bet to the bottom of the list. 
     * If the player loses, he crosses out the two extreme numbers and the list gets smaller. 
     * In the next round the procedure is repeated. 
     * For example, if the player has the list [1,2,3,4] he will bet 5 (1+4=5). So:
     *  - If he wins, he add 5 to the list ([1,2,3,4,5]) and then he will bet 6 (1+5=6).
     *  - If he loses, he removes extremes from the list ([2,3]) and then he will bet 5 (2+3=5).
     * 
     * If the list runs out of numbers, the player also resets the list.
     * @see Player::betList
     * @see Player::resetBetList()
     */
    void updateBetList(bool hasWon);
    
    /**
     * @brief Updates \ref currentBet based on \ref betList.
     * The minimum bet is 5 and the maximum is 4000. 
     * If a player's next bet is outside of those values, it calls
     * \ref resetBetList() to reset the \ref betList to [1,2,3,4].
     * @see Player::betList
     * @see Player::currentBet
     * @see Player::resetBetList()
     */
    void updateCurrentBet();
        
    /**
     * @brief Print the player's data on the screen.
     * Printed data is:
     *  - \ref name
     *  - \ref defaultBetType
     *  - \ref betList
     *  - money bet in the last round.
     *  - result of the last round (if won or lost)
     *  - \ref balance
     * 
     * @see Player::displayLog
     */
    void printPlayerInfo(bool hasWon, int moneyBet, int balance) const;
    
    /**
     * @brief If set to TRUE, the player will write log to screen every round. 
     * The assignment is done in the constructor of the Player class.
     * @see Player::Player()
     * @see Player::printPlayerInfo()
     */
    bool displayLog;
};

#endif