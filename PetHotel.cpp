//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include <iostream>
#include "PetHotel.h"
#include "Animals/Dog.h"
#include "Animals/Cat.h"
#include "Animals/Rodent.h"
#include <iomanip>
#include<string>
#include<algorithm>
#include "IDManager.h"
#include "Files/AnimalsFH.h"
#include "Logic/Booking.h"
#include "Logic/DatePeriod.h"

using namespace std;

PetHotel::PetHotel() {
    SetAnimals(animalsFH.Read());
    SetReservations(reservationsFH.Read(&animalsMap));
    SetKennels(kennelsFH.Read(&animalsMap));
    IDManager::Read();
    booking = Booking(kennels,reservations);
}

PetHotel::~PetHotel() {
    IDManager::Write();

    kennelsFH.WriteAll(kennels);
    for (Kennel* kennel: GetKennels()) {
        delete kennel;
    }

    reservationsFH.WriteAll(reservations);
    for (Reservation* reservation: GetReservations()) {
        delete reservation;
    }

    animalsFH.WriteAll(animals);
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

Animal *PetHotel::AddAnimal(const string &type, const string &name, const string &birthDate, const string &breed, int weight) {
    switch (type) {
        case "Dog":
            Dog* dog = new Dog(name, birthDate, breed,  weight);
            this->animals.push_back(dog);
            animalsFH.Write(dog);
            animalsMap[dog->GetID()] = dog;
            return dog;
        case "Cat":
            Cat* cat = new Cat(name, birthDate, breed, weight);
            this->animals.push_back(cat);
            animalsFH.Write(cat);
            animalsMap[cat->GetID()] = cat;
            return cat;
        default:
            throw invalid_argument("PetHotel::AddAnimal: Incorrect Animal type.");
    }
}

Animal *PetHotel::AddAnimal(const string &type, const string &name, const string &birthDate, const string &breed, const string &rodentType) {
    switch (type) {
        case "Rodent":
            Rodent* rodent = new Rodent(name, birthDate, breed,  rodentType);
            this->animals.push_back(rodent);
            animalsFH.Write(rodent);
            animalsMap[rodent->GetID()] = rodent;
            return rodent;
        default:
            throw invalid_argument("PetHotel::AddAnimal: Incorrect Animal type.");
    }
}




vector<Kennel*> PetHotel::GetKennels() const {
    return this->kennels;
}

void PetHotel::SetKennels(vector<Kennel*> kennels) {
    this->kennels = kennels;
}

void PetHotel::AddKennel(Kennel *kennel) {
    kennels.push_back(kennel);
    kennelsFH.Write(kennel);
}

void PetHotel::RemoveKennel(Kennel *kennel) {
    kennelsFH.Delete(kennel);
    erase(kennels, kennel);
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

Animal *PetHotel::FindAnimal(int id) {
    for (int i = 0; i < this->animals.size(); i++) {
        if (this->animals[i]->GetID() == id) {
            return this->animals[i];
        }
    }
    return nullptr;
}


Kennel* PetHotel::FindKennel(int id) {
    for (int i = 0; i < this->kennels.size(); i++) {
        if (this->kennels[i]->GetID() == id) {
            return this->kennels[i];
        }
    }
    return nullptr;
}

vector<Kennel *> PetHotel::ChooseKennels(Animal* animal, bool putTogether, DatePeriod datePeriod){
    string type = animal->GetType();
    vector<Kennel*> result;
    bool accepted = true;
    string size, rodentType;

    switch (type) {
        case "Dog":
            size = Animal::CarvinoresWeightToSize(dynamic_cast<Dog*>(animal)->GetWeight());
            for (int i = 0; i < this->kennels.size(); i++) {
                if (kennels[i]->GetSize() != size) accepted = false;
                if (kennels[i]->GetType() != "Dog" && kennels[i]->GetType() != "NULL") accepted = false;
                if (putTogether && kennels[i]->GetFreeSpots() == 0) accepted = false;

                if (accepted) result.push_back(kennels[i]);
            }
            break;
        case "Cat":
            size = Animal::CarvinoresWeightToSize(dynamic_cast<Cat*>(animal)->GetWeight());
            for (int i = 0; i < this->kennels.size(); i++) {
                if ((size != "Medium" && size != "Small") || kennels[i]->GetSize() != size) accepted = false;
                if (kennels[i]->GetType() != "Cat" && kennels[i]->GetType() != "NULL") accepted = false;
                if (putTogether && kennels[i]->CheckAvailability() == false) accepted = false;

                if (accepted) result.push_back(kennels[i]);
            }
            break;
        case "Rodent":
            rodentType = dynamic_cast<Rodent*>(animal)->GetRodentType();
            for (int i = 0; i < this->kennels.size(); i++) {
                if (kennels[i]->GetSize() != "Mini") accepted = false;
                if (kennels[i]->GetType() != rodentType && kennels[i]->GetType() != "NULL") accepted = false;
                if (putTogether && kennels[i]->CheckAvailability() == false) accepted = false;

                if (accepted) result.push_back(kennels[i]);
            }
            break;
        default:
            throw logic_error("Choose kennel: Didn't find a valid Animal type.");
    }

    result = booking.FindAvailableKennels(result, datePeriod);
    if (putTogether) {
        sort(result.begin(), result.end(),[](Kennel* a, Kennel* b) {
            if (a->GetIsEmpty() != b->GetIsEmpty())
                return a->GetIsEmpty() < b->GetIsEmpty();
            return a->GetFreeSpots() < b->GetFreeSpots();
        });
    }else {
        sort(result.begin(), result.end(),[](Kennel* a, Kennel* b) {return a->GetCapacity() < b->GetCapacity();});
    }
    return result;

}


void PetHotel::DisplayKennels() {
    cout << endl;
    cout << "==================================== Kennels =========================================" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < this->kennels.size(); i++) {
        cout << setw(10) << this->kennels[i]->GetID() << "|";
        cout << setw(10) << this->kennels[i]->GetType() << "|";
        cout << setw(10) << this->kennels[i]->GetCapacity() << "|";
        cout << setw(10) << this->kennels[i]->GetSize() << "|";
        cout << setw(20);
        vector<Animal*> animals = this->kennels[i]->GetAnimals();
        cout << "[";
        for (int j = 0; j < animals.size(); j++) {
            cout << animals[j]->GetID() << " ";
        }
        cout << "]";
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}

void PetHotel::DisplayKennels(vector<Kennel*> sliced_kennels) {
    cout << endl;
    cout << "==================================== Kennels =========================================" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < sliced_kennels.size(); i++) {
        cout << setw(10) << sliced_kennels[i]->GetID() << "|";
        cout << setw(10) << sliced_kennels[i]->GetType() << "|";
        cout << setw(10) << sliced_kennels[i]->GetCapacity() << "|";
        cout << setw(10) << sliced_kennels[i]->GetSize() << "|";
        cout << setw(20);
        vector<Animal*> animals = sliced_kennels[i]->GetAnimals();
        cout << "[";
        for (int j = 0; j < animals.size(); j++) {
            cout << animals[j]->GetID() << " ";
        }
        cout << "]";
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}

void PetHotel::DisplayReservations() {
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

void PetHotel::DisplayAnimals() {
    cout << endl;
    cout << "===================================== Animals ========================================" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < animals.size(); i++) {
        cout << setw(10) << animals[i]->GetID() << "|";
        cout << setw(10) << animals[i]->GetName() << "|";
        cout << setw(10) << animals[i]->GetBirthDate() << "|";
        cout << setw(10) << animals[i]->GetBreed() << "|";
        cout << setw(10) << animals[i]->GetCareSchedule() << "|";
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}

void PetHotel::DisplayAnimals(vector<Animal*> sliced_animals) {
    cout << endl;
    cout << "===================================== Animals ========================================" << endl;
    cout << "======================================================================================" << endl;
    for (int i = 0; i < sliced_animals.size(); i++) {
        cout << setw(10) << i << "|";
        cout << setw(10) << sliced_animals[i]->GetID() << "|";
        cout << setw(10) << sliced_animals[i]->GetName() << "|";
        cout << setw(10) << sliced_animals[i]->GetBirthDate() << "|";
        cout << setw(10) << sliced_animals[i]->GetBreed() << "|";
        cout << setw(10) << sliced_animals[i]->GetCareSchedule() << "|";
        cout << endl;
    }
    cout << "======================================================================================" << endl;
}
