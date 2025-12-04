//
// Created by Nikita Bekeruk on 24/11/2025.
//

#include "Cat.h"
#include "../IDManager.h"
#include <iostream>

using namespace std;

Cat::Cat(const string &name, const string &birthDate, const string &breed, int weight):
    Animal(name, birthDate, breed), weight(weight)
{
    this->ID = IDManager::NewID("Cat");
}

Cat::Cat(int ID, const string &name, const string &birthDate, const string &breed,  int weight):
    Animal(name, birthDate, breed), weight(weight)
{
    this->ID = ID;
}

Cat::~Cat(){}

int Cat::GetWeight() const {
    return this->weight;
}

void Cat::SetWeight(int weight) {
    this->weight = weight;
}

void Cat::MakeSound(){
    cout << "Cat say meuw meuw!" << endl;
}

string Cat::GetType(){
    return "Cat";
}

int Cat::GetSpace() const {
    return WeightToSpace(weight);
}

