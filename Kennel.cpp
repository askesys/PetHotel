//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Kennel.h"

#include "Animals/Dog.h"
#include "Animals/Cat.h"
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



int Kennel::KennelSizeToSpace(const string &size) {
    if (size == "Large" || size == "Mini") {
        return 4;
    }
    else if (size == "Medium") {
        return 2;
    }
    else if (size == "Small") {
        return 1;
    }
    else if (size == "NULL") {
        return 0;
    }
    else {
        throw runtime_error("Kennel::KennelSizeToSpace(): Unknown size");
    }
}


int Kennel::GetFullSpace() const {
    return KennelSizeToSpace(this->size);
}


