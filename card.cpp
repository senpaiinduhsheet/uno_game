#include <iostream>
#include "card.h"

Color Card::getColor() const{
    return color;
}
    
int Card::getNumber() const{
    return number;
}

void Card::setColor(Color c){
    color = c;
}

void Card::setNumber(int n){
    number = n;
}

NumberCard::NumberCard(Color c, int n) {
    setColor(c);
    setNumber(n);
}

string NumberCard::render(int line) const{
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    \e[0;31mRED\e[0;37m    |";
                break;
            case BLUE:
                return "|    \e[0;34mBLUE\e[0;37m   |";
                break;
            case GREEN:
                return "|   \e[0;32mGREEN\e[0;37m   |";
                break;
            case YELLOW:
                return "|  \e[0;33mYELLOW\e[0;37m   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|     " <<  number << "     |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool NumberCard::play(Card* discard, GameState &gameState) {
    if(color == discard->getColor() || BLACK == discard->getColor() || number == discard->getNumber()){
        return true;
    } else {
        return false;
    }
}

ReverseCard::ReverseCard(Color c) {
    setColor(c);
    setNumber(11);
}

string ReverseCard::render(int line) const{
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    \e[0;31mRED\e[0;37m    |";
                break;
            case BLUE:
                return "|    \e[0;34mBLUE\e[0;37m   |";
                break;
            case GREEN:
                return "|   \e[0;32mGREEN\e[0;37m   |";
                break;
            case YELLOW:
                return "|  \e[0;33mYELLOW\e[0;37m   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|  REVERSE  |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool ReverseCard::play(Card* discard, GameState &gameState) {
    if(color == discard->getColor() || BLACK == discard->getColor() || discard->getNumber() == REVERSE_CARD) {
        if(gameState.numPlayers == 2) {
            gameState.skipTurn = true;
            gameState.numCardsToPlay = 0;
        } else {
            gameState.turnDirection = gameState.turnDirection == LEFT ? RIGHT : LEFT;
        }
        return true;
    } else {
        return false;
    }
}

SkipCard::SkipCard(Color c) {
    setColor(c);
    setNumber(12);
}

string SkipCard::render(int line) const{
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    \e[0;31mRED\e[0;37m    |";
                break;
            case BLUE:
                return "|    \e[0;34mBLUE\e[0;37m   |";
                break;
            case GREEN:
                return "|   \e[0;32mGREEN\e[0;37m   |";
                break;
            case YELLOW:
                return "|  \e[0;33mYELLOW\e[0;37m   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|    SKIP   |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool SkipCard::play(Card* discard, GameState &gameState) {
    if(color == discard->getColor() || BLACK == discard->getColor() || discard->getNumber() == SKIP_CARD) {
        gameState.skipTurn = true;
        gameState.numCardsToPlay = 0;
        return true;
    } else {
        return false;
    }
}

Draw2Card::Draw2Card(Color c) {
    setColor(c);
    setNumber(DRAW2_CARD);
}

string Draw2Card::render(int line) const{
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    \e[0;31mRED\e[0;37m    |";
                break;
            case BLUE:
                return "|    \e[0;34mBLUE\e[0;37m   |";
                break;
            case GREEN:
                return "|   \e[0;32mGREEN\e[0;37m   |";
                break;
            case YELLOW:
                return "|  \e[0;33mYELLOW\e[0;37m   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|   DRAW 2  |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool Draw2Card::play(Card* discard, GameState &gameState) {
    if(color == discard->getColor() || BLACK == discard->getColor() || discard->getNumber() == DRAW2_CARD) {
        gameState.numCardsToDraw = 2;
        gameState.skipTurn = true;
        gameState.numCardsToPlay = 0;
        return true;
    } else {
        return false;
    }
}

WildCard::WildCard() {
    setColor(BLACK);
    setNumber(WILD_CARD);
}

string WildCard::render(int line) const{
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    \e[0;31mRED\e[0;37m    |";
                break;
            case BLUE:
                return "|    \e[0;34mBLUE\e[0;37m   |";
                break;
            case GREEN:
                return "|   \e[0;32mGREEN\e[0;37m   |";
                break;
            case YELLOW:
                return "|  \e[0;33mYELLOW\e[0;37m   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|   WILD    |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

bool WildCard::play(Card* discard, GameState &gameState) {
    int choice;
    cout << "Choose the color" << endl;
    cout << "0: Red" << endl;
    cout << "1: Blue" << endl;
    cout << "2: Green" << endl;
    cout << "3: Yellow" << endl;
    cin >> choice;

    if(choice >= 0 && choice < 4) {
        setColor((Color)choice);
        return true;
    } else {
        return false;
    }
}

Draw4Card::Draw4Card() {
    setColor(BLACK);
    setNumber(DRAW4_CARD);
}

string Draw4Card::render(int line) const{
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: 
            switch(color){
            case RED:
                return "|    \e[0;31mRED\e[0;37m    |";
                break;
            case BLUE:
                return "|    \e[0;34mBLUE\e[0;37m   |";
                break;
            case GREEN:
                return "|   \e[0;32mGREEN\e[0;37m   |";
                break;
            case YELLOW:
                return "|  \e[0;33mYELLOW\e[0;37m   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "|  WILD+4   |";
            return ss.str();
            break;
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}


bool Draw4Card::play(Card* discard, GameState &gameState) {
    int choice;
    cout << "Choose the color" << endl;
    cout << "0: Red" << endl;
    cout << "1: Blue" << endl;
    cout << "2: Green" << endl;
    cout << "3: Yellow" << endl;
    cin >> choice;
    
    gameState.numCardsToDraw = 4;
    gameState.skipTurn = true;
    gameState.numCardsToPlay = 0;

    if(choice >= 0 && choice < 4) {
        setColor((Color)choice);
        return true;
    } else {
        return false;
    }
}
