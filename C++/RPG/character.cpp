#include <iostream>
#include <random>
#include "character.h"

using namespace std;
 
//default and overloaded constructors
Character::Character() : Character{"",0.0,0.0,0.0,0.0} {
}

Character::Character(string n, double hp, double str, double def, double spd) : name{n}, healthPoints{hp}, strength{str}, defense{def}, speed{spd} {
}

//calculates the damage being delt
void Character::defend(double s) {
    
    //computes a random number between 1 and 10, inclusive. If the value is > 7, then a critical hit will be displayed
    computeCriticalHit();
    
    //damage = strength + critical hit value
    double damage = s + criticalHit;
    
    //lowering the defender's defense
    if (defense > 0.0) {
        defense -= damage;
        //if the damage > defense the defense will be removed and the remaining damage will lower the HP
        if (defense < 0.0) {
            if (defense > healthPoints)
                healthPoints = 0.0;
            else {
                healthPoints += defense;
                defense = 0.0;
             }
        }
    }
    
    else {
    //if there is no defense then health will be lowered
    if (damage > healthPoints)
        healthPoints = 0.0;
    else 
        healthPoints -= damage;
    }
}

//the attack logic for hero
void Character::heroAttack(Character &h, Character &m) {
    m.defend(h.getStrength());
    if (m.getHP() != 0.0)     
        h.defend(m.getStrength());
}

//the attack logic for monster
void Character::monsterAttack(Character &h, Character &m) {
        h.defend(m.getStrength());
        if(h.getHP() != 0.0)
            m.defend(h.getStrength());
}

//passes in a value and creates a health potion
void Character::potion(int potionVal) {
    healthPoints += potionVal;
}

//returns the character's values
string Character::getName() const {
    return name;
}

double Character::getHP() const {
    return healthPoints;
}

double Character::getStrength() const {
    return strength;
}

double Character::getSpeed() const {
    return speed;
}

double Character::getDefense() const {
    return defense;
}

double Character::getCriticalHit() const {
    return criticalHit;
}

//displays information about the game
void Character::getInfo(Character h, Character m) const {
    cout << "There once was two brothers named " << h.getName() << " and " << m.getName() << ". " << endl << "Both brothers grew up in royalty. Their parents ruled over Scottsdale. " << endl;
    cout << "One day their father became terribly ill. " << endl << "The time came for " << h.getName() << " to take over the throne. " << endl << m.getName() << ", who was jealous and envy, became over enraged. " << endl;
    cout << "He swore to never let his brother see the light of day again." << endl << endl;
}

//gets the stats of the player and the monster
void Character::getStats(Character h,Character m) const {
    cout << "Your HP: " << h.getHP() << endl;
    cout << "Your Strength: " << h.getStrength() << endl;
    cout << "Your Defense: " << h.getDefense()<< endl;   
    cout << "Your Speed: " << h.getSpeed() << endl;
    cout <<"-------------------" <<endl;
    cout << m.getName() <<"'s Health: " << m.getHP() << endl;
    cout << m.getName() <<"'s Strength: " << m.getStrength() << endl;
    cout << m.getName() << "'s Defense: " << m.getDefense() << endl;
    cout << m.getName() << "'s Speed: " << m.getSpeed() << endl << endl;
}
 
//displays the heath, defense, and whether a critical hit was done after each attack
void Character::displayHpDef(Character h, Character m) const {
    cout << "\n------------" << endl;
    
    //determines if critical hit will be displayed for hero
    if (h.getCriticalHit() > 7.0)
        cout << "Critical Hit! ";
    cout << "Damage delt was " << h.getStrength() + h.getCriticalHit() << endl;
    cout << "Your HP: " << h.getHP() << endl;
    cout << "Your Defense: " << h.getDefense() << endl;
    cout << "------------" << endl;
    
    //determines if critical hit will be displayed for monster
    if (m.getCriticalHit() > 7.0)
        cout << "Critical Hit! ";
    cout << "Damage delt was " <<  m.getStrength() + m.getCriticalHit() << endl;
    cout << m.getName() << "'s HP: " << m.getHP() << endl;
    cout << m.getName() << "'s Defense: " << m.getDefense() << endl << endl;
}

double Character::computeCriticalHit() {
    //creates a random number between 1 and 10, inclusive. if criticalHit > 7, there will be a critical hit
    double min = 1.0;
    double max = 10.0;
    
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(min,max); // guaranteed unbiased
    return criticalHit = uni(rng);
}