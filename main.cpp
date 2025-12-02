#include <iostream>
#include "PetHotel.h"
#include "IDManager.h"
#include<random>

#include "Animals/Cat.h"
#include "Animals/Dog.h"
#include "Animals/Rodent.h"
#include "Animals/AnimalFilter.h"
#include "Files/AnimalsFH.h"

using namespace std;


Animal* RegisterAnimal(PetHotel& petHotel) {
    string name, birthDate, bread, careSchedule, rodentType;
    int animalType{-1}, weight;
    Animal* animal;

    while (animalType < 1 || animalType > 3) {
        cout << "Choose a type of your animal" << endl;
        cout << "\t" << "1. Dog" << endl;
        cout << "\t" << "2. Cat" << endl;
        cout << "\t" << "3. Rodent" << endl;
        cout << "\t" << "Write \"0\" to abort this procedure" << endl;
        cout << "Enter your choice: ";
        cin >> animalType;
        cin.get();

        if (animalType == 0) return nullptr;
    }

    cout << "Enter name of your animal: ";
    getline(cin, name);
    cout << "Enter birth date of your animal: ";
    cin >> birthDate;
    cin.get();
    cout << "Enter breed of your animal: ";
    getline(cin, bread);

    if (animalType == 1) {
        cout << "Enter weight of animal: ";
        cin >> weight;
        cin.get();
        cout << "Recommended care schedule: " << Animal::RecommendCareSchedule("Dog", weight);
        cout << "Write your care schedule: ";
        getline(cin, careSchedule);

        animal = petHotel.AddAnimal("Dog", name, birthDate, bread, weight);
        animal->SetCareSchedule(careSchedule);
        cout << "Your dog was succesfully added to our Pet Hotel. Its ID is " << animal->GetID() << endl;
    }
    else if (animalType == 2) {
        cout << "Enter weight of animal: ";
        cin >> weight;
        cin.get();
        cout << "Recommended care schedule: " << Animal::RecommendCareSchedule("Cat", weight);
        cout << "Write your care schedule: ";
        getline(cin, careSchedule);

        animal = petHotel.AddAnimal("Cat", name, birthDate, bread, weight);
        animal->SetCareSchedule(careSchedule);
        cout << "Your dog was succesfully added to our Pet Hotel. Its ID is " << animal->GetID() << endl;
    }
    else if (animalType == 3) {
        cout << "Enter type of your rodent: ";
        getline(cin, rodentType);
        cout << "Recommended care schedule: " << Animal::RecommendCareSchedule("Rodent", rodentType);
        cout << "Write your care schedule: ";
        getline(cin, careSchedule);

        animal = petHotel.AddAnimal("Rodent", name, birthDate, bread, rodentType);
        animal->SetCareSchedule(careSchedule);
        cout << "Your dog was succesfully added to our Pet Hotel. Its ID is " << animal->GetID() << endl;
    }

    return animal;

}

void SelectAnimalSequence(PetHotel& petHotel, vector<Animal*>& sequence) {
    int chooseAnimalSelectionOption{-1}, chooseListOption{-1};

    while (chooseAnimalSelectionOption < 0 || chooseAnimalSelectionOption > 4) {
        cout << "Checking whether animal can be accomodated.";
        cout << "\t" << "1. Enter animal's ID";
        cout << "\t" << "2. Find an animal by name";
        cout << "\t" << "3. Add an animal";
        cout << "\t" << "0. Exit";
        cout << "Choose an option: ";
        cin >> chooseAnimalSelectionOption;
        cin.get();
    }


    switch (chooseAnimalSelectionOption) {
        case 0:
            return;
        case 1:
            int animalID;
            cout << "Enter ID of your animal: ";
            cin >> animalID;
            cin.get();
            Animal* animal = petHotel.FindAnimal(animalID);
            if (animal != nullptr) {
                sequence.push_back(animal);
                cout << "Your " << animal->GetType() << " " << animal->GetID() << " is added to sequence" << endl;
            }
            else throw runtime_error("Animal not found");
            break;
        case 2:
            string animalName;
            cout << "Enter ID of your animal: ";
            cin >> animalID;
            cin.get();
            AnimalFilter animalFilter({{AnimalKey::Name,animalName}});
            auto filteredAnimals = petHotel.GetAnimals();
            animalFilter.Filter(filteredAnimals);
            petHotel.DisplayAnimals(filteredAnimals);
            while (chooseListOption < 0 && chooseListOption > filteredAnimals.size()) {
                cout << "Choose an option: ";
                cin >> chooseListOption;
                cin.get();
            }
            sequence.push_back(filteredAnimals[chooseListOption]);
            cout << "Your " << filteredAnimals[chooseListOption]->GetType() << " ";
            cout << filteredAnimals[chooseListOption]->GetID() << " is added to sequence" << endl;
            break;
        case 3:
            sequence.push_back(RegisterAnimal(petHotel));
    }
}

void MakeReservation(PetHotel& petHotel) {
    bool addMoreAnimals{true};
    int chooseKennelManually{-1};
    vector<Animal*> sequence;
    vector<Kennel*> kennels;

    while (addMoreAnimals) {
        SelectAnimalSequence(petHotel, sequence);
        cout << "Do you want to add another animal (0 - false / 1 - true): ";
        int addAnother{-1};
        while (addAnother < 0 || addAnother > 1) {
            cin >> addAnother;
        }
        if (addAnother == 0) addMoreAnimals = false;
    }

    string startDate, endDate;
    int isPutTogetherInt{-1};

    cout << "Enter start date: ";
    cin >> startDate;
    cin.get();
    cout << "Enter end date: ";
    cin >> endDate;
    cin.get();

    Date sDate(startDate);
    Date eDate(endDate);

    DatePeriod datePeriod(sDate, eDate);
    while (isPutTogetherInt < 0 || isPutTogetherInt > 1) {
        cout << "Should your animals be put together with other animals (y/n): ";
        cin >> isPutTogetherInt;
        cin.get();
    }
    bool isPutTogether = static_cast<bool>(isPutTogetherInt);
    for (Animal* animal : sequence) {
        kennels = petHotel.ChooseKennels(animal, isPutTogether, datePeriod);
        if (kennels.size() == 0) {
            cout << "Animal " << animal->GetName() << " cannot be accommodated in any kennel!" << endl;
        }
        while (chooseKennelManually < 0 || chooseKennelManually > 1){
            cout << "Choose an option: " << endl;
            cout << "\t" << "1. Choose kennel manually" << endl;
            cout << "\t" << "2. Agree: put in " << kennels[0]->GetID() << " kennel" << endl;
        }
    }

}



void InitKennels(PetHotel& petHotel) {
    default_random_engine engine{static_cast<unsigned int>(time(0))};
    uniform_int_distribution<int> distribution{3,8};

    //large
    for (int i = 0; i < 10; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Large", distribution(engine), true);
        petHotel.AddKennel(kennel);
    }

    //medium
    for (int i = 0; i < 20; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Medium", distribution(engine), true);
        petHotel.AddKennel(kennel);
    }

    //small
    for (int i = 0; i < 50; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Small", distribution(engine), true);
        petHotel.AddKennel(kennel);
    }

    //large
    for (int i = 0; i < 30; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Mini", 4, true);
        petHotel.AddKennel(kennel);
    }

}

int main() {
    PetHotel petHotel;

    //InitKennels(petHotel);

    //MakeReservation(petHotel);

    //RegisterAnimal(petHotel);

    petHotel.DisplayKennels();
    //petHotel.DisplayReservations();
    AnimalFilter animalFilter({{AnimalKey::Type,"Dog"}});
    //petHotel.DisplayAnimals(animalFilter);


    return 0;
}