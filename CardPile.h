#ifndef _CARDPILE_H_
#define _CARDPILE_H_

using namespace std;

#include <vector>
#include "Card.h"
#include "PRNG.h"

class CardPile : private vector<Card*> {
    public:
        // Constructors and destructor
        CardPile ();
        virtual ~CardPile ();

        void setRandomSeed(uint32_t randomSeed);
        // Other stuff needed
	
        int heartsValue();
        virtual void print();

        using vector<Card*>::size;
        using vector<Card*>::push_back;
        using vector<Card*>::at;
	using vector<Card*>::clear;
    
        void shuffle();
    
    private:
        PRNG prng;
        static const uint32_t DefaultRandomSeed;
};

#endif 
