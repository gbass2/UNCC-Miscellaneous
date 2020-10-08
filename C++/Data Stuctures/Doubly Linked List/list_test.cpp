// Test for templated linked list impementation
#include <iostream>
#include "list.h"
#include "list.cpp"
using namespace std;

int main() {
	List<string> planets;
	planets.push_back("Mercury");
	planets.push_back("Venus");
	planets.push_back("Earth");
	planets.push_back("Mars");

	for (auto p = planets.begin(); !p.equals(planets.end());  p.next())
		cout << p.get() << " ";
	cout << endl;

	// Test erase
	auto p = planets.begin();
	// Erase earth
	p.next(); p.next();
	auto it = planets.erase(p);
	cout << "Next in list: " << it.get() << endl;

	// Test copy constructor - homework
	List<string> planetsCopy(planets);
	// Insert Earth into copy
	p = planetsCopy.begin();
	p.next();
	planetsCopy.insert(p, "Earth");
	
	// Print copied list - Should print: Mercury Earth Venus Mars
	for (auto p = planetsCopy.begin(); !p.equals(planetsCopy.end());  p.next())
		cout << p.get() << " ";
	cout << endl;

	// Print original list - Should print: Mercury Venus Mars
	for (auto p = planets.begin(); !p.equals(planets.end());  p.next())
		cout << p.get() << " ";
	cout << endl;

}
