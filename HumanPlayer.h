#ifndef _HMPLAYER_H_
#define _HMPLAYER_H_

#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

class HumanPlayer : public Player {
public:
    HumanPlayer(string n);
    string getName();
    Card* lead();
    Card* throwOff();
    Card* followSuit(Card::Suit suit, Card::Rank rank);
};

#endif
