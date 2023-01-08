#include "Powerup.hpp"

Powerup::Powerup(){}

Powerup::Powerup(string name, string description, int qnt, int price, int difficulty){
    this->name = name;  //name
    this->description = description; //description
    this->qnt = qnt; //quantity
    this->price = price; //price
    this->difficulty = difficulty; //difficulty
}

string Powerup::getName(){ //take name
    return name;
}

string Powerup::getDescription(){ //take description
    return description;
}

int Powerup::getQnt(){ //take quantity
    return qnt;
}

int Powerup::getPrice(){ //take price
    return price;
}

int Powerup::getDifficulty(){ //take difficulty
    return difficulty;
} 

void Powerup::setQnt(int qnt){ //set quantity
    this->qnt = qnt;
}

void Powerup::setName(string name){
	this->name = name;
}
