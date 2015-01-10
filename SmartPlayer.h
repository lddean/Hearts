#ifndef _SMARTPLAYER_H_
#define _SMARTPLAYER_H_

#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

class SmartPlayer : public Player {
    public:
        SmartPlayer(string n);
        string getName();
        Card* lead();
        Card* throwOff();
        Card* followSuit(Card::Suit suit, Card::Rank rank);
};

#endif
