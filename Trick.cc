//
//  Trick.cpp
//  a6
//
//  Created by LDDean on 12-11-28.
//  Copyright (c) 2012年 Ivan Chau. All rights reserved.
//

#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "CardPile.h"
#include <vector>
#include "Trick.h"


using namespace std;


Trick::Trick() : CardPile(), loser(0), total(0), position(0) {
    for (int i = 0; i < 4 ; i++){
        player[i] = 0;
    }
    trump = NULL;
}

Trick::~Trick(){}

void Trick::readCard(Card* cards, int player){
    push_back(cards);
    this -> player[position] = player;  
    position = position + 1;
    if (trump == NULL){
        trump = cards;
    }else{
        if (trump -> getSuit() == cards -> getSuit() && trump->getRank() < cards -> getRank()){
            trump = cards;
        }
    }
    //cout << "trump cards" << *trump << endl;
}

void Trick::calculate(){
    Card::Suit lead;
    lead = at(0) -> getSuit();
    Card::Rank max;
    max = at(0) -> getRank();
    loser = player[0];
    /*
    if (lead == Card::Hearts) {
        total ++;
    }
    */
    for (int i = 1 ; i <= 3 ;i++){
        Card::Suit now_suit;
        now_suit = at(i) -> getSuit();
        /*
        if (now_suit != lead) {
            if ( now_suit == Card::Hearts){
                total ++;
            }
            if ( now_suit == Card::Spades && at(i) -> getRank() == Card::Queen){
                total = total + 13;
            }
            */
        Card::Rank now_rank;
        now_rank = at(i) -> getRank();
        /*
        if (now_rank == max){
            cerr << "Card was being played!!";
            exit(1);
        }
        */
        if (now_rank > max && now_suit == lead) {
            max = now_rank;
            loser = player[i];       
            /*
            if ( now_suit == Card::Hearts){
                total ++;
            }
            if ( now_suit == Card::Spades && at(i) -> getRank() == Card::Queen){
                total = total + 13;
            }
        }else{
            if ( now_suit == Card::Hearts){
                total ++;
            }
            if ( now_suit == Card::Spades && at(i) -> getRank() == Card::Queen){
                total = total + 13;
            }
            */
        }
    }
    total = heartsValue();
}

int Trick::getLoser(){
    return loser;
}


int Trick::getPoints(){
    return total;
}

Card* Trick::gettrump(){
    return trump;
}


void Trick::print(){
    cout << "    ";
    for (int i = 0; i < 4 ; i++){
        cout << *(at(i)) << " ";
    }
    cout << endl << endl;
}




