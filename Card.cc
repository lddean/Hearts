#include <string>
#include <cassert>
#include <iostream>
#include "Card.h"

using namespace std;

const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);

int find_pos (const char& rs, const string& rsname) {
    for (int i = 0; i < rsname.size(); i++) {
        if (rs == rsname[i]) {
            return i;
        }
    }
}

// We'll give you this one.
Card::Card() : rank(Ace), suit(Spades) {}

// Now you do the rest.
Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Card::Card(string sCard) : rank(static_cast<Rank>(find_pos(sCard[0], RankName))), suit(static_cast<Suit>(find_pos(sCard[1], SuitName))) {}

Card::~Card() {}

Card::Rank Card::getRank() const {
    return rank;
}

Card::Suit Card::getSuit() const {
    return suit;
}

int Card::getHeartsValue() const {
    if (suit == Hearts) return 1;
    else if (suit == Spades && rank == Queen) return 13;
    else return 0;
}

bool Card::stringIsALegalCard (string s) {
    if (s.length() != 2) return false;
    size_t rpos = RankName.find(s[0]);
    size_t spos = SuitName.find(s[1]);
    if (rpos != string::npos && spos != string::npos) {
        return true;
    } else {
        return false;
    }
}

bool operator== (const Card& c1, const Card& c2) {
    if (c1.getRank() == c2.getRank() && c1.getSuit() == c2.getSuit()) {
        return true;
    } else {
        return false;
    }
}

bool operator< (const Card& c1, const Card& c2) {
    if (c1.getRank() < c2.getRank() || (c1.getRank() == c2.getRank() && c1.getSuit() < c2.getSuit())) {
        return true;
    }else{
        return false;
    }
}

ostream& operator<< (ostream &out, const Card &c) {
    out << c.RankName[c.getRank()] << c.SuitName[c.getSuit()];
    return out;
}
istream& operator>> (istream& in, Card& c) {
    string rs;
    in >> rs;
    c = Card(rs);
    return in;
}
