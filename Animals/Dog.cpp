//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Dog.h"

#include <iostream>
#include <ostream>
#include "../IDManager.h"

Dog::Dog(const string &name, const string &birthDate, const string &breed, const string &careSchedule, int weight):
    Animal(name, birthDate, breed, careSchedule), weight(weight)
{
    this->ID = IDManager::NewID("Dog");
}

Dog::Dog(int ID, const string &name, const string &birthDate, const string &breed, const string &careSchedule, int weight):
    Animal(name, birthDate, breed, careSchedule), weight(weight)
{
    this->ID = ID;
}



Dog::~Dog() {}


int Dog::GetWeight() const {
    return this->weight;
}

void Dog::SetWeight(int weight) {
    this->weight = weight;
}

void Dog::MakeSound(){
    cout << "Dog makes *bark *bark!" << endl;
}

string Dog::GetType(){
    return "Dog";
}
