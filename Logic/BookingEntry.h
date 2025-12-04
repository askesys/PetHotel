//
// Created by Nikita Bekeruk on 01/12/2025.
//

#ifndef BOOKINGENTRY_H
#define BOOKINGENTRY_H
#include "Date.h"
#include <string>

using namespace std;


class BookingEntry {
private:
    int id;
    int AnimalID;
    int KennelID;
    Date StartDate;
    Date EndDate;

public:
    BookingEntry(int AnimalID, int KennelID, Date StartDate, Date EndDate):
    AnimalID(AnimalID), KennelID(KennelID), StartDate(StartDate), EndDate(EndDate) {}
    void SetID(int id);
    int GetID() const;
    int GetAnimalID() const;
    int GetKennelID() const;
    string GetStartDate() const;
    void SetStartDate(Date startDate);
    string GetEndDate() const;
};



#endif //BOOKINGENTRY_H
