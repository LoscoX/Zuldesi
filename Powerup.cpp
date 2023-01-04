#include "Powerup.hpp"

Powerup::Powerup(){}

Powerup::Powerup(string name, string description, int qnt, int price, int difficulty){
    this->name = name;  //name
    this->description = description; //description
    this->qnt = qnt; //quantity
    this->price = price; //price
    this->difficulty = difficulty; //difficulty
}

string Powerup::getName(){
    return name;
}

string Powerup::getDescription(){
    return description;
}

int Powerup::getQnt(){
    return qnt;
}

int Powerup::getPrice(){
    return price;
}

int Powerup::getDifficulty(){
    return difficulty;
} 

void Powerup::setQnt(int qnt){
    this->qnt = qnt;
}
