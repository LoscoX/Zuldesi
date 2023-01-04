#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;

class Powerup{
public:
	string name;//powerup identifier
	string description; //Description
	int qnt; //Quantity of powerup
	int price; //price
	int difficulty;//measures how much the difficulty should increase when bought
	Powerup();
	Powerup(string name, string description, int qnt, int price, int difficulty);
	string getName();
	string getDescription();
	int getQnt();
	int getPrice();
	int getDifficulty();
	void setQnt(int qnt);
};
