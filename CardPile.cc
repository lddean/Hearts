#include <vector>
#include <algorithm>
#include <iostream>
#include "CardPile.h"
//#include "Card.h"

const uint32_t CardPile::DefaultRandomSeed = 37;

CardPile::CardPile() : prng(DefaultRandomSeed) {}

void CardPile::setRandomSeed(uint32_t randomSeed) {
	prng.seed(randomSeed);
}

using namespace std;


// Other stuff

CardPile::~CardPile() {}

void CardPile::shuffle() {
	for (int i = size() - 1; i > 0; i--) {
		const int j = prng(i);
		Card* tmp = at(j);
		at(j) = at(i);
		at(i) = tmp;
	}
}

int CardPile::heartsValue() {
	int heart = 0;
	for (int i = size() - 1; i >= 0; i--) {
		if (*at(i) == Card::QueenOfSpades) heart += 13;
		if (at(i)->getSuit() == Card::Hearts) heart++;
	}
	return heart;
}


void  CardPile::print(){
    for (int i = 0; i < 52 ; i++){
        cout << *(at(i)) << " ";
    }
}
