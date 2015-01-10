#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <vector>
#include <string>
#include "Card.h"
using namespace std;

class Player {
    public:
        Player(string name);
        void print();
        string getName();
        void addCard(Card* card);
        void removeCard (Card* card);
        bool existSuit (Card::Suit suit);
        virtual Card* lead() = 0;
        virtual Card* throwOff() = 0;
        virtual Card* followSuit(Card::Suit suit, Card::Rank rank) = 0;
    protected:
        vector<Card*> Hand;
        string name;
};

#endif