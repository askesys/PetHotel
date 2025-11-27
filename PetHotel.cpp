//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include <iostream>
#include "PetHotel.h"

#include <iomanip>
#include<string>

#include "IDManager.h"
#include "Files/AnimalsFH.h"

using namespace std;

PetHotel::PetHotel() {
    SetAnimals(animalsFH.Read());
    SetReservations(reservationsFH.Read(&animalsMap));
    SetKennels(kennelsFH.Read(&animalsMap));
    IDManager::Read();
}

PetHotel::~PetHotel() {
    IDManager::Write();

    for (Kennel* kennel: GetKennels()) {
        delete kennel;
    }

    for (Reservation* reservation: GetReservations()) {
        delete reservation;
    }

    for (Animal* animal: GetAnimals()) {
        delete animal;
    }
}



string PetHotel::GetName() const {
    return this->name;
}

void PetHotel::SetName(const string &name) {
    this->name = name;
}

string PetHotel::GetAddress() const {
    return this->address;
}

void PetHotel::SetAddress(const string &address) {
    this->address = address;
}

vector<Animal*> PetHotel::GetAnimals() const {
    return this->animals;
}

void PetHotel::SetAnimals(vector<Animal*> animals) {
    this->animals = animals;
    for (Animal* animal: animals) {
        animalsMap[animal->GetID()] = animal;
    }
}

void PetHotel::AddAnimal(Animal* animal) {
    this->animals.push_back(animal);
    animalsFH.Write(animal);
    animalsMap[animal->GetID()] = animal;
}

vector<Kennel*> PetHotel::GetKennels() const {
    return this->kennels;
}

void PetHotel::SetKennels(vector<Kennel*> kennels) {
    this->kennels = kennels;
}

vector<Reservation*> PetHotel::GetReservations() const {
    return this->reservations;
}

void PetHotel::SetReservations(vector<Reservation*> reservations) {
    this->reservations = reservations;
}

void PetHotel::AddReservation(Reservation *reservation) {
    this->reservations.push_back(reservation);
    reservationsFH.Write(reservation);
}

Kennel* PetHotel::ChooseKennel(int id) {
    for (int i = 0; i < this->kennels.size(); i++) {
        if (this->kennels[i]->GetID() == id) {
            return this->kennels[i];
        }
    }
    return nullptr;
}

Kennel* PetHotel::ChooseKennel(const string &size, const string &type, bool putTogether) {
    if (putTogether) {
        for (int i = 0; i < this->kennels.size(); i++) {
            if (kennels[i]->GetSize() == size && kennels[i]->GetType() == type &&
                (kennels[i]->GetAnimals().size() + 1) <= kennels[i]->GetCapacity()) {
                return kennels[i];
                }
        }
    }

    for (int i = 0; i < this->kennels.size(); i++) {
        if (kennels[i]->GetSize() == size && kennels[i]->GetIsEmpty() == true) {
            return kennels[i];
        }
    }

    return nullptr;
}

void PetHotel::ListKannels() {
    cout << endl;
    cout << "==================================== Kennels =========================================" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < this->kennels.size(); i++) {
        cout << setw(10) << kennels[i]->GetID() << "|";
        cout << setw(10) << kennels[i]->GetType() << "|";
        cout << setw(10) << kennels[i]->GetCapacity() << "|";
        cout << setw(10) << kennels[i]->GetSize() << "|";
        cout << setw(20);
        vector<Animal*> animals = kennels[i]->GetAnimals();
        cout << "[";
        for (int j = 0; j < animals.size(); j++) {
            cout << animals[j]->GetID() << " ";
        }
        cout << "]";
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}

void PetHotel::ListReservations() {
    cout << endl;
    cout << "================================== Reservations ======================================" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < this->reservations.size(); i++) {
        cout << setw(10) << reservations[i]->GetID() << "|";
        cout << setw(10) << reservations[i]->GetStartDate() << "|";
        cout << setw(10) << reservations[i]->GetEndDate() << "|";
        cout << setw(10) << reservations[i]->GetPutTogether() << "|";
        cout << setw(20);
        vector<Animal*> animals = reservations[i]->GetAnimals();
        cout << "[";
        for (int j = 0; j < animals.size(); j++) {
            cout << animals[j]->GetID() << " ";
        }
        cout << "]";
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}

void PetHotel::ListAnimals() {
    cout << endl;
    cout << "===================================== Animals ========================================" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < this->animals.size(); i++) {
        cout << setw(10) << animals[i]->GetID() << "|";
        cout << setw(10) << animals[i]->GetName() << "|";
        cout << setw(10) << animals[i]->GetBirthDate() << "|";
        cout << setw(10) << animals[i]->GetBreed() << "|";
        cout << setw(10) << animals[i]->GetCareSchedule() << "|";
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}
