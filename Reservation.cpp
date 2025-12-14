//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Reservation.h"
#include<string>

#include "IDManager.h"
#include "Logic/Booking.h"
#include "Logic/Date.h"

using namespace std;

Reservation::Reservation(int ID, const string &startDate, const string &endDate, const vector<Animal*> &animals, bool putTogether):
    ID(ID), startDate(startDate),endDate(endDate), animals(animals), putTogether(putTogether) {}

Reservation::Reservation(const string &startDate, const string &endDate, bool putTogether, Animal *animal):
startDate(startDate),endDate(endDate), putTogether(putTogether)
{
    SetID(IDManager::NewID("Reservation"));
    AddAnimal(animal);
}


Reservation::~Reservation() {}


string Reservation::GetStartDate() const {
    return this->startDate;
}

void Reservation::SetStartDate(const string &date) {
    this->startDate = date;
}

string Reservation::GetEndDate() const {
    return this->endDate;
}

void Reservation::SetEndDate(const string &date) {
    this->endDate = date;
}

vector<Animal *> Reservation::GetAnimals() const {
    return this->animals;
}

void Reservation::SetAnimals(const vector<Animal*> animals) {
    this->animals = animals;
}

void Reservation::AddAnimal(Animal *animal) {
    this->animals.push_back(animal);
}


bool Reservation::GetPutTogether() const {
    return this->putTogether;
}

void Reservation::SetPutTogether(bool putTogether) {
    this->putTogether = putTogether;
}

int Reservation::GetID() const {
    return this->ID;
}

void Reservation::SetID(int ID) {
    this->ID = ID;
}

bool Reservation::IsDurationValid() const {
    Date sDate(this->startDate), eDate(this->endDate);
    int length = eDate - sDate;
    return length >= 2 && length <= 14; //I validate this when I create reservation. But can be used for debuging later
}
