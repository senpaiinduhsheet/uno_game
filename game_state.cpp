#include "game_state.h"

GameState::GameState(int n){
    numPlayers = n;
    currentPlayerIndex = 0;
    numCardsToPlay = 1;
    numCardsToDraw = 0;
    turnDirection = LEFT;
}

TurnDirection GameState::getDirection() {
    return turnDirection;
}

void GameState::nextTurn(){
    if(turnDirection == LEFT){
        currentPlayerIndex++;
        if(currentPlayerIndex >= numPlayers){
            currentPlayerIndex = 0;
        }
    } 
    else {
        currentPlayerIndex--;
        if(currentPlayerIndex < 0) {
            currentPlayerIndex = numPlayers - 1;
        }
    }

}