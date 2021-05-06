#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "game_state.h"
#include "card.h"

using namespace std;
using Deck = vector<Card*>;

/**
 * Function to clear the terminal by inserting many new line characters.
 */
void clearTerminal();

/**
 * Function to populate the deck with cards.
 * 
 * @param deck A vector reference of Card pointers representing the deck
 */
void buildDeck(Deck& deck);

/**
 * Function to shuffle the deck.
 * 
 * @param deck A vector reference of Card pointers representing the deck
 */
 void shuffleDeck(Deck&);

/**
 * Function to draw a card from the deck to either the hand or discard pile.
 * 
 * @param deck A vector reference of Card pointers representing the deck
 * @param target A vector representing the structure that the card being drawn 
 * from the deck is being drawn to. This can be either a hand or the discard
 * pile
 */
void drawCards(Deck& deck, Deck& target, Deck& discard, int);

/**
 * Function to draw 7 cards to each player's hand at the beginning of the game.
 * 
 * @param deck A vector reference of Card pointers representing the deck.
 * @param hands A vector of vector of Card pointers representing each player 
 * and their hands. The indicies of the first vector represents a player, and 
 * the indicies of the vector at that index is each individual card within the
 * player's hand.
 */
void populateHands(Deck& deck, vector<Deck>& hands, Deck& discard);

/** 
 * Renders the cards in he hand vector passed.
 * 
 * @param hand A vector containing Card pointers
 */
void renderHand(Deck hand);

/**
 * Renders the top card of the passed discard vector.
 * 
 * @param hand A vector containing Card pointers
 */
void renderDiscard(Deck);

/**
 * Passed references to the deck, hand, and discard vectors and a reference to 
 * the game state. This function will resolve the turn for the current player
 * (whose index is stored in the game state). TakeTurn will query the user for
 * input, draw cards if the previous card was a draw 2 card, or skip the current
 * players turn (see numCardsToPlay in GameState).
 * 
 * @param deck A vector reference of Card pointers representing the deck
 * @param hand A vector reference of Card pointers representing a single player's hand
 * @param discard A vector reference of Card pointers representing the discard pile
 * @param gameState A reference of the game state object
 * @return The index of the player who has won (negative value if no one has won)
 */
int takeTurn(Deck& deck, Deck& hand, Deck& discard, GameState& gameState);

int main(){
    srand(time(0));
    int num_players = 0;
    int winner = -1;

    do {
        cout << "Enter the number of players (2-16): ";
        cin >> num_players;
    } while(num_players < 2 || num_players > 16);

    GameState gameState(num_players);
    
    Deck deck;
    Deck discard;
    
    vector<Deck> hands(num_players);

    buildDeck(deck);
    shuffleDeck(deck);
    populateHands(deck, hands, discard);
    drawCards(deck, discard, discard, 1);
    
    while(winner == -1){
        winner = takeTurn(deck, hands.at(gameState.currentPlayerIndex), discard, gameState);
    }

    cout << "Player " << winner << " wins!" << endl;
    
    return 0;
}

void clearTerminal(){
    for(int i = 0; i < 100; i++){
        cout << endl;
    }
}

void buildDeck(Deck &deck){
    // Create Number Cards
    for(int c = RED; c < NUM_COLORS; c++){
        for(int n = 0; n < 10; n++){
            Card* temp = new NumberCard((Color)c, n);
            deck.push_back(temp);
            deck.push_back(temp);
        }
        deck.push_back(new ReverseCard((Color)c));
        deck.push_back(new ReverseCard((Color)c));
        deck.push_back(new SkipCard((Color)c));
        deck.push_back(new Draw2Card((Color)c));
        deck.push_back(new Draw2Card((Color)c));
        
    }
    for(int i = 0; i < 18; ++i) {
        deck.push_back(new WildCard());
        deck.push_back(new Draw4Card());
    }
}

void shuffleDeck(Deck &deck){
    for(int i = 0; i < 1000; i++){
        int idx1 = rand() % deck.size();
        int idx2 = rand() % deck.size();
        Card* temp = deck.at(idx1);
        deck.at(idx1) = deck.at(idx2);
        deck.at(idx2) = temp;
    }
}

void drawCards(Deck &deck, Deck &target, Deck &discard, int numToDraw){
    for(int i = 0; i < numToDraw; i++){
        if(deck.size() == 0 && discard.size() > 1){
            Card* top = discard.back();
            discard.pop_back();
            shuffleDeck(discard);
            deck = discard;
            discard.clear();
            discard.push_back(top);
        }
        if(deck.size() > 0) {
            target.push_back(deck.at(deck.size() - 1));
            deck.pop_back();
        }
    }
}

void populateHands(Deck &deck, vector<Deck> &hands, Deck &discard){
    for(int i = 0; i < hands.size(); i++){
        drawCards(deck, hands.at(i), discard, 7);
    }
}

void renderHand(Deck hand){
    if(hand.size() > 0){
        for(int i = 0; i <= 7; i++){
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

void renderDiscard(Deck discard){
    for(int i = 0; i <= 7; i++){
        cout << discard.at(discard.size() - 1)->render(i) << endl;
    }
}

int takeTurn(Deck &deck, Deck &hand, Deck &discard, GameState &gameState){
    clearTerminal();
    renderDiscard(discard);
    cout << "Player " << gameState.currentPlayerIndex + 1 << "'s turn." << endl;
    
    drawCards(deck, hand, discard, gameState.numCardsToDraw);
    gameState.numCardsToDraw = 0; // reset cards to draw back to 0
    
    renderHand(hand);
    
    // loop for number of cards to play (0 if previously played card was a "skip" or "draw 2")
    //for(int j = 0; j < gameState.numCardsToPlay; j++){
    if(!gameState.skipTurn){
        // Collect user input
        cout << discard.size() << ' ' << deck.size() << ' ' << endl;
        cout << "What would you like to do?" << endl;
        int i;
        for(i = 0; i < hand.size(); i++){
            cout << i << ": Play Card" << endl;
        }
        cout << i << ": Draw a Card" << endl;
        int input;
        cin >> input;
        
        do {
            if (input > i)
            {
                cout << "This is an invalid input, please enter a valid input." << endl;
                cin >> input;
            }
            else 
                break;
            
        }while (input > i);
        
        // Evaluate user input
    if(hand.at(input)->play(discard.at(discard.size()-1), gameState)){
        Card* temp;
        temp = hand.at(input);
        discard.push_back(temp);
        hand.erase(hand.begin() + input); // Remove card in hand at position "input"
    } 
    
    if(input == i){
    drawCards(deck, hand, discard, 1);
    }
        
    } 
    else{
        gameState.skipTurn = false;
    }

    if(hand.size() == 0){
        return gameState.currentPlayerIndex;
    } else{
        // update variables for next turn
        gameState.nextTurn();
        return -1;
    }
}