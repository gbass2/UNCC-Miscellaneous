#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <sstream>

using namespace std;

class GameManager{
    public:
    bool drawTwo = false;
    bool skipTurn = false;
    bool reverse = false;
    bool drawFour = false;
    int numPlayers = 2;
    int playerTurnIndex = 0;

    void setNumPlayers(int);
};

// Creates the colors for the cards
enum ColorType{RED, BLUE, GREEN, YELLOW};

class Card{
    protected:
    // Number
    int number;
    // Color
    ColorType color;

    public:
    // Mutators and Accessors:
    void setColor(ColorType);
    void setNumber(int);
    ColorType getColor() const;
    int getNumber() const;

    // Virtual function for drawing card
    virtual string render(int);
    // Virtual function for playing card
    virtual bool play(Card, GameManager&);

};

class NumberCard : public Card{
    public:
    // Member functions:
    NumberCard(ColorType, int);
    string render(int);
    bool play(Card, GameManager&);
};

class SkipCard : public Card{
    public:
    // Member function:
    SkipCard(ColorType);
    string render(int);
    bool play(Card, GameManager&);
};

class DrawTwoCard : public Card{
    public:
    // Member functions:
    DrawTwoCard(ColorType);
    string render(int);
    bool play(Card, GameManager&);
};

class ReverseCard : public Card{
  public:
   // Member functions:
  ReverseCard(ColorType);
  string render(int);
  bool play(Card, GameManager&);
};

class WildCard : public Card{
    public:
    bool hasColor = false;

    // Member functions:
    string render(int);
    bool play(Card, GameManager&);
};

class DrawFourCard : public Card{
    public:
    bool hasColor = false;

    DrawFourCard();
    string render(int);
    bool play(Card, GameManager&);
};

#endif
