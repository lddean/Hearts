#include <iostream>
#include <string>
#include "PRNG.h"
#include "RandomPlayer.h"
using namespace std;

RandomPlayer::RandomPlayer(string name, int seed) : Player(name), seed(seed) {
    prng = PRNG(seed);
}

Card* RandomPlayer::lead(){
    int num_cards;
    num_cards = Hand.size();
    for (int i =0 ; i < num_cards ; i++){
        if (*Hand.at(i) == Card::TwoOfClubs){
            return Hand.at(i);
        }
    }
    int j = prng(num_cards - 1);
    return Hand.at(j);
}

Card* RandomPlayer::throwOff(){
    int num_cards;
    num_cards = Hand.size();
    int j = prng(num_cards - 1);
    return Hand.at(j);
}

Card* RandomPlayer::followSuit(Card::Suit suit, Card::Rank rank){
    int num_cards;
    num_cards = Hand.size();
    int following = 0;
    for (int i = 0 ; i < Hand.size(); i++){
        if (Hand.at(i) -> getSuit() == suit){
            following ++;
        }
    }
    int j = prng(following - 1) + 1;
    for (int i = 0 ; i < Hand.size(); i++){
        if (Hand.at(i) -> getSuit() == suit){
            j = j - 1;
            if (j == 0){
                return Hand.at(i);
            }
        }

    }
}