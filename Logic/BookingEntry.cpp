//
// Created by Nikita Bekeruk on 01/12/2025.
//

#include "BookingEntry.h"
#include "Date.h"
#include "../IDManager.h"

BookingEntry::BookingEntry(int ID, int ReservationID, int AnimalID, int KennelID, Date StartDate, Date EndDate):
    ID(ID), ReservationID(ReservationID), AnimalID(AnimalID), KennelID(KennelID), StartDate(StartDate), EndDate(EndDate){}


BookingEntry::BookingEntry(int ReservationID, int AnimalID, int KennelID, Date StartDate, Date EndDate):
    ReservationID(ReservationID), AnimalID(AnimalID), KennelID(KennelID), StartDate(StartDate), EndDate(EndDate)
{
    this->ID = IDManager::NewID("Booking");
}

void BookingEntry::SetID(int id) {
    this->ID = id;
}

int BookingEntry::GetID() const {
    return this->ID;
}

int BookingEntry::GetReservationID() const {
    return this->ReservationID;
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



