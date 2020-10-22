#include "card.h"

void GameManager::setNumPlayers(int numPlayers){
    if(numPlayers < 2)
        numPlayers = 2;
    else if(numPlayers > 6)
        numPlayers = 6;

    this->numPlayers = numPlayers;
}

// Mutators and Accessors:
void Card::setColor(ColorType color){
    this->color = color;
}

void Card::setNumber(int number){
    this->number = number;
}

ColorType Card::getColor() const{
    return this->color;
}

int Card::getNumber() const{
    return this->number;
}

bool Card::play(Card discard, GameManager &gameManager){
    return true;
}

string Card::render(int line){
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2: return "|           |";
        case 3: return "|           |";
        case 4: return "|           |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

// Number card's constructor
NumberCard::NumberCard(ColorType color, int number){
    setColor(color);
    setNumber(number);
}

// Renders the number card
string NumberCard::render(int line){
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2:
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
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

// Number card's logic
bool NumberCard::play(Card discard, GameManager &gameManager){
    if(this->getNumber() == discard.getNumber() || this->getColor() == discard.getColor()){
        return true;
    } else {
        return false;
    }
}

// Skip card's overloaded constructor
SkipCard::SkipCard(ColorType color){
    setColor(color);
    setNumber(-1);
}

// Renders the skip card
string SkipCard::render(int line){
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2:
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "| " <<  "   SKIP" << "   |";
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

// Skip card's logic
bool SkipCard::play(Card discard, GameManager &gameManager){
    if(this->getNumber() == discard.getNumber() || this->getColor() == discard.getColor()){
        gameManager.skipTurn = true;
        return true;
    } else {
        return false;
    }
}

// Draw 2 card's overloaded constructer
DrawTwoCard::DrawTwoCard(ColorType color){
    setColor(color);
    setNumber(-2);
}

// Renders the Draw 2 card
string DrawTwoCard::render(int line){
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2:
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|    BLUE   |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "| " <<  "  DRAW 2" << "  |";
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

// Draw 2 card's logic
bool DrawTwoCard::play(Card discard, GameManager &gameManager){
    if(this->getNumber() == discard.getNumber() || this->getColor() == discard.getColor()){
        gameManager.drawTwo = true;
        gameManager.skipTurn = true;
        return true;
    } else {
        return false;
    }
}

// Reverse card's overloaded constructer
ReverseCard::ReverseCard(ColorType color){
    setColor(color);
    setNumber(-3);
}

// Renders the Reverse card
string ReverseCard::render(int line){
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2:
            switch(color){
            case RED:
                return "|    RED    |";
                break;
            case BLUE:
                return "|   BLUE    |";
                break;
            case GREEN:
                return "|   GREEN   |";
                break;
            case YELLOW:
                return "|  YELLOW   |";
                break;
            default:
                return "|           |";
                break;
            break;
            }
        case 3:
            ss << "| " <<  "  <---  " << "  |";
            return ss.str();
            break;
        case 4: return "|   --->    |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

// Reverse card's logic
bool ReverseCard::play(Card discard, GameManager &gameManager){
    if(this->getNumber() == discard.getNumber() || this->getColor() == discard.getColor()){
        if(!gameManager.reverse){
            gameManager.reverse = true;
        } else {
            gameManager.reverse = false;
        }
        return true;
    } else {
        return false;
    }
}

// Renders the wild card
string WildCard::render(int line){
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2:
            // If no color is set, "WILD" will only be displayed
            if(!hasColor)
                return "|           |";
            // "WILD" and color will be displayed
            else{
                switch(color){
                    case RED:
                        return "|    RED    |";
                        break;
                    case BLUE:
                        return "|    BLUE   |";
                        break;
                    case GREEN:
                        return "|   GREEN   |";
                        break;
                    case YELLOW:
                        return "|  YELLOW   |";
                        break;
                    default:
                        return "|           |";
                        break;
                    break;
                }
            }
        case 3:
            ss << "| " <<  "   WILD" << "   |";
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

// Wild card's logic
bool WildCard::play(Card discard, GameManager &gameManager){
    // If a color has not been specified, get userinput and set color to the userinput
    if(!hasColor){
        string userInput;
        cout << "What color would you like it to be?: ";
        cin >> userInput;
        this->hasColor = true;

        // Set color to userInput; Default is  RED
        if(userInput == "red" || userInput ==  "RED")
           setColor(RED);
        else if(userInput == "blue" || userInput ==  "BLUE")
            setColor(BLUE);
        else if(userInput == "green" || userInput ==  "GREEN")
            setColor(GREEN);
        else if(userInput == "yellow" || userInput ==  "YELLOW")
            setColor(YELLOW);
        return true;
    // If color is already set, the card will be checked with the top discard card to see if it can be played
    } else {
        if (this->getColor() == discard.getColor()){
            return true;
        } else {
            return false;
        }
    }
}

// Draw four card's default constructor
DrawFourCard::DrawFourCard(){
    setNumber(-4);
}

// Renders the Draw four card
string DrawFourCard::render(int line){
    stringstream ss;
    switch(line){
        case 0: return ".___________.";
        case 1: return "|           |";
        case 2:
            // If no color is set, "WILD" will only be displayed
            if(!hasColor)
                return "|           |";
            // "WILD" and color will be displayed
            else{
                switch(color){
                    case RED:
                        return "|    RED    |";
                        break;
                    case BLUE:
                        return "|    BLUE   |";
                        break;
                    case GREEN:
                        return "|   GREEN   |";
                        break;
                    case YELLOW:
                        return "|  YELLOW   |";
                        break;
                    default:
                        return "|           |";
                        break;
                    break;
                }
            }
        case 3:
            ss << "| " <<  "   WILD" << "   |";
            return ss.str();
            break;
        case 4: return "|   DRAW 4  |";
        case 5: return "|           |";
        case 6: return "|           |";
        case 7: return "|___________|";
        default:
            return " ";
    }
}

// Draw 4 card's logic
bool DrawFourCard::play(Card discard, GameManager &gameManager){
    // If a color has not been specified, get userinput and set color to the userinput
        if(!hasColor){
            string userInput;
            cout << "What color would you like it to be?: ";
            cin >> userInput;
            this->hasColor = true;

            // Set color to userInput; Default is RED
            if(userInput == "red" || userInput ==  "RED")
               setColor(RED);
            else if(userInput == "blue" || userInput ==  "BLUE")
                setColor(BLUE);
            else if(userInput == "green" || userInput ==  "GREEN")
                setColor(GREEN);
            else if(userInput == "yellow" || userInput ==  "YELLOW")
                setColor(YELLOW);
        }
        gameManager.drawFour = true;
        gameManager.skipTurn = true;
        return true;
}
