#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
 
using namespace std;

class Character {
    private:
    
    //member decleration
    string name;
    double healthPoints;
    double strength;
    double defense;
    double speed;
    double criticalHit;
    
    double computeCriticalHit();
    
    public:
    
    //constructors
    Character();
    Character(string n, double hp, double str, double def, double spd);
    
    //member function prototypes
    void defend(double);
    void heroAttack(Character &h, Character &m);
    void monsterAttack(Character &h, Character &m);
    double getHP() const;
    double getSpeed() const;
    double getStrength() const;
    double getDefense() const;
    double getCriticalHit() const;
    string getName() const;
    void getStats(Character, Character) const;
    void getInfo(Character, Character) const;
    void displayHpDef(Character, Character) const;
    void potion(int);
};

#endif