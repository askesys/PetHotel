//
// Created by Nikita Bekeruk on 01/12/2025.
//

#include "BookingEntry.h"
#include "Date.h"

void BookingEntry::SetID(int id) {
    this->id = id;
}

int BookingEntry::GetID() const {
    return this->id;
}

int BookingEntry::GetAnimalID() const {
    return this->AnimalID;
}

int BookingEntry::GetKennelID() const {
    return this->KennelID;
}

string BookingEntry::GetStartDate() const {
    return this->StartDate.toString();
}

void BookingEntry::SetStartDate(Date startDate) {
    this->StartDate = startDate;
}


string BookingEntry::GetEndDate() const {
    return this->EndDate.toString();
}



