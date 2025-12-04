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
        cout << "Recommended care schedule: " << Animal::RecommendCareSchedule("Dog", weight) << endl;
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
        cout << "Recommended care schedule: " << Animal::RecommendCareSchedule("Cat", weight) << endl;
        cout << "Write your care schedule: ";
        getline(cin, careSchedule);

        animal = petHotel.AddAnimal("Cat", name, birthDate, bread, weight);
        animal->SetCareSchedule(careSchedule);
        cout << "Your cat was succesfully added to our Pet Hotel. Its ID is " << animal->GetID() << endl;
    }
    else if (animalType == 3) {
        cout << "Enter type of your rodent: ";
        getline(cin, rodentType);
        cout << "Recommended care schedule: " << Animal::RecommendCareSchedule("Rodent", rodentType) << endl;
        cout << "Write your care schedule: ";
        getline(cin, careSchedule);

        animal = petHotel.AddAnimal("Rodent", name, birthDate, bread, rodentType);
        animal->SetCareSchedule(careSchedule);
        cout << "Your " << rodentType <<  " was succesfully added to our Pet Hotel. Its ID is " << animal->GetID() << endl;
    }

    return animal;

}

void SelectAnimalSequence(PetHotel& petHotel, vector<Animal*>& sequence) {
    int chooseAnimalSelectionOption;

    cout << "Checking whether animal can be accommodated.\n";
    cout << "1. Enter animal's ID\n";
    cout << "2. Find an animal by name\n";
    cout << "3. Add an animal\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";

    cin >> chooseAnimalSelectionOption;

    switch (chooseAnimalSelectionOption) {
        case 0:
            // Exit
            break;

        case 1: { // Case 1 scope
            int animalID;
            cout << "Enter ID of your animal: ";
            cin >> animalID;
            cin.get();

            Animal* animal = petHotel.FindAnimal(animalID);
            if (animal != nullptr) {
                sequence.push_back(animal);
                cout << "Your " << animal->GetType() << " " << animal->GetID() << " is added to sequence.\n";
            } else {
                throw runtime_error("Animal not found");
            }
            break;
        }

        case 2: { // Case 2 scope
            string animalName;
            cout << "Enter name of your animal: ";
            cin >> animalName;
            cin.get();

            AnimalFilter animalFilter({{AnimalKey::Name, animalName}});
            auto filteredAnimals = petHotel.GetAnimals();
            animalFilter.Filter(filteredAnimals);

            if (filteredAnimals.empty()) {
                cout << "No animals found with that name.\n";
                break;
            }

            petHotel.DisplayAnimals(filteredAnimals);

            int chooseListOption{-1};
            while (chooseListOption < 0 || chooseListOption >= filteredAnimals.size()) {
                cout << "Choose an option: ";
                cin >> chooseListOption;
                cin.get();
            }

            sequence.push_back(filteredAnimals[chooseListOption]);
            cout << "Your " << filteredAnimals[chooseListOption]->GetType() << " "
                 << filteredAnimals[chooseListOption]->GetID() << " is added to sequence.\n";
            break;
        }

        case 3:
            sequence.push_back(RegisterAnimal(petHotel));
            break;

        default:
            throw runtime_error("Invalid option selected");
    }
}

void MakeReservation(PetHotel& petHotel) {
    bool addMoreAnimals{true};
    int chooseKennelManually{-1};
    vector<Animal*> sequence;
    vector<Kennel*> kennels;
    Reservation* reservation{nullptr};

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
        cout << "Should your animals be put together with other animals (1 - yes / 0 - no ): ";
        cin >> isPutTogetherInt;
        cin.get();
    }
    bool isPutTogether = static_cast<bool>(isPutTogetherInt);

    while (addMoreAnimals) {
        SelectAnimalSequence(petHotel, sequence);

        if (sequence.size() == 0) break;

        Animal* animal = sequence.back();
        vector<BookingData> bd = petHotel.AutoChooseKennels(animal, isPutTogether, datePeriod);
        if (bd.size() == 0) {
            cout << "Animal " << animal->GetName() << " cannot be accommodated in any kennel!" << endl;
        }else {
            while (chooseKennelManually < 0 || chooseKennelManually > 2){
                cout << "Choose an option: " << endl;
                cout << "\t" << "1. Agree for putting put in:" << endl;
                for (auto bdone: bd) {
                    cout << "\t" << "Kennel ID: " << bdone.kennelID;
                    cout << " from " << bdone.startDate.toString();
                    cout << " to " << bdone.endDate.toString() << endl;
                }
                cout << "\t" << "2. Choose kennel manually" << endl;
                cin >> chooseKennelManually;
                cin.get();
            }
            if (chooseKennelManually == 1) {
                petHotel.AddReservation(startDate, endDate, isPutTogether, animal);
                for (auto bdone: bd) {
                    petHotel.AddBooking(animal, bdone.kennelID, DatePeriod(bdone.startDate, bdone.endDate));
                }
            }
            else if (chooseKennelManually == 2) {
                petHotel.DisplayKennels(kennels);
                cout << "Choose an option: ";
                int option{-1};
                cin >> option;
                cin.get();
            }
        }


        cout << "Do you want to add another animal (0 - false / 1 - true): ";
        int addAnother{-1};
        while (addAnother < 0 || addAnother > 1) {
            cin >> addAnother;
        }
        if (addAnother == 0) addMoreAnimals = false;


    }



}



void InitKennels(PetHotel& petHotel) {
    //default_random_engine engine{static_cast<unsigned int>(time(0))};
    //uniform_int_distribution<int> distribution{3,8}; used earlier for dynamic capacity

    //large
    for (int i = 0; i < 2; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Large", 4, true);
        petHotel.AddKennel(kennel);
    }

    /*
    //medium
    for (int i = 0; i < 20; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Medium", 4, true);
        petHotel.AddKennel(kennel);
    }

    //small
    for (int i = 0; i < 50; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Small", 4, true);
        petHotel.AddKennel(kennel);
    }

    //large
    for (int i = 0; i < 30; i++) {
        Kennel* kennel = new Kennel(IDManager::NewID("Kennel"),"Mini", 4, true);
        petHotel.AddKennel(kennel);
    }

    */

}

int main() {
    PetHotel petHotel;
    //InitKennels(petHotel);

    int choice{-1};

    while (choice < 0 || choice > 10) {
        cout << "===================== MENU ====================" << endl;
        cout << "0. Exit" << endl;
        cout << "1. Register an animal" << endl;
        cout << "2. Make an reservation" << endl;
        cout << "3. Display all animals" << endl;
        cout << "4. Display all reservations" << endl;
        cout << "5. Display all kennels" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cin.get();

        if (choice == 0) return 0;
        else if (choice == 1) RegisterAnimal(petHotel);
        else if (choice == 2) MakeReservation(petHotel);
        else if (choice == 3) petHotel.DisplayAnimals();
        else if (choice == 4) petHotel.DisplayReservations();
        else if (choice == 5) petHotel.DisplayKennels();
    }

    return 0;
}