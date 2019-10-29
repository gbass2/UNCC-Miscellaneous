#include <iostream>
#include <cctype>
#include "character.h"

using namespace std;

int main () {
    
    //create instances of the player, enemy, and display which displays options
    Character hero("Harry",100,20,50,60);
    Character monster("Peter",100,20,40,70);
    Character display;
    
    char choice;
 
    cout << hero.getName() << " you are battling " << monster.getName() << endl << endl;

    //displays the player and monster's stats until broken
    do {
    
    //displaying the users choice
    cout << "S - Stats" << endl;
    cout << "I - Info" << endl;
    cout << "C - Continue" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;

    choice = tolower(choice);

    switch(choice) {
    //player and monster's stats
    case 's': 
        display.getStats(hero,monster);
        break;
        
    case 'i':
        display.getInfo(hero, monster);
        break;
        
    case'c':
        break;
        
    default: cout << "Unkown input, please re-enter your choice" << endl << endl; 
        break;
        }
    }
 
   while (choice != 'c' && choice != 'C');
    
    //loops until health of both characters is zero  
    do {
        //displays the users choice
        cout << "A - Attack" << endl;
        cout << "P - Health Potion that restores 25 HP" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        choice = tolower(choice);
        
        //gives player the choice to attack or use a potion
        switch (choice) {
            case 'a': {
                if (hero.getSpeed() > monster.getSpeed()) {
                //hero attacks
                hero.heroAttack(hero,monster);
                display.displayHpDef(hero,monster);
                }
                else {
                //monster attacks
                monster.monsterAttack(hero,monster);
                display.displayHpDef(hero,monster);
                }
            }
                break;
                //restores a set number of HP
            case 'p': {
                hero.potion(25.0);
                hero.defend(monster.getStrength()); 
                display.displayHpDef(hero,monster);
            }
                break;
            
            default: cout << "\nUnknown input, please re-enter your choice" << endl << endl;
                break;
        }
    }
        
    while (hero.getHP() != 0.0 && monster.getHP() != 0.0);
        
    //Displays a message of the winner
    if (hero.getHP() != 0.0)
        cout << "Congrats, You have beaten " << monster.getName() << endl;
    else 
        cout << "Better luck next time, you have been defeated by " << monster.getName() << endl; 
    
    return 0;
}