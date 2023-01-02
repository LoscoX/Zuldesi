#include "Powerup.hpp"
#include <cstring>
#include <list>
#include <iostream>
#include <iterator>

using namespace std;

Powerup::Powerup(){}

Powerup::Powerup(string name, string description, int qnt, int price, int difficulty){
    this->name = name;
    this->description = description;
    this->qnt = qnt;
    this->price = price;
    this->difficulty = difficulty;
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