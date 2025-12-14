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
#include <set>

using namespace std;

PetHotel::PetHotel() {
    SetAnimals(animalsFH.Read());
    SetReservations(reservationsFH.Read(&animalsMap));
    SetKennels(kennelsFH.Read(&animalsMap));
    booking.GenerateBookingCalendar(kennels,animalsMap);
    IDManager::Read();
    auto animalsInKennels = booking.GetCurrentAnimals(animalsMap);
    SetRelevantAnimals(animalsInKennels);
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

Animal *PetHotel::AddAnimal(const string &type, const string &name, const string &birthDate,
                            const string &breed, int weight)
{
    if (type == "Dog") {
        Dog* dog = new Dog(name, birthDate, breed, weight);
        this->animals.push_back(dog);
        animalsFH.Write(dog);
        animalsMap[dog->GetID()] = dog;
        return dog;
    }
    else if (type == "Cat") {
        Cat* cat = new Cat(name, birthDate, breed, weight);
        this->animals.push_back(cat);
        animalsFH.Write(cat);
        animalsMap[cat->GetID()] = cat;
        return cat;
    }
    else {
        throw invalid_argument("PetHotel::AddAnimal: Incorrect Animal type.");
    }
}

Animal *PetHotel::AddAnimal(const string &type, const string &name, const string &birthDate,
                            const string &breed, const string &rodentType)
{
    if (type == "Rodent") {
        Rodent* rodent = new Rodent(name, birthDate, breed, rodentType);
        this->animals.push_back(rodent);
        animalsFH.Write(rodent);
        animalsMap[rodent->GetID()] = rodent;
        return rodent;
    }
    else {
        throw invalid_argument("PetHotel::AddAnimal: Incorrect Animal type.");
    }
}

void PetHotel::MoveAnimal(Reservation* reservation, Animal* animal, Kennel* kennel, DatePeriod period)
{
    if (!ChooseKennel(kennel, animal, reservation->GetPutTogether(), period)) {
        cout << "Cannot accommodate the animal in this kennel for this period" << endl;
        return;
    }

    auto bookings = booking.GetBookings(reservation->GetID(), animal->GetID());

    Date targetStartDate = period.getStart();
    Date targetEndDate   = period.getEnd();

    int rID = reservation->GetID();
    int aID = animal->GetID();
    int newKID = kennel->GetID();
    int requiredSpace = reservation->GetPutTogether() ? -1 : animal->GetSpace();

    for (BookingEntry* bookingEntry : bookings) {
        Date sDate = bookingEntry->GetStartDate();
        Date eDate = bookingEntry->GetEndDate();
        int oldKID = bookingEntry->GetKennelID();

        if (eDate <= targetStartDate || sDate >= targetEndDate) {
            continue;
        }

        booking.RemoveBooking(bookingEntry, animalsMap);

        if (sDate < targetStartDate) {
            DatePeriod left(sDate, targetStartDate);
            if (left.length() > 0) {
                booking.AddBooking(rID, aID, oldKID, left, requiredSpace);
            }
        }

        Date moveStart = std::max(sDate, targetStartDate);
        Date moveEnd   = std::min(eDate, targetEndDate);

        DatePeriod moved(moveStart, moveEnd);
        if (moved.length() > 0) {
            booking.AddBooking(rID, aID, newKID, moved, requiredSpace);
        }

        if (eDate > targetEndDate) {
            DatePeriod right(targetEndDate, eDate);
            if (right.length() > 0) {
                booking.AddBooking(rID, aID, oldKID, right, requiredSpace);
            }
        }
    }

    auto animalsInKennels = booking.GetCurrentAnimals(animalsMap);
    SetRelevantAnimals(animalsInKennels);
}


vector<Kennel*> PetHotel::GetKennels() const {
    return this->kennels;
}

void PetHotel::SetKennels(vector<Kennel*> kennels) {
    this->kennels = kennels;
}

void PetHotel::SetRelevantAnimals(map<int, vector<Animal *> > animalsInKennels) {
    for (Kennel* kennel: this->kennels) {
        kennel->SetAnimals(vector<Animal *>());
        kennel->SetType("NULL");
        kennel->SetIsEmpty(true);

        if (animalsInKennels.contains(kennel->GetID())) {
            for (Animal* animal: animalsInKennels[kennel->GetID()]) {
                kennel->AddAnimal(animal);
                if (kennel->GetType() == "NULL") {
                    string kennelType = animal->GetType();
                    if (kennelType == "Rodent") kennelType = dynamic_cast<Rodent*>(animal)->GetRodentType();
                    kennel->SetType(kennelType);
                    kennel->SetIsEmpty(false);
                }
            }
        }
    }
}


void PetHotel::AddKennel(Kennel *kennel) {
    kennels.push_back(kennel);
}

void PetHotel::AddKennel(const string &size) {
    Kennel* kennel = new Kennel(size, Kennel::STANDART_CAPACITY);
    this->kennels.push_back(kennel);
}


void PetHotel::RemoveKennel(Kennel *kennel) {
    if (booking.isAnyBooked(kennel->GetID())) {
        cout << "You cannot delete this kennel becasue for it exists relevant bookings:" << endl;
        for (auto be: booking.GetBookings(kennel->GetID())) {
            cout << "\t >> Animal " << be->GetAnimalID() << " is located from "
                 << be->GetStartDate() << " to " << be->GetEndDate() << endl;
        }
    } else erase(kennels, kennel);
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

Reservation *PetHotel::AddReservation(const string &startDate, const string &endDate, bool putTogether, Animal *animal) {
    Reservation* reservation = new Reservation(startDate, endDate, putTogether, animal);
    this->reservations.push_back(reservation);
    return reservation;
}


bool PetHotel::IsValidReservation(Animal *animal, DatePeriod period) {
    for (auto reserv: this->reservations) {
        for (auto ranim: reserv->GetAnimals()) {
            if (ranim == animal && period.overlaps(DatePeriod(Date(reserv->GetStartDate()), Date(reserv->GetEndDate())))) {
                return false;
            }
        }
    }
    return true;
}


Reservation *PetHotel::FindReservation(int reservationID) const {
    for (int i = 0; i < this->reservations.size(); i++) {
        if (this->reservations[i]->GetID() == reservationID) {
            return this->reservations[i];
        }
    }
    return nullptr;
}

void PetHotel::EditReservation(Reservation *reservation, DatePeriod period) {
    Date currentStartDate = reservation->GetStartDate();
    Date currentEndDate   = reservation->GetEndDate();

    Date targetStartDate = period.getStart();
    Date targetEndDate   = period.getEnd();

    int rID = reservation->GetID();

    for (Animal* animal : reservation->GetAnimals()) {
        int aID = animal->GetID();
        int requiredSpace = reservation->GetPutTogether() ? -1 : animal->GetSpace();

        auto bookingEntries = booking.GetBookings(rID, aID);

        for (BookingEntry* entry : bookingEntries) {
            Date sDate = entry->GetStartDate();
            Date eDate = entry->GetEndDate();
            int kID    = entry->GetKennelID();

            booking.RemoveBooking(entry, animalsMap);

            Date newStart = std::max(sDate, targetStartDate);
            Date newEnd   = std::min(eDate, targetEndDate);

            if (newStart < newEnd) {
                booking.AddBooking(rID, aID, kID, DatePeriod(newStart, newEnd), requiredSpace);
            }
        }
    }

    DatePeriod leftExtended, rightExtended;
    map<Animal*, vector<BookingData>> leftBookingData, rightBookingData;

    if (targetStartDate < currentStartDate) {
        leftExtended = DatePeriod(targetStartDate, currentStartDate);
        for (Animal* animal : reservation->GetAnimals()) {
            auto bd = AutoChooseKennels(animal, reservation->GetPutTogether(), leftExtended);
            if (bd.empty()) {
                cout << "Refused: Animal " << animal->GetName() << endl;
                return;
            }
            leftBookingData[animal] = bd;
        }
    }

    if (currentEndDate < targetEndDate) {
        rightExtended = DatePeriod(currentEndDate, targetEndDate);
        for (Animal* animal : reservation->GetAnimals()) {
            auto bd = AutoChooseKennels(animal, reservation->GetPutTogether(), rightExtended);
            if (bd.empty()) {
                cout << "Refused: Animal " << animal->GetName() << endl;
                return;
            }
            rightBookingData[animal] = bd;
        }
    }

    for (Animal* animal : reservation->GetAnimals()) {
        int aID = animal->GetID();
        int requiredSpace = reservation->GetPutTogether() ? -1 : animal->GetSpace();

        if (leftExtended.length() > 0) {
            for (BookingData bd : leftBookingData[animal]) {
                booking.AddBooking(rID, aID, bd.kennelID, leftExtended, requiredSpace);
            }
        }

        if (rightExtended.length() > 0) {
            for (BookingData bd : rightBookingData[animal]) {
                booking.AddBooking(rID, aID, bd.kennelID, rightExtended, requiredSpace);
            }
        }
    }

    reservation->SetStartDate(targetStartDate.toString());
    reservation->SetEndDate(targetEndDate.toString());

    auto animalsInKennels = booking.GetCurrentAnimals(animalsMap);
    SetRelevantAnimals(animalsInKennels);
}


void PetHotel::EditReservation(Reservation *reservation, const vector<Animal *>& targetAnimals) {
    int reservationID = reservation->GetID();

    set<Animal*> setTargetAnimals(targetAnimals.begin(), targetAnimals.end());
    set<Animal*> setCurrentAnimals;
    for (auto a : reservation->GetAnimals()) {
        if (a) setCurrentAnimals.insert(a);
    }

    vector<Animal*> newAnimals;
    vector<Animal*> oldAnimals;
    map<Animal*, vector<BookingData> > booking_datas;

    DatePeriod datePeriod(DatePeriod(reservation->GetStartDate(), reservation->GetEndDate()));

    set_difference(setTargetAnimals.begin(), setTargetAnimals.end(),
        setCurrentAnimals.begin(),setCurrentAnimals.end(),
        back_inserter(newAnimals)
        );

    set_difference(setCurrentAnimals.begin(), setCurrentAnimals.end(),
        setTargetAnimals.begin(), setTargetAnimals.end(),
        back_inserter(oldAnimals)
        );

    if (!newAnimals.empty()) {
        for (Animal* animal : newAnimals) {
            auto bookingData = AutoChooseKennels(animal, reservation->GetPutTogether(), datePeriod);
            if (bookingData.empty()) {
                cout << "Refused: New animal " << animal->GetName() << " (" << animal->GetID() << ") cannot be accommodate" << endl;
                return;
            }
            booking_datas[animal] = bookingData;
        }
    }

    if (!oldAnimals.empty()) {
        for (Animal* animal : oldAnimals) {
            auto bookings = booking.GetBookings(reservationID, animal->GetID());
            for(auto boo: bookings){
                booking.RemoveBooking(boo, animalsMap);
            }
        }
    }

    if (!newAnimals.empty()) {
        for (Animal* animal : newAnimals) {
            int requiredSpace = reservation->GetPutTogether() ? -1 : animal->GetSpace();
            for (BookingData bd: booking_datas[animal]) {
                DatePeriod dp(bd.startDate, bd.endDate);
                booking.AddBooking(reservationID, animal->GetID(), bd.kennelID, dp, requiredSpace);
            }
        }
    }

    reservation->SetAnimals(targetAnimals);
    auto animalsInKennels = booking.GetCurrentAnimals(animalsMap);
    SetRelevantAnimals(animalsInKennels);
}

void PetHotel::RemoveReservation(Reservation *reservation) {
    for (Animal* animal: reservation->GetAnimals()) {
        auto bookings = booking.GetBookings(reservation->GetID(), animal->GetID());
        for(auto boo: bookings) {
            booking.RemoveBooking(boo, animalsMap);
        }
    }

    auto it = find(reservations.begin(), reservations.end(), reservation);
    if (it != reservations.end()) {
        reservations.erase(it);
    }
    delete reservation;
}


void PetHotel::AddBooking(Animal* animal, int reservationID, int kennelID, DatePeriod datePeriod, bool fullBooking) {
    int requiredSpace = fullBooking ? -1 : animal->GetSpace();
    booking.AddBooking(reservationID, animal->GetID(), kennelID, datePeriod, requiredSpace);
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

vector<BookingData> PetHotel::AutoChooseKennels(Animal* animal, bool putTogether, DatePeriod datePeriod) {
    string type = animal->GetType();
    vector<Kennel*> result;
    string rodentType;
    int requiredSpace{1};

    if (type == "Dog") {
        requiredSpace = animal->GetSpace();

        for (int i = 0; i < this->kennels.size(); i++) {
            bool accepted = true;

            if (requiredSpace > kennels[i]->GetFullSpace())
                accepted = false;
            else if (kennels[i]->GetType() != "Dog" && kennels[i]->GetType() != "NULL")
                accepted = false;
            else if (kennels[i]->GetSize() == "Mini")
                accepted = false;

            if (accepted)
                result.push_back(kennels[i]);
        }
    }
    else if (type == "Cat") {
         requiredSpace = animal->GetSpace();

        for (int i = 0; i < this->kennels.size(); i++) {
            bool accepted = true;

            if (requiredSpace > kennels[i]->GetFullSpace())
                accepted = false;
            else if (kennels[i]->GetType() != "Cat" && kennels[i]->GetType() != "NULL")
                accepted = false;
            else if (kennels[i]->GetSize() == "Mini")
                accepted = false;

            if (accepted)
                result.push_back(kennels[i]);
        }
    }
    else if (type == "Rodent") {
        rodentType = dynamic_cast<Rodent*>(animal)->GetRodentType();
        requiredSpace = animal->GetSpace();

        for (int i = 0; i < this->kennels.size(); i++) {
            bool accepted = true;

            if (kennels[i]->GetSize() != "Mini")
                accepted = false;
            else if (kennels[i]->GetType() != rodentType && kennels[i]->GetType() != "NULL")
                accepted = false;

            if (accepted)
                result.push_back(kennels[i]);
        }
    }
    else {
        throw logic_error("Choose kennel: Didn't find a valid Animal type.");
    }

    vector<BookingData> booking_datas;
    booking.FindPossibleBookings(result, datePeriod, requiredSpace, booking_datas);

    return booking_datas;
}

bool PetHotel::ChooseKennel(Kennel *kennel, Animal *animal, bool putTogether, DatePeriod datePeriod) {
    vector<Kennel*> result{};
    int requiredSpace{1};
    string type = animal->GetType();
    bool accepted = true;

    if (type == "Dog") {
        requiredSpace = animal->GetSpace();

        if (requiredSpace > kennel->GetFullSpace())
            accepted = false;
        else if (kennel->GetType() != "Dog" && kennel->GetType() != "NULL")
            accepted = false;
        else if (kennel->GetSize() == "Mini")
            accepted = false;

        if (accepted)
            result.push_back(kennel);

    }
    else if (type == "Cat") {
        requiredSpace = animal->GetSpace();

        if (requiredSpace > kennel->GetFullSpace())
            accepted = false;
        else if (kennel->GetType() != "Cat" && kennel->GetType() != "NULL")
            accepted = false;
        else if (kennel->GetSize() == "Mini")
            accepted = false;

        if (accepted)
            result.push_back(kennel);
    }
    else if (type == "Rodent") {
        string rodentType = dynamic_cast<Rodent*>(animal)->GetRodentType();
        requiredSpace = animal->GetSpace();

        if (kennel->GetSize() != "Mini")
            accepted = false;
        else if (kennel->GetType() != rodentType && kennel->GetType() != "NULL")
            accepted = false;

        if (accepted)
            result.push_back(kennel);
    }
    else {
        throw logic_error("Choose kennel: Didn't find a valid Animal type.");
    }


    return booking.isBookingExists(result, datePeriod, requiredSpace);
}



void PetHotel::DisplayKennels() {
    cout << endl;
    cout << "==================================== Kennels =========================================" << endl;
    cout << setw(5) << "#" << "|"
         << setw(10) << "ID" << "|"
         << setw(10) << "Type" << "|"
         << setw(10) << "Capacity" << "|"
         << setw(10) << "Size" << "|"
         << setw(20) << "Animals" << endl;
    cout << "======================================================================================" << endl;

    for (int i = 0; i < this->kennels.size(); i++) {
        cout << setw(5) << i << "|";
        cout << setw(10) << this->kennels[i]->GetID() << "|";
        cout << setw(10) << this->kennels[i]->GetType() << "|";
        cout << setw(10) << this->kennels[i]->GetCapacity() << "|";
        cout << setw(10) << this->kennels[i]->GetSize() << "|";

        vector<Animal*> animals = this->kennels[i]->GetAnimals();
        cout << setw(20) << "[";
        for (int j = 0; j < animals.size(); j++) {
            cout << animals[j]->GetID();
            if (j < animals.size() - 1) cout << ", ";
        }
        cout << "]";
        cout << endl;
    }

    cout << "======================================================================================" << endl;
}

void PetHotel::DisplayKennels(vector<Kennel*> sliced_kennels) {
    cout << endl;
    cout << "==================================== Kennels =========================================" << endl;
    cout << setw(5) << "#" << "|"
         << setw(10) << "ID" << "|"
         << setw(10) << "Type" << "|"
         << setw(10) << "Capacity" << "|"
         << setw(10) << "Size" << "|"
         << setw(20) << "Animals" << endl;
    cout << "======================================================================================" << endl;

    for (int i = 0; i < sliced_kennels.size(); i++) {
        cout << setw(5) << i << "|";
        cout << setw(10) << sliced_kennels[i]->GetID() << "|";
        cout << setw(10) << sliced_kennels[i]->GetType() << "|";
        cout << setw(10) << sliced_kennels[i]->GetCapacity() << "|";
        cout << setw(10) << sliced_kennels[i]->GetSize() << "|";

        vector<Animal*> animals = sliced_kennels[i]->GetAnimals();
        cout << setw(20) << "[";
        for (int j = 0; j < animals.size(); j++) {
            cout << animals[j]->GetID();
            if (j < animals.size() - 1) cout << ", ";
        }
        cout << "]";
        cout << endl;
    }

    cout << "======================================================================================" << endl;
}

void PetHotel::DisplayReservations() {
    cout << endl;
    cout << "================================== Reservations ======================================" << endl;
    cout << setw(5) << "#" << "|"
         << setw(10) << "ID" << "|"
         << setw(10) << "Start" << "|"
         << setw(10) << "End" << "|"
         << setw(10) << "Together" << "|"
         << setw(20) << "Animals" << endl;
    cout << "======================================================================================" << endl;

    for (int i = 0; i < this->reservations.size(); i++) {
        cout << setw(5) << i << "|";
        cout << setw(10) << reservations[i]->GetID() << "|";
        cout << setw(10) << reservations[i]->GetStartDate() << "|";
        cout << setw(10) << reservations[i]->GetEndDate() << "|";
        cout << setw(10) << reservations[i]->GetPutTogether() << "|";

        vector<Animal*> animals = reservations[i]->GetAnimals();
        cout << setw(20) << "[";
        for (int j = 0; j < animals.size(); j++) {
            cout << animals[j]->GetID();
            if (j < animals.size() - 1) cout << ", ";
        }
        cout << "]";
        cout << endl;
    }

    cout << "======================================================================================" << endl;
}

void PetHotel::DisplayAnimals() {
    cout << endl;
    cout << "===================================== Animals ========================================" << endl;
    cout << setw(5) << "#" << "|"
         << setw(10) << "ID" << "|"
         << setw(10) << "Name" << "|"
         << setw(10) << "Birth" << "|"
         << setw(10) << "Breed" << "|"
         << setw(10) << "Care" << endl;
    cout << "======================================================================================" << endl;

    for (int i = 0; i < animals.size(); i++) {
        cout << setw(5) << i << "|";
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
    cout << setw(5) << "#" << "|"
         << setw(10) << "ID" << "|"
         << setw(10) << "Name" << "|"
         << setw(10) << "Birth" << "|"
         << setw(10) << "Breed" << "|"
         << setw(10) << "Care" << endl;
    cout << "======================================================================================" << endl;

    for (int i = 0; i < sliced_animals.size(); i++) {
        cout << setw(5) << i << "|";
        cout << setw(10) << sliced_animals[i]->GetID() << "|";
        cout << setw(10) << sliced_animals[i]->GetName() << "|";
        cout << setw(10) << sliced_animals[i]->GetBirthDate() << "|";
        cout << setw(10) << sliced_animals[i]->GetBreed() << "|";
        cout << setw(10) << sliced_animals[i]->GetCareSchedule() << "|";
        cout << endl;
    }

    cout << "======================================================================================" << endl;
}

void PetHotel::DisplayBookings() {
    cout << endl;
    cout << "===================================== Bookings ========================================" << endl;
    cout << setw(5) << "#" << "|"
         << setw(10) << "ID" << "|"
         << setw(10) << "ReservationID" << "|"
         << setw(10) << "AnimalID" << "|"
         << setw(10) << "KennelID" << "|"
         << setw(10) << "StartDate" << endl
         << setw(10) << "EndDate" << endl;
    cout << "======================================================================================" << endl;

    auto be = booking.GetBookings();
    for (int i = 0; i < be.size(); i++) {
        cout << setw(5) << i << "|";
        cout << setw(10) << be[i]->GetID() << "|";
        cout << setw(10) << be[i]->GetReservationID() << "|";
        cout << setw(10) << be[i]->GetAnimalID() << "|";
        cout << setw(10) << be[i]->GetKennelID() << "|";
        cout << setw(10) << be[i]->GetStartDate() << "|";
        cout << setw(10) << be[i]->GetEndDate() << "|";
        cout << endl;
    }

    cout << "======================================================================================" << endl;
}
