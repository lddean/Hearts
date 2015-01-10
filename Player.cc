#include <iostream>
#include <string>
#include "Player.h"
//#include "Card.h"
using namespace std;

Player::Player(string name) : name(name) {}


string Player::getName() {
    return name;
}

void Player::print() {
    cout << "    ";
    for (int i = 0; i < Hand.size(); i++) {
        cout << *(Hand[i]) << " ";
    }
    cout << endl;
}

void Player::addCard (Card* card) {
    Hand.push_back(card);
}

void Player::removeCard (Card* card) {
    for (int i = 0; i < Hand.size(); i++) {
        if ((*Hand[i]) == *card) {
            Hand.erase(Hand.begin() + i);
        }
    }
}

bool Player::existSuit (Card::Suit suit) {
    for (int i = 0; i < Hand.size(); i++) {
        if (Hand[i]->getSuit() == suit) {
            return true;
        }
    }
    return false;
}

