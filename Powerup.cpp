#include "Powerup.hpp"
#include <string>

using namespace std;

class Powerup{
    private:
        string name;
        string description;
        bool owned;
        int price;
    public:
        Powerup(string name, string description, bool owned, int price){
            this->name = name;
            this->description = description;
            this->owned = owned;
            this->price = price;
        }
        string getName(){
            return name;
        }
        string getDescription(){
            return description;
        }
        bool isOwned(){
            return owned;
        }
        int getPrice(){
            return price;
        }
};