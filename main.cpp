#include <iostream>
#include "PetHotel.h"
#include "IDManager.h"
#include<random>

#include "Animals/Cat.h"
#include "Animals/Dog.h"
#include "Animals/Rodent.h"

#include "Files/AnimalsFH.h"

using namespace std;


void RegisterAnimal(PetHotel& petHotel) {
    string animalType, name, birthDate, bread, careSchedule, rodentType;
    int weight;

    while (animalType != "1" && animalType != "2" && animalType != "3") {
        cout << "Choose a type of your animal" << endl;
        cout << "\t" << "1. Dog" << endl;
        cout << "\t" << "2. Cat" << endl;
        cout << "\t" << "3. Rodent" << endl;
        cout << "\t" << "Write \"exit\" to abort this procedure" << endl;
        cout << "Enter your choice: ";
        cin >> animalType;
        cin.get();

        if (animalType == "exit") return;
    }

    cout << "Enter name of your animal: ";
    getline(cin, name);
    cout << "Enter birth date of your animal: ";
    cin >> birthDate;
    cin.get();
    cout << "Enter breed of your animal: ";
    getline(cin, bread);
    cout << "Enter care schedule: ";
    getline(cin, careSchedule);

    if (animalType == "1") {
        cout << "Enter weight of animal: ";
        cin >> weight;
        cin.get();
        Dog* dog = new Dog(name, birthDate, bread, careSchedule, weight);
        petHotel.AddAnimal(dog);
        cout << "Your dog was succesfully added to our Pet Hotel. Its ID is " << dog->GetID() << endl;
    }
    else if (animalType == "2") {
        cout << "Enter weight of animal: ";
        cin >> weight;
        cin.get();
        Cat* cat = new Cat(name, birthDate, bread, careSchedule, weight);
        petHotel.AddAnimal(cat);
        cout << "Your cat was succesfully added to our Pet Hotel. Its ID is " << cat->GetID() << endl;
    }
    else if (animalType == "3") {
        cout << "Enter type of rodent: ";
        getline(cin, rodentType);
        cin.get();
        Rodent* rodent = new Rodent(name, birthDate, bread, careSchedule, rodentType);
        petHotel.AddAnimal(rodent);
        cout << "Your rodent was succesfully added to our Pet Hotel. Its ID is " << rodent->GetID() << endl;
    }
}

void MakeReservation(PetHotel& petHotel) {
    string startDate, endDate, isPutTogetherStr{"hd8ch3"};
    int shoudlExitAnimalChoose{0};

    cout << "Enter start date: ";
    cin >> startDate;
    cin.get();
    cout << "Enter end date: ";
    cin >> endDate;
    cin.get();
    while (isPutTogetherStr != "y" && isPutTogetherStr != "n") {
        cout << "Should your animals be put together with other animals (y/n): ";
        cin >> isPutTogetherStr;
        cin.get();
    }
    bool isPutTogether = (isPutTogetherStr == "y" ? true : false);

    while (shoudlExitAnimalChoose < 1 || shoudlExitAnimalChoose > 4) {
        cout << "Checking whether animal can be accomodated.";
        cout << "\t" << "1. Enter animal's ID";
        cout << "\t" << "2. Find an animal by name";
        cout << "\t" << "3. Add an animal";
        cout << "\t" << "4. Exit";
        cout << "Choose an option: ";
        cin >> shoudlExitAnimalChoose;
        cin.get();



    }
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

    //petHotel.SetKennels(InitKennels());

    //MakeReservation(petHotel);

    //RegisterAnimal(petHotel);

    petHotel.ListKannels();
    petHotel.ListReservations();
    petHotel.ListAnimals();


    return 0;
}