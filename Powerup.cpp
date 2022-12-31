#include "Powerup.hpp"
#include <cstring>
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

class Powerup{
    private:
        string name;//powerup identifier
        string description;
        bool owned;//additional lives/shields powerups do not take this value into account (they can be retaken anytime)
        int price;
        int difficulty;//measures how much the difficulty should increase when bought
    public:
        Powerup(string name, string description, bool owned, int price, int difficulty){
            this->name = name;
            this->description = description;
            this->owned = owned;
            this->price = price;
            this->difficulty = difficulty;
        }
        string getName(){
            return name;
        }
        string getDescription(){
            return description;
        }
        bool isOwned(){
            if(this->name == "HP" || this->name == "Shield")
                return false;
            return owned;
        }
        int getPrice(){
            return price;
        }
        int getDifficulty(){
            return difficulty;
        } 
        void setOwned(bool owned){
            this->owned = owned;
        }

};

int main(int argc, char* argv[]){
    //this code initializes the first powerup list, needs to be moved to Game.cpp
    list<Powerup> powerups = list<Powerup>();
    powerups.push_back(*new Powerup("HP", "Get back on your feet one more time", false, 1, 1));         //LIFE
    powerups.push_back(*new Powerup("Shield", "A shield that blocks damage one time", false, 1, 1));    //SHIELD
    powerups.push_back(*new Powerup("tmp", "Extra Life", false, 1, 1));                                 //TBD
    powerups.push_back(*new Powerup("tmp", "Extra Life", false, 1, 1));                                 //TBD
    powerups.push_back(*new Powerup("tmp", "Extra Life", false, 1, 1));                                 //TBD
    
};