#ifndef _RANDOMPLAYER_H_
#define _RANDOMPLAYER_H_

#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

class RandomPlayer : public Player {
    public:
        RandomPlayer(string n, int s);
        Card* lead();
        Card* throwOff();
        Card* followSuit(Card::Suit suit, Card::Rank rank);
    private:
        int seed;
        PRNG prng;
};

#endif