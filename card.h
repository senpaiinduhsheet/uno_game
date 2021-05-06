#ifndef CARD_H
#define CARD_H

#include <sstream>
#include "game_state.h"

using namespace std;


enum Color{RED, BLUE, GREEN, YELLOW, NUM_COLORS, BLACK};


class Card{
    protected:
    Color color;
    int number;
    enum { 
        REVERSE_CARD = 11, SKIP_CARD = 12, DRAW2_CARD = 13, WILD_CARD = 14, DRAW4_CARD = 15
    };
    
    public:
   
    Color getColor() const;
    

    int getNumber() const;
  
    void setColor(Color c);

    void setNumber(int n);
    
    
    virtual string render(int line) const = 0;
    virtual bool play(Card* discard, GameState& gameState) = 0;
};


class NumberCard : public Card{
    public:
    NumberCard(Color c, int n);
    string render(int) const;
    bool play(Card*, GameState&);
};

class ReverseCard : public Card{
    public:
    ReverseCard(Color c);
    string render(int) const;
    bool play(Card*, GameState&);
};


class SkipCard : public Card{
    public:
    SkipCard(Color c);
    string render(int) const;
    bool play(Card*, GameState&);
};


class Draw2Card : public Card{
    public:
    Draw2Card(Color c);
    string render(int) const;
    bool play(Card*, GameState&);
};

class Draw4Card : public Card{
    public:
    Draw4Card();
    string render(int) const;
    bool play(Card*, GameState&);
};

class WildCard : public Card{
    public:
    WildCard();
    string render(int) const;
    bool play(Card*, GameState&);
};


#endif