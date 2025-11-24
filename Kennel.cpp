//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Kennel.h"

Kennel::Kennel(int ID, const string& size, int capacity, bool isEmpty):
    ID(ID), size(size), capacity(capacity), isEmpty(isEmpty), type("NA"){}

Kennel::Kennel(int ID, const string& size, int capacity, const string& type, bool isEmpty, vector<Animal*> animals):
    ID(ID), size(size), capacity(capacity), type(type), isEmpty(isEmpty), animals(animals){}

Kennel::~Kennel() {}


string Kennel::GetSize() const {
    return this->size;
}

void Kennel::SetSize(const string& size) {
    this->size = size;
}

int Kennel::GetCapacity() const {
    return this->capacity;
}

void Kennel::SetCapacity(int capacity) {
    this->capacity = capacity;
}

string Kennel::GetType() const {
    return this->type;
}

void Kennel::SetType(const string& type) {
    this->type = type;
}

vector<Animal*> Kennel::GetAnimals() const {
    return this->animals;
}

void Kennel::SetAnimals(vector<Animal*> animals) {
    this->animals = animals;
}

bool Kennel::GetIsEmpty() {
    return this->isEmpty;
}

void Kennel::SetIsEmpty(bool isEmpty) {
    this->isEmpty = isEmpty;
}

int Kennel::GetID() const {
    return this->ID;
}

void Kennel::SetID(int ID) {
    this->ID = ID;
}

/*
bool Kennel::CheckAvailability() {
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
*/

void Kennel::AddAnimal(Animal* animal) {
    this->animals.push_back(animal);
    this->isEmpty = false;
    if (this->type == "NA") {
        this->type = animal->GetType();
    }
}