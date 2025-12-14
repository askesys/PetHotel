#include <iostream>
#include "PetHotel.h"
#include <sstream>
#include "Animals/AnimalFilter.h"


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

            if (animal == nullptr){
                cout << "Animal " << animalID << " not found.\n";

            }
            else if (find(sequence.begin(), sequence.end(), animal) != sequence.end()) {
                cout << "Animal " << animalID << "has been already added to the sequence.\n";
            }
            else{
                sequence.push_back(animal);
                cout << "Your " << animal->GetType() << " " << animal->GetID() << " is added to sequence.\n";
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

            Animal* animal = filteredAnimals[chooseListOption];

            if (find(sequence.begin(), sequence.end(), animal) != sequence.end()) {
                cout << "Animal " << animal->GetID() << "has been already added to the sequence.\n";
            }
            else{
                sequence.push_back(animal);
                cout << "Your " << animal->GetType() << " " << animal->GetID() << " is added to sequence.\n";
            }
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
    Kennel* kennel;
    Reservation* reservation{nullptr};
    vector<BookingData> bd;
    string startDate, endDate;
    Date sDate, eDate;
    DatePeriod datePeriod;
    int isPutTogetherInt{-1}, kennelID{-1};

    bool sdCorrect = true;
    while (sdCorrect) {
        cout << "Enter start date: ";
        cin >> startDate;
        cin.get();
        sDate = Date(startDate);
        sdCorrect = !Booking::isValidStartDate(sDate);
    }

    bool edCorrect = true;
    while (edCorrect) {
        cout << "Enter end date: ";
        cin >> endDate;
        cin.get();
        eDate = Date(endDate);
        datePeriod = DatePeriod(sDate, eDate);
        edCorrect = !Booking::isValidPeriod(datePeriod);
    }

    while (isPutTogetherInt < 0 || isPutTogetherInt > 1) {
        cout << "Should your animals be put together with other animals (1 - yes / 0 - no ): ";
        cin >> isPutTogetherInt;
        cin.get();
    }
    bool isPutTogether = static_cast<bool>(isPutTogetherInt);

    while (addMoreAnimals) {
        SelectAnimalSequence(petHotel, sequence);

        if (sequence.empty()) break;

        Animal* animal = sequence.back();
        if (!petHotel.IsValidReservation(animal, datePeriod)) {
            cout << "This animal has conflict reservation" << endl;
            sequence.pop_back();
            continue;
        }

        bd = petHotel.AutoChooseKennels(animal, isPutTogether, datePeriod);
        if (bd.empty()) {
            cout << "Animal " << animal->GetName() << " cannot be accommodated in any kennel!" << endl;
            continue;
        }

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

        if (chooseKennelManually == 1) {
            if (reservation == nullptr) {
                reservation =  petHotel.AddReservation(startDate, endDate, isPutTogether, animal);
            }
            else {
                reservation->AddAnimal(animal);
            }

            for (auto bdone: bd) {
                petHotel.AddBooking(animal, reservation->GetID(), bdone.kennelID, DatePeriod(bdone.startDate, bdone.endDate));
            }
        }
        else if (chooseKennelManually == 2) {
            cout << "Input ID of the kennel: ";
            cin >> kennelID;
            cin.get();

            kennel = petHotel.FindKennel(kennelID);

            bool status = petHotel.ChooseKennel(kennel, animal, isPutTogether, datePeriod);

            if (status) {
                if (reservation == nullptr) {
                    reservation =  petHotel.AddReservation(startDate, endDate, isPutTogether, animal);
                }
                else {
                    reservation->AddAnimal(animal);
                }

                petHotel.AddBooking(animal, reservation->GetID(), kennelID, datePeriod);
            }
            else {
                cout << "This animal cannot be accommodated in this kennel" << endl;
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
    for (int i = 0; i < 10; i++) {
        Kennel* kennel = new Kennel("Large", 4);
        petHotel.AddKennel(kennel);
    }

    //medium
    for (int i = 0; i < 20; i++) {
        Kennel* kennel = new Kennel("Medium", 4);
        petHotel.AddKennel(kennel);
    }

    //small
    for (int i = 0; i < 50; i++) {
        Kennel* kennel = new Kennel("Small", 4);
        petHotel.AddKennel(kennel);
    }

    //large
    for (int i = 0; i < 30; i++) {
        Kennel* kennel = new Kennel("Mini", 4);
        petHotel.AddKennel(kennel);
    }

}



void ManipulateKennels(PetHotel& petHotel) {
    bool executionCycle{true};
    string command;

    while (executionCycle) {
        cout << "Execute a command or call \"help\": ";
        cin >> command;

        if (command == "help") {
            cin.get();
            cout << "exit -> abrupt this procedure" << endl;
            cout << "add L -> it creates one large kennel. Other options M - medium, S - small, R - for rodents" << endl;
            cout << "remove -> remove a kennel. It will show you list of kennels and ask for ID" << endl;
        }
        else if (command == "add") {
            string size;
            cin >> size;
            cin.get();
            if (size == "L") petHotel.AddKennel("Large");
            else if (size == "M") petHotel.AddKennel("Medium");
            else if (size == "S") petHotel.AddKennel("Small");
            else if (size == "R") petHotel.AddKennel("Mini");
        }
        else if (command == "remove") {
            int id;

            petHotel.DisplayKennels();
            cout << "Write an ID of a kennel which you want to delete: ";
            cin >> id;
            cin.get();
            Kennel* kennel = petHotel.FindKennel(id);
            if (kennel) petHotel.RemoveKennel(kennel);
            else cout << "Kennel " << id << " doesn't exist" << endl;
        }
        else if (command == "exit") executionCycle = false;
    }

}

void MoveAnimals(PetHotel& petHotel) {
    Reservation* reservation;
    Animal* animal;
    vector<Animal*> animals;
    int reservationOption, anOption, kennelID;
    string startDate, endDate;
    Date sDate, eDate;
    DatePeriod datePeriod;
    Kennel* kennel;


    petHotel.DisplayReservations();
    cout << "Enter reservation option: ";
    cin >> reservationOption;
    cin.get();

    reservation = petHotel.GetReservations()[reservationOption];
    animals = reservation->GetAnimals();
    petHotel.DisplayAnimals(animals);

    cout << "Enter the animal which you want to move (First column): ";
    cin >> anOption;
    cin.get();
    animal = animals[anOption];

    cout << "Input a kennel ID where do you want to relocate an animal: ";
    cin >> kennelID;
    cin.get();
    kennel = petHotel.FindKennel(kennelID);

    bool sdCorrect = true;
    while (sdCorrect) {
        cout << "Enter start date: ";
        cin >> startDate;
        cin.get();
        sDate = Date(startDate);
        sdCorrect = !Booking::isValidStartDate(sDate) && sDate >= Date(reservation->GetStartDate());
    }

    bool edCorrect = true;
    while (edCorrect) {
        cout << "Enter end date: ";
        cin >> endDate;
        cin.get();
        eDate = Date(endDate);
        datePeriod = DatePeriod(sDate, eDate);
        edCorrect = !Booking::isValidPeriod(datePeriod) && eDate <= Date(reservation->GetEndDate());
    }

    petHotel.MoveAnimal(reservation, animal, kennel, datePeriod);

}

void ChangeReservation(PetHotel& petHotel) {
    int option{-1}, choice{-1};
    Reservation* reservation;

    petHotel.DisplayReservations();
    cout << "Enter reservation option: ";
    cin >> option;
    cin.get();
    reservation = petHotel.GetReservations()[option];

    while (choice != 0) {
        cout << "\n--- Edit Reservation (ID: " << reservation->GetID() << ") ---\n";
        cout << "1. Change start date (current: " << reservation->GetStartDate() << ")\n";
        cout << "2. Change end date (current: " << reservation->GetEndDate() << ")\n";
        cout << "3. Change animals' list\n";
        cout << "0. Exit editing\n";
        cout << "Choose an option: ";

        cin >> choice;
        cin.get();

        if (choice == 1) {
            string startDate;
            cout << "Enter start date: ";
            cin >> startDate;
            cin.get();
            petHotel.EditReservation(reservation, DatePeriod(Date(startDate), reservation->GetEndDate()));
        }
        else if (choice == 2) {
            string endDate;
            cout << "Enter end date: ";
            cin >> endDate;
            cin.get();
            petHotel.EditReservation(reservation, DatePeriod(reservation->GetStartDate(), Date(endDate)));
        }
        else if (choice == 3) {
            vector<Animal*> animals;
            string line;

            petHotel.DisplayAnimals();
            cout << "Enter animals' options (like \"2 4 ...\": ";
            getline(cin, line);
            stringstream ss(line);
            while (!ss.eof()) {
                int id;
                ss >> id;
                Animal* animal = petHotel.GetAnimals()[id];
                animals.push_back(animal);
            }

            petHotel.EditReservation(reservation, animals);
        }
        else if (choice == 0) {
            return;
        }
        else {
            cout << "Invalid choice\n";
        }
    }
}

void RemoveReservation(PetHotel& petHotel) {
    int option;
    Reservation* reservation;

    petHotel.DisplayReservations();
    cout << "Enter reservation option: ";
    cin >> option;
    cin.get();
    reservation = petHotel.GetReservations()[option];
    petHotel.RemoveReservation(reservation);
}

int main() {
    PetHotel petHotel;
    int actorOption{-1};
    bool executionCycle{true};
    //InitKennels(petHotel);

    int choice{-1};

    cout << "Choose an actor: " << endl;
    cout << "\t1. Customer" << endl;
    cout << "\t2. Employer" << endl;
    cout << "\t0. Exit" << endl;
    cout << "Choose an option: ";
    cin >> actorOption;
    cin.get();

    if (actorOption == 1) {
        while (executionCycle) {
            cout << "===================== CUSTOMER'S MENU ====================" << endl;
            cout << "0. Exit" << endl;
            cout << "1. Make reservation" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.get();

            if (choice == 0) executionCycle = false;
            else if (choice == 1) MakeReservation(petHotel);
            else cout << "Invalid choice\n";
        }
    }
    else if (actorOption == 2) {
        while (executionCycle) {
            cout << "===================== EMPLOYEE'S MENU ====================" << endl;
            cout << "0. Exit" << endl;
            cout << "1. Register an animal" << endl;
            cout << "2. Display all animals" << endl;
            cout << "3. Display all reservations" << endl;
            cout << "4. Display all kennels" << endl;
            cout << "5. Manipulate kennels" << endl;
            cout << "6. Move animal" << endl;
            cout << "7. Change reservation" << endl;
            cout << "8. Remove reservation" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.get();

            if (choice == 0) executionCycle = false;
            else if (choice == 1) RegisterAnimal(petHotel);
            else if (choice == 2) petHotel.DisplayAnimals();
            else if (choice == 3) petHotel.DisplayReservations();
            else if (choice == 4) petHotel.DisplayKennels();
            else if (choice == 5) ManipulateKennels(petHotel);
            else if (choice == 6) MoveAnimals(petHotel);
            else if (choice == 7) ChangeReservation(petHotel);
            else if (choice == 8) RemoveReservation(petHotel);
            else cout << "Invalid choice\n";
        }
    }
    else if (actorOption == 0) return 0;
    else {
        cout << "Invalid choice\n";
        exit(1);
    }

    return 0;
}
