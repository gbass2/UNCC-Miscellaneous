#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "card.h"

using namespace std;

void buildDeck(vector<Card*> &deck){
    // Adds number cards 1-9; Two of each color
    for (int i = 0; i < 2; i++){
        for(int j = 1; j < 10; j++){
            for(int c = RED; c <= YELLOW; c++){
                deck.push_back(new NumberCard((ColorType)c, j));
            }
        }
    }
    
    // Adds number card 0; 1 of wach color
    for(int i = 0; i < 1; i++){
            for(int c = RED; c <= YELLOW; c++){
                deck.push_back(new NumberCard((ColorType)c, i));
            }
    }
    
    // Adds skip cards
    for(int i = 0; i < 2; i++){
        for(int c = RED; c <= YELLOW; c++){
            deck.push_back(new SkipCard((ColorType)c));
        }
    }
    
    // Adds Draw 2 cards
    for(int i = 0; i < 2; i++){
        for(int c = RED; c <= YELLOW; c++){
            deck.push_back(new DrawTwoCard((ColorType)c));
        }
    }
    
    // Adds reverse cards
    for(int i = 0; i < 2; i++){
        for(int c = RED; c <= YELLOW; c++){
            deck.push_back(new ReverseCard((ColorType)c));
        }
    }
    
    // Adds wild cards
    for(int i = 0; i < 1; i++){
            for(int c = RED; c <= YELLOW; c++){
                deck.push_back(new WildCard);
            }
    }
    
    // Adds Draw 4 cards
    for(int i = 0; i < 1; i++){
        for(int c = RED; c <= YELLOW; c++){
            deck.push_back(new DrawFourCard);
        }
    }
    
}

void drawCards(vector<Card*> &deck, vector<Card*> &hand, int numCards){
    for(int i = 0; i < numCards; i++){
        Card* temp = deck.at(deck.size() - 1);
        deck.pop_back();
        hand.push_back(temp);
    }
}

// Shuffles the deck
void scramble(vector <Card*> &deck){
    random_device rd;
    shuffle(begin(deck), end(deck), rd);
}

// Reshuffles the deck if all 108 cards have been used
void reshuffle(vector<Card*> &deck, vector<Card*> &discard){
    //if the deck empties, it will be reshuffled;
        if(deck.size() < 1){
            cout << "\nreshuffling..." << endl;
            buildDeck(deck);
            scramble(deck);
        }
    // Removes all but top card in discard
    Card* temp = discard.at(discard.size() - 1);
    for (int i = 0; i < discard.size(); i++){
        discard.pop_back();
    }
    discard.push_back(temp);
}

// Creates hands for n number of players
void createHands(vector<Card*> &deck, vector<vector<Card*>> &hands){
    for(int i = 0; i < hands.size(); i++){
        drawCards(deck, hands.at(i), 7);
    }
}

void renderHand(vector<Card*> hand){
    if(hand.size() > 0){
        for(int i = 0; i <= 7; i++){
           // cout << endl;
            for(int j = 0; j < hand.size(); j++){
                cout << hand.at(j)->render(i) << " ";
            }
            cout << endl;
        }
    } else {
        for(int i = 0; i <= 7; i++)
            cout << endl;
    }
}

void renderDiscard(vector<Card*> discard){
    for(int i = 0; i <= 7; i++){
        cout << discard.at(discard.size() - 1)->render(i) << endl;
    }
}

void takeTurn(vector<Card*> &deck, vector<vector<Card*>> &hands, vector<Card*> &discard, GameManager &gameManager){
    // Print player's turn (GameManger's repsonsiblity)
    cout << "\nPlayer " << gameManager.playerTurnIndex + 1 << "'s turn" << endl;
    int playerChoice;
    
    // Do I need to draw cards? (Draw 2 played last)
    if(gameManager.drawTwo){
        drawCards(deck, hands.at(gameManager.playerTurnIndex), 2);
    }
    
    // Do I need to draw cards? (Draw 4 played last)
    if(gameManager.drawFour){
        drawCards(deck, hands.at(gameManager.playerTurnIndex), 4);
    }
        
    // Do I need to skip this player's turn
    if(!gameManager.skipTurn){
        // if false:
        // Select card in hand to play
        renderDiscard(discard);
        renderHand(hands.at(gameManager.playerTurnIndex));
        cout << "Which card would you like to play? (0 - ";
        cout << hands.at(gameManager.playerTurnIndex).size() - 1 << "): ";
        cin >> playerChoice;
        
        // Check for valid input
        while(playerChoice < 0 || playerChoice > hands.at(gameManager.playerTurnIndex).size() - 1){
            cout << "Invalid card. ";
            cout << "Which card would you like to play? (0 - ";
            cout << hands.at(gameManager.playerTurnIndex).size() - 1 << "): " << endl;
            cin >> playerChoice;
        }
            
        if(hands.at(gameManager.playerTurnIndex).at(playerChoice)->play(*discard.at(discard.size() -1), gameManager)){
            // Is selected card valid?
            // if true:
                // remove card from hand and edit effects to game manager
            Card* temp = hands.at(gameManager.playerTurnIndex).at(playerChoice);
            hands.at(gameManager.playerTurnIndex).erase(hands.at(gameManager.playerTurnIndex).begin() + playerChoice);
            discard.push_back(temp);
        } else {     
            // if false:
                //draw card
            drawCards(deck, hands.at(gameManager.playerTurnIndex), 1);
        } 
    } else {
        // if true:
            // reset game manager (draw2, draw4, and skip = false)
        gameManager.drawTwo = false;
        gameManager.drawFour = false;
        gameManager.skipTurn = false;
    }
    
    // Get next player index (use game manager info to determine)
    if(!gameManager.reverse){     
        gameManager.playerTurnIndex++;
        if(gameManager.playerTurnIndex >= gameManager.numPlayers)
            gameManager.playerTurnIndex = 0;
    } else {
    //reverse card reverses the index
    gameManager.playerTurnIndex--;
    if(gameManager.playerTurnIndex < 0)
        gameManager.playerTurnIndex = gameManager.numPlayers - 1;
    }
    
}

bool hasWon(vector<vector<Card*>> hands, GameManager& gameManager){
    for(int i = 0; i < hands.size(); i++){
        if((hands.at(i)).size() == 0){
            cout << "\nCongratulations! Player " << gameManager.playerTurnIndex + 1 << " has Won!" << endl; 
            return true;
        }
    }
}


int main(){
    // Determining the amount of players
    cout << "How many are playing (max of 6): ";
    int players;
    cin >> players;
    
    //Check to see if the number of players is between 2 and 6 and setting the number to numPlayers
    while(players < 2 || players > 6){
        cout << "Invalid number of players. Please re-enter the numbre of players: ";
        cin >> players;
    }
    
    GameManager gameManager;
    gameManager.setNumPlayers(players);
    
    vector<Card*> deck;
    vector<Card*> discard;
    vector<vector<Card*>> hands(gameManager.numPlayers);
    
    // Builds the deck
    buildDeck(deck);
    
    // Shuffles the deck
    scramble(deck);
    
    // Creates the first discard card
    drawCards(deck, discard, 1);
    
    // Creates hands for n number of players
    createHands(deck, hands);

    // Loops until a player has won
    while(!hasWon(hands, gameManager)){
        // Reshuffles the deck and removes all but the top card in discard;
        reshuffle(deck, discard);

        takeTurn(deck, hands, discard, gameManager);
    }
    
    return 0;
}
