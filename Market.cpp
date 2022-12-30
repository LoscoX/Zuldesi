#include "Market.hpp"
#include "Powerup.cpp"
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

class Market{
    private:
        list<Powerup> powerups;

    public:
        Market(){
            cout<<"constr\n";
        }

        void addPowerup(Powerup p){
            powerups.push_back(p);
        }

        list<Powerup> getNPowerups(int n){
            list<Powerup> notOwned;

            list<Powerup>::iterator it;
            for(it = powerups.begin(); it != powerups.end(); it++)
                if(!it->isOwned())
                    notOwned.push_back(*it);
            
            for(int i = 0; i<n && i<notOwned.size(); i++){
                
            }
        }

};

int main(){
    Market m;
    return 0;
}