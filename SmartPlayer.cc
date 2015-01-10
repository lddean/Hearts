#include <iostream>
#include <string>
#include "SmartPlayer.h"
#include "Player.h"
using namespace std;

SmartPlayer::SmartPlayer(string name) : Player(name){}

Card* SmartPlayer::lead(){
    Card* lower;
    lower = Hand.at(0);
    if (*lower == Card::TwoOfClubs){
        return Hand.at(0);
    }
    int lowest_posn = 0;
    int num_cards;
    num_cards = Hand.size();
    for (int i = 1 ; i < num_cards; i++){
        if (*Hand.at(i) == Card::TwoOfClubs){
            return Hand.at(i);
        }
        if ( *Hand.at(i) < *lower){
            lower = Hand.at(i);
            lowest_posn = i;
        }
    }
    return lower;
}

Card* SmartPlayer::throwOff(){
    int num_cards;
    num_cards = Hand.size();
    for (int i = 0; i< num_cards; i++){
        Card::Suit  black;
        black = Hand.at(i) -> getSuit();
        if (black == Card::Spades && Hand.at(i) -> getRank() == Card::Queen){
            return Hand.at(i);
        }
    }
    int max_posn = -1;
    Card::Rank max;
    for (int i = 0; i < num_cards; i++){
        if (Hand.at(i)->getSuit() == Card::Hearts && max_posn < 0){
            max = Hand.at(i)-> getRank();
            max_posn = i;
        }else if( Hand.at(i)-> getSuit() == Card::Hearts){
            if ( Hand.at(i) -> getRank() > max){
                max = Hand.at(i) -> getRank();
                max_posn = i;
            }
        }else{
            continue;
        }
    }
    if (max_posn >= 0){
        return Hand.at(max_posn);
    }else{
        Card::Suit kinds;
        kinds = Hand.at(0)->getSuit();
        max = Hand.at(0)->getRank();
        max_posn = 0;
        for (int i = 1; i < num_cards; i++){
            if (Hand.at(i) -> getRank() > max){
                max = Hand.at(i) -> getRank();
                kinds = Hand.at(i) -> getSuit();
                max_posn = i;
            }else if (Hand.at(i) -> getRank() == max && Hand.at(i) -> getSuit() > kinds){
                max_posn = i;
                kinds = Hand.at(i) -> getSuit();
            }else{
                continue;
            }
        }
        return Hand.at(max_posn);
    }
}

Card* SmartPlayer::followSuit(Card::Suit suit, Card::Rank rank){
    int num_cards;
    num_cards = Hand.size();
    int max_posn = -1;
    int min_posn = -1;
    Card::Rank max;
    Card::Rank min;
    for (int i = 0; i < num_cards; i++){
        if (Hand.at(i)->getSuit() == suit && max_posn < 0){
            max = Hand.at(i) -> getRank();
            min = Hand.at(i) -> getRank();
            max_posn = i;
            min_posn = i;
        }else if( Hand.at(i) -> getSuit() == suit){
            if ( Hand.at(i) -> getRank() > max){
                max = Hand.at(i) -> getRank();
                max_posn = i;
            }
            if (Hand.at(i) -> getRank() < min){
                min = Hand.at(i) -> getRank();
                min_posn = i;
            }
        }else{
            continue;
        }
    }
    if (max < rank){
        return Hand.at(max_posn);
    }else if (min > rank){
        return Hand.at(min_posn);
    }else{
        int max_posn1 = -1;
        Card::Rank max1 = min;
        for (int i = 0; i < num_cards; i++){
            if (Hand.at(i)->getSuit() == suit && max_posn1 < 0){
                if (Hand.at(i) -> getRank() >= max1 && Hand.at(i) -> getRank() <= rank){
                    max1 = Hand.at(i) -> getRank();
                    max_posn1 = i;
                }
            }else if (Hand.at(i)->getSuit() == suit && Hand.at(i) -> getRank() >= max1 && Hand.at(i) -> getRank() <= rank){
                max1 = Hand.at(i) -> getRank();
                max_posn1 = i;
            }else{
                continue;
            }
        }
        return Hand.at(max_posn1);
    }
}