//
// Created by Nikita Bekeruk on 05/11/2025.
//

#include<string>
#include "Animal.h"
#include "Reservation.h"
#include "Kennel.h"
using namespace std;

#ifndef PETHOTEL_H
#define PETHOTEL_H

class PetHotel {
private:
    string name;
    string address;
    vector<Animal*> animals;
    vector<Kennel*> kennels;
    vector<Reservation*> reservations;

public:
    string GetName() const;
    void SetName(const string&);
    string GetAddress() const;
    void SetAddress(const string&);
    vector<Animal*> GetAnimals() const;
    void SetAnimals(vector<Animal*>);
    void AddAnimal(Animal* animal);
    vector<Kennel*> GetKennels() const;
    void SetKennels(vector<Kennel*>);
    vector<Reservation*> GetReservations() const;
    void SetReservations(vector<Reservation*>);
    void AddReservation(Reservation*);

    Kennel* ChooseKennel(int);
    Kennel* ChooseKennel(const string &size, const string &type, bool putTogether);
    void ListKannels();
    void ListReservations();
    void ListAnimals();
};

#endif //PETHOTEL_H
