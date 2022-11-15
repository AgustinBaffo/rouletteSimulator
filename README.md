# Roulette Simulator

### This repository contains a roulette simulator developed in C++.

## Project Description

Roulette is a casino game in which a player may choose to place a bet on a single number or in different groups of numbers. Then a wheel is spun and a random number in the range [0.36] is obtained. Finally, the corresponding players are paid.
You can read more about roulettes in this [link](https://en.wikipedia.org/wiki/Roulette).

In this simulator, players can place only the following simple bets:
* If the number will be high or low. A low number is in range [1,18] and a high number is in [19,36].
* If the color of the number will be red or black.
* If the number will be even or odd.

Note that when 0 is the selected number, everyone loses.

In this simulator, 6 players participate. Each player always makes the same bet in each round:
* Player A bet on red numbers.
* Player B bet on black numbers.
* Player C bet on high numbers.
* Player D bet on low numbers.
* Player E bet on even numbers.
* Player F bet on odd numbers.

Each player has a list of numbers written down on a piece of paper that starts with the values: [1,2,3,4]. The amount of money to bet is the sum of the ends of the list. If the player wins, he add the amount bet to the bottom of the list. If the player loses, he crosses out the two extreme numbers and the list gets smaller. In the next round the procedure is repeated.
For example, if the player has the list [1,2,3,4] he will bet 5 (1+4=5). So:
* If he wins, he add 5 to the list ([1,2,3,4,5]) and then he will bet 6 (1+5=6).
* If he loses, he removes the extremes from the list ([2,3]) and then he will bet 5 (2+3=5).

The minimum bet is 5 and the maximum is 4000. If a player's next bet is outside of those values, the player resets the list to [1,2,3,4]. If the list runs out of numbers, the player also resets the list.

The simulation runs for 10,000 rounds. At the end of the round the individual winnings of each player and the total winnings are calculated.


## Documentation

You can found the code documentation in this [link](https://abaffo.github.io/rouletteSimulator/documentation/html/) (created with [Doxygen](https://doxygen.nl/)).

## Install and run

1. Clone the project repository:
```bash
git clone https://github.com/abaffo/rouletteSimulator.git
```

2. Go to the root folder of the repository and build the project using make.
```bash
cd rouletteSimulator
make
```

3. The executable file will be located in the bin folder. you can run it as follows:
```bash
./bin/roulette
```

If you want to run the program a number of times other than 10,000, you can use `-n` paramter to set the amount. The value must be an integer in the range [1, 999999].
```bash
./bin/roulette -n 10
```

Also the program can be executed with `-v` param to show a log with the information of each round:
```bash
./bin/roulette -v
```

You can use `-h` option for help with the arguments.
