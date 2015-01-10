#include <iostream>
#include <string>
#include <cassert>
#include "Card.h"
#include "HumanPlayer.h"
#include "Player.h"
using namespace std;

HumanPlayer::HumanPlayer(string name) : Player(name) {}

int search_pos (const char& rs, const string& rsname) {
    for (int i = 0; i < rsname.size(); i++) {
        if (rs == rsname[i]) {
            return i;
        }
    }
}

Card* HumanPlayer::lead(){
    int num_card;
    num_card = Hand.size();
    for (int i = 0; i < num_card-1; i++) {
        if (*Hand.at(i) == Card::TwoOfClubs) {
            return Hand.at(i);
        }
    }
    string cards;
    cout << "Human Player " << name << " has these cards:" << endl;
    print();
    while (1) {
        cout << "What card would you like to play, " << name << "? ";
        cin >> cards;
        if (!Card::stringIsALegalCard(cards)) {
            cout << cards << " is not a card" << endl;
            continue;
        }
        Card::Rank rank = static_cast<Card::Rank>(search_pos(cards[0],Card::RankName));
        Card::Suit suit = static_cast<Card::Suit>(search_pos(cards[1],Card::SuitName));
        for (int i = 0; i < num_card; i++){
            if (Hand.at(i) -> getRank() == rank && Hand.at(i) -> getSuit() == suit){
                return Hand.at(i);
            }
        }
        cout << cards << " is not in your hand" << endl;
    }
}

Card* HumanPlayer::throwOff(){
    int num_card;
    num_card = Hand.size();
    string cards;
    cout << "Human Player " << name << " has these cards:" << endl;
    print();
    while(1) {
        cout << "What card would you like to play, " << name << "? ";
        cin >> cards;
        if (!Card::stringIsALegalCard(cards)) {
            cout << cards << " is not a card" << endl;
            continue;
        }
        Card::Rank rank = static_cast<Card::Rank>(search_pos(cards[0],Card::RankName));
        Card::Suit suit = static_cast<Card::Suit>(search_pos(cards[1],Card::SuitName));
        for (int i = 0; i < num_card; i++){
            if (Hand.at(i) -> getRank() == rank && Hand.at(i) -> getSuit() == suit){
                return Hand.at(i);
            }
        }
        cout << cards << " is not in your hand" << endl;
    }
}

Card* HumanPlayer::followSuit(Card::Suit suit, Card::Rank rank){
    int cont_flag = 0;
    int num_card;
    num_card = Hand.size();
    string cards;
    cout << "Human Player " << name << " has these cards:" << endl;
    print();
    while(1) {
        cont_flag = 0;
        cout << "What card would you like to play, " << name << "? ";
        cin >> cards;
        if (!Card::stringIsALegalCard(cards)) {
            cout << cards << " is not a card" << endl;
            continue;
        }
        Card::Rank ranks = static_cast<Card::Rank>(search_pos(cards[0],Card::RankName));
        Card::Suit suits = static_cast<Card::Suit>(search_pos(cards[1],Card::SuitName));
        for (int i = 0; i < Hand.size(); i++) {
            if (Hand[i]->getSuit() == suits && Hand[i]->getRank() == ranks) {
                if (suit != suits) {
                    cout << "You have at least one " << Card::SuitName[suit] << "; you must follow suit!" << endl;
                    cont_flag = 1;
                    break;
                } else return Hand.at(i);
            }
        }
        if (cont_flag == 1) continue;
        cout << cards << " is not in your hand" << endl;
    }
}




