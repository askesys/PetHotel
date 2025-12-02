//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Kennel.h"
#include "Animals/Rodent.h"

Kennel::Kennel(int ID, const string& size, int capacity, bool isEmpty):
    ID(ID), size(size), capacity(capacity), isEmpty(isEmpty), type("NULL"){}

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


bool Kennel::CheckAvailability() {
    if (this->animals.size() < this->GetCapacity()) {
        return true;
    }

    return false;
}

void Kennel::AddAnimal(Animal* animal) {
    this->animals.push_back(animal);
    this->isEmpty = false;
    if (this->type == "NULL") {
        if (typeid(*animal) == typeid(Rodent)) {
            this->type = dynamic_cast<Rodent*>(animal)->GetRodentType();
        }
        else {
            this->type = animal->GetType();
        }
    }
}

int Kennel::GetTakenSpots() const {
    return GetAnimals().size();
}


int Kennel::GetFreeSpots() const{
    return GetCapacity()-GetAnimals().size();
}
