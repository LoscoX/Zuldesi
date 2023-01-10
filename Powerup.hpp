#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;

class Powerup{
public:
    /**
     * Power-up identifier.
     */
	string name;
    /**
     * Description.
     */
	string description;
    /**
     * Quantity of power-up.
     */
	int qnt;
    /**
     * Price.
     */
	int price;
    /**
     * Measures how much the difficulty should increase when bought.
     */
	int difficulty;
	Powerup();
	Powerup(string name, string description, int qnt, int price, int difficulty);
	string getName();
	string getDescription();
	int getQnt();
	int getPrice();
	int getDifficulty();
	void setQnt(int qnt);
	void setName(string name);
};
