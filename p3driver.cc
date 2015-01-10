#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Card.h"
#include "Deck.h"
#include "Trick.h"
#include "Player.h"
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
using namespace std;

// This is the Card game - HEARTS
// Fours players will be playing the game and the gaol is achieving the lowest score
// All cards with the suit heart will receive 1 point and Queen of Spades will receive 13 points
// There are four main options at the beginning of game
// "-r" set the seed of deck when it is shuffled, "-s" is setting the max score of the game
// "-d" pass in a file with cards in it and "-p" is manually setting the players of the game
//
// 3 Strategies are used when players put their card: lead, followSuit and throwoff
// If he/she is the first player of the round, then it will use lead
// If the player has cards with the same suit as leadCard, then it will use followSuit
// Otherwise, it will just throwOff a Card

int main(int argc, char* argv[]) {

    int seed = 37;
    int maxScore = 40;
    int maxPlayers = 4;
    Player* plyList[4];
    
    Deck* newDeck = new Deck;
    
    
    // Indicator for -d and -p options
    int dOn = 0;
    int pOn = 0;
    
    // Four options of the game
    for (int i = 1; i < argc;) {
        string option = argv[i];
        
        if (option == "-r") {
            if (dOn == 1) {
                cerr << "ERROR: option -r must occur before -d" << endl;
                exit(1);
            }
            seed = atoi(argv[i+1]);
            i = i + 2;
        }
        
        else if (option == "-s") {
            maxScore = atoi(argv[i+1]);
            if (maxScore <= 0) {
                cerr << "ERROR: Maxscore must be positive" << endl;
                exit(1);
            }
            i = i + 2;
        }
        
        else if (option == "-d") {
            ifstream file;
            file.open(argv[i+1]);
            if (file.good()) {
                file >> *newDeck;
                file.close();
                i = i + 2;
                dOn = 1;
            } else {
                cerr << "ERROR: Cannot open file" << endl;
                exit(1);
            }
        }
        
        else if (option == "-p") {
            int cnt = 0;
            for (int j = 1 , id = 0; id < maxPlayers; j = j+2, id++) {
                if (!argv[i+j] || !argv[i+j+1]) {
                    cerr << "ERROR: -p requires another argument" << endl;
                    exit(1);
                }
                string n = argv[i+j];
                string k = argv[i+j+1];
                if (k == "H") {
                    Player* ply = new HumanPlayer('h'+n);
                    plyList[id] = ply;
                }
                else if (k == "S") {
                    Player* ply = new SmartPlayer('s'+n);
                    plyList[id] = ply;
                }
                else if (k == "R") {
                    int RNSeed = atoi(argv[i+j+2]);
                    j++;
                    Player* ply = new RandomPlayer('r'+n, RNSeed);
                    plyList[id] = ply;
                }
                else {
                    cerr << "ERROR: Illegal player kind" << endl;
                    exit(1);
                }
                cnt = j;
            }
            i = i + cnt + 2;
            pOn = 1;
        }
    }
    
    //Generate Default Deck if not created
    if (dOn == 0) {
        newDeck->generate();    
    }
    
    // Creating default players if -p option not specified
    if (pOn == 0) {
        for (int i = 0; i < maxPlayers; i++) {
            string names[4] = {"sAlice", "sBob", "sCarole", "sTed"};
            Player* ply = new SmartPlayer(names[i]);
            plyList[i] = ply;
        }
    }
    
    newDeck->setRandomSeed(seed);
    newDeck->shuffle();
    
    // Deal Cards       
    int FirstPlayer;
    for (int i = 51, j = 0; i >= 0; i--, j++) {
        (*plyList[j % maxPlayers]).addCard(newDeck->at(i));
        if (*(newDeck->at(i)) == Card::TwoOfClubs) {
            FirstPlayer = j % maxPlayers;
        }
    }
    cout << endl;

    
    //PLAY GAME************************************************
    int score[4] = {0};
    
    int hand_cnt = 1;
    int whoExceed = 0;
    while(1) {
        cout << "\nAt the beginning of hand " << hand_cnt << ", here is the deck:" << endl;
        newDeck->print();
    
        cout << "\nHere are the hands for each player at the start of hand number " << hand_cnt << endl;
        
        for (int i = 0; i < maxPlayers; i++) {
            cout << endl << plyList[i]->getName() << " has these cards:" << endl;
            plyList[i]->print();
        }
    
        cout << endl << endl;
    
        for (int round = 0; round < 13; round++) {
            cout << "Now starting round " << round+1 << " of hand " << hand_cnt << endl;
        
            Trick* trick = new Trick;
            Card::Suit leadSuit;
            Card::Rank trumpRank;
            for (int i = FirstPlayer; i < FirstPlayer + maxPlayers; i++) {
                int pos = i % maxPlayers;
                if (i == FirstPlayer) {
                    Card* leadCard = plyList[pos]->lead();
                    leadSuit = leadCard->getSuit();
                    trumpRank = leadCard->getRank();
                    trick->readCard(leadCard, pos);
                    plyList[pos]->removeCard(leadCard);
                    if (round == 0) {
                        cout << "  " << plyList[pos]->getName() << " has " << *leadCard << " and leads with it" << endl;
                    } else {
                        cout << "  " << plyList[pos]->getName() << " led " << *leadCard << endl;
                    }
                } else {
                    
                    if (plyList[pos]->existSuit(leadSuit)) {
                        Card* followCard = plyList[pos]->followSuit(leadSuit, trumpRank);
                        if (trumpRank < followCard->getRank()) {
                            trumpRank = followCard->getRank();
                        }
                        trick->readCard(followCard, pos);
                        plyList[pos]->removeCard(followCard);
                        cout << "  " << plyList[pos]->getName() << " followed suit with " << *followCard << endl;
                    } else {
                        Card* throwCard = plyList[pos]->throwOff();
                        trick->readCard(throwCard, pos);
                        plyList[pos]->removeCard(throwCard);
                        cout << "  " << plyList[pos]->getName() << " threw off " << *throwCard << endl;
                    }
                }
            }
            trick->calculate();
            score[trick->getLoser()] += trick->getPoints();
            FirstPlayer = trick->getLoser();
            cout << "  " << plyList[FirstPlayer]->getName() << " won the trick and added the following cards:" << endl;
            trick->print();
            delete trick;
        }
        
        cout << "At the end of hand " << hand_cnt << ", the score is:" << endl;
        for (int i = 0; i < maxPlayers; i++) {
            cout << "    " << plyList[i]->getName() << "  " << score[i] << endl;
        }
        cout << endl;

        newDeck->clean();
        
        //Check if the game is done or not
        int canBreak = 0;
        int highScore = 0;
        for (int i = 0; i < maxPlayers; i++) {
            if (score[i] >= maxScore && score[i] > highScore) {
                canBreak = 1;
                highScore = score[i];
                whoExceed = i;
            }
        }
        if (canBreak) {
            break;
        }
        
        //If the game is not terminated, then regenerate the deck and deal the cards to players
        newDeck->generate();
        newDeck->shuffle();
        
        for (int i = 51, j = (hand_cnt % maxPlayers); i >= 0; i--, j++) {
            (*plyList[j % maxPlayers]).addCard(newDeck->at(i));
            if (*(newDeck->at(i)) == Card::TwoOfClubs) {
            FirstPlayer = j % maxPlayers;
            }
        }
        hand_cnt++;
    }
    
    int winner = 0;
    int lowest = score[0];
    for(int i = 1; i < maxPlayers; i++) {
        if (score[i] < lowest) {
            lowest = score[i];
            winner = i;
        }
    }
    
    cout << "The game is over." << endl;
    cout << plyList[whoExceed]->getName() << " has exceeded " << maxScore << " points." << endl;
    cout << "The winner is " << plyList[winner]->getName() << endl;
    
    for (int i = 0; i < maxPlayers; i++) {
        delete plyList[i];
    }
    
    delete newDeck;
    exit(1);
    
}











