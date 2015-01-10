#include <iostream>
#include <cstdlib>
#include "Deck.h"
#include "Card.h"
//#include "CardPile.h"
#include <vector>

using namespace std;


Deck::Deck(){
    CardPile();
}

Deck::~Deck() {}

void Deck::generate() {
    for (int i = 0; i < Card::numSuits; i++) {
        for (int j = 0; j < Card::numRanks; j++) {
            Card::Suit nSuit = static_cast<Card::Suit>(i);
            Card::Rank nRank = static_cast<Card::Rank>(j);
            Card* nCard = new Card(nRank, nSuit);
            push_back(nCard);    
        }
    }
}

void Deck::clean() {
    for (int i = 0; i < size(); i++) {
        delete at(i);
    }
    clear();
}

bool Deck::playingWithAFullDeck() const {
    int exist[52] = {0};
    for (int i = 0; i < 52; i ++){
        Card* one_card = at(i);
        int a , b;
        a = one_card -> getRank();
        b = one_card -> getSuit() * 13;
        int position;
        position = a + b;
        exist[position] = 1;
    }
    for (int i = 0; i < 52; i++){
        if (exist[i] == 0){
            return false;
        }else{
            continue;
        }
    }
    return true;
    
}

istream& operator>> (istream& in, Deck& deck) {
    for (int j = 0; j < 52 ; j++){
        string card;
        in >> card;
        if (Card::stringIsALegalCard(card)) {
            Card* new_card = new Card(card);
            deck.push_back(new_card);    
        } else {
            cerr << "ERROR: Not a legal card" << endl;
            exit(1);
        }
    }
    if (deck.playingWithAFullDeck()){
        return in;
    } else {
        cerr << "Deck is not VALID" << endl;
        exit(1);
    }
}

void Deck::print(){
    cout << "    ";
    for (int i = 0; i< 52 ; i++){
        cout << *(at(i)) << " ";
    }
    cout << endl << endl;
}








