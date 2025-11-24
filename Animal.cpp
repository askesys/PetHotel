//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Animal.h"

#include "PetHotel.h"

Animal::Animal(int ID, const string &name, const string &birthDate, const string &breed, const string &CareSchedule):
    ID(ID), name(name), birthDate(birthDate), breed(breed), CareSchedule(CareSchedule) {}

Animal::~Animal() {}


string Animal::GetName() const {
    return this->name;
}

void Animal::SetName(const string& name) {
    this->name = name;
}

string Animal::GetBirthDate() const {
    return this->birthDate;
}

void Animal::SetBirthDate(const string& date) {
    this->birthDate = date;
}

string Animal::GetBreed() const {
    return this->breed;
}

void Animal::SetBreed(const string& breed) {
    this->breed = breed;
}

int Animal::GetID() const {
    return this->ID;
}

void Animal::SetID(int ID) {
    this->ID = ID;
}

string Animal::GetCareSchedule() const {
    return this->CareSchedule;
}


void Animal::SetCareSchedule(const string& careSchedule) {
    this->CareSchedule = careSchedule;
}

void Animal::MakeSound() {}

string Animal::GetType() {}



string Animal::CarvinoresWeightToSize(int weight) {
    if (weight < 0) {
        invalid_argument("passed weight is negative");
        return "";
    }

    if (weight >= 25) return "Large";
    if (weight >= 10 && weight < 25) return "Medium";
    if (weight < 10) return "Small";

    return "Invalid string";
}



