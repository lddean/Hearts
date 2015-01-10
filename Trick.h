//
//  Trick.h
//  a6
//
//  Created by LDDean on 12-11-28.
//  Copyright (c) 2012年 Ivan Chau. All rights reserved.
//

#ifndef a6_Trick_h
#define a6_Trick_h

#include "CardPile.h"
#include <vector>

using namespace std;


class Trick : public CardPile {
    public:
    Trick ();
    void readCard(Card* card, int players);
    void calculate();
    virtual ~Trick();
    int getLoser();
    int getPoints();
    Card* gettrump();
    void print();
private:
    int loser;
    int total;
    int position;
    int player[4];
    Card *trump;
};


#endif
