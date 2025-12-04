//
// Created by Nikita Bekeruk on 05/11/2025.
//

#include <map>
#include<string>
#include "Animal.h"
#include "Reservation.h"
#include "Kennel.h"
#include "Animals/AnimalFilter.h"
#include "Files/AnimalsFH.h"
#include "Files/KennelsFH.h"
#include "Files/ReservationsFH.h"
#include "Animals/Dog.h"
#include "Animals/Cat.h"
#include "Animals/Rodent.h"
#include "Logic/Booking.h"
#include "Logic/DatePeriod.h"

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
    AnimalsFH animalsFH;
    map<int, Animal*> animalsMap;
    ReservationsFH reservationsFH;
    KennelsFH kennelsFH;
    Booking booking;

public:
    PetHotel();
    ~PetHotel();

    string GetName() const;
    void SetName(const string&);
    string GetAddress() const;
    void SetAddress(const string&);
    vector<Animal*> GetAnimals() const;
    void SetAnimals(vector<Animal*>);
    void AddAnimal(Animal* animal);
    Animal* AddAnimal(const string& type, const string& name, const string& birthDate, const string& breed, int weight);
    Animal* AddAnimal(const string& type, const string& name, const string& birthDate, const string& breed, const string& rodentType);
    vector<Kennel*> GetKennels() const;
    void SetKennels(vector<Kennel*>);
    void AddKennel(Kennel* kennel);
    void RemoveKennel(Kennel* kennel);
    vector<Reservation*> GetReservations() const;
    void SetReservations(vector<Reservation*>);
    void AddReservation(Reservation*);
    Reservation* AddReservation(const string& startDate, const string& endDate, bool putTogether, Animal* animal);
    void AddBooking(Animal* animal, int kennelID, DatePeriod datePeriod, bool fullBooking = false);
    Animal* FindAnimal(int id);
    Kennel* FindKennel(int id);
    vector<BookingData> AutoChooseKennels(Animal* animal, bool putTogether, DatePeriod datePeriod);
    void DisplayKennels();
    void DisplayKennels(vector<Kennel*> sliced_kennels);
    void DisplayReservations();
    void DisplayAnimals();
    void DisplayAnimals(vector<Animal*> sliced_animals);
};

#endif //PETHOTEL_H
