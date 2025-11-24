//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Reservation.h"
#include<string>

using namespace std;

Reservation::Reservation(int ID, const string &startDate, const string &endDate, const vector<Animal*> &animals, bool putTogether):
    ID(ID), startDate(startDate),endDate(endDate), animals(animals), putTogether(putTogether) {}

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

/*
bool Reservation::IsDurationValid() const {
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
*/