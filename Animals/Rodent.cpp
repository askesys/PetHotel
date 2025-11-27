//
// Created by Nikita Bekeruk on 24/11/2025.
//

#include "Rodent.h"
#include "../IDManager.h"
#include <iostream>

using namespace std;

Rodent::Rodent(const string &name, const string &birthDate, const string &breed, const string &careSchedule, const string &rodentType):
    Animal(name, birthDate, breed, careSchedule), rodentType(rodentType)
{
    IDManager::NewID("Rodent");
}

Rodent::Rodent(int ID, const string &name, const string &birthDate, const string &breed, const string &careSchedule, const string &rodentType):
    Animal(name, birthDate, breed, careSchedule), rodentType(rodentType)
{
    this->ID = ID;
}

Rodent::~Rodent() {}

string Rodent::GetRodentType() const {
    return rodentType;
}

void Rodent::SetRodentType(const string &rodentType) {
    this->rodentType = rodentType;
}

void Rodent::MakeSound(){
    cout << "Rodent makes chew chew!" << endl;
}

string Rodent::GetType(){
    return "Rodent";
}



