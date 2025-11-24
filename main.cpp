#include <iostream>
#include "PetHotel.h"
#include "IDManager.h"
#include<random>
#include "Dog.h"

using namespace std;


void MakeReservation(PetHotel& petHotel) {
    /*
    unsigned int count;
    string name, birthDate, breed, careSchedule, size;
    int weight;
    bool putTogether;

    cout << "Enter the number of animals: ";
    cin >> count;
    cin.get();
    cout << "Should be your animals be put with other animals (0/1): " ;
    cin >> putTogether;
    cin.get();


    for (int i = 0; i < count; i++) {
        cout << "Enter the name of animal: " << i+1 << ": ";
        cin >> name;
        cin.get();
        cout << "Enter the birth date: ";
        cin >> birthDate;
        cin.get();
        cout << "Enter the breed: ";
        cin >> breed;
        cin.get();
        cout << "Enter the care schedule: ";
        getline(cin, careSchedule);
        cin.get();
        cout << "Enter the weight: ";
        cin >> weight;
        cin.get();
        cout << endl;

        Animal* animal = new Dog(IDManager::NewID("Animal"), name, birthDate, breed, careSchedule, weight);
        */
        int putTogether = 1;

        Animal* dog1 = new Dog(IDManager::NewID("Animal"), "Mihai", "08/10/2003", "Chihuahua", "everyday", 60);
        Animal* dog2 = new Dog(IDManager::NewID("Animal"), "Nikita", "17/01/2000", "Bullgod", "everyday", 73);
        vector<Animal*> dogs;
        int weights[] = {60, 78};
        dogs.push_back(dog1);
        dogs.push_back(dog2);

        for (int i = 0; i < dogs.size(); i++) {
            string size = Animal::CarvinoresWeightToSize(weights[i]);
            Animal* animal = dogs[i];
            Kennel* suitableKennel = petHotel.ChooseKennel(size, animal->GetType(), putTogether);

            if (suitableKennel == nullptr) {
                cout << "We cannot accommodate this animal";
                delete dogs[i];
            }else {
                cout << animal->GetType() << " " << animal->GetName() << " was succesfully accommodate in kennel N" << suitableKennel->GetID() << endl;
                suitableKennel->AddAnimal(animal);
                petHotel.AddAnimal(animal);
            }
        }

        Reservation* reservation = new Reservation(IDManager::NewID("Reservation"),"06/11/2025", "08/11/2025", dogs, putTogether);
        petHotel.AddReservation(reservation);
    }



vector<Kennel*> InitKennels() {
    default_random_engine engine{static_cast<unsigned int>(time(0))};
    uniform_int_distribution<int> distribution{1,20};

    vector<Kennel*> kennels;
    //large
    for (int i = 0; i < 10; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Large", distribution(engine), true);
        kennels.push_back(kennel);
    }

    //medium
    for (int i = 0; i < 20; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Medium", distribution(engine), true);
        kennels.push_back(kennel);
    }

    //small
    for (int i = 0; i < 50; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Small", distribution(engine), true);
        kennels.push_back(kennel);
    }

    //large
    for (int i = 0; i < 10; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Mini", 4, true);
        kennels.push_back(kennel);
    }

    return kennels;
}

int main() {
    PetHotel petHotel;

    petHotel.SetKennels(InitKennels());

    MakeReservation(petHotel);

    petHotel.ListKannels();
    petHotel.ListReservations();
    petHotel.ListAnimals();

    vector<Kennel*> phKens = petHotel.GetKennels();
    for (int i = 0; i < phKens.size(); i++) {
        delete phKens[i];
    }

    vector<Animal*> animals = petHotel.GetAnimals();
    for (int i = 0; i < animals.size(); i++) {
        delete animals[i];
    }

    vector<Reservation*> reservations = petHotel.GetReservations();
    for (int i = 0; i < reservations.size(); i++) {
        delete reservations[i];
    }


    return 0;
}