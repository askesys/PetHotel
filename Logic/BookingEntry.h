//
// Created by Nikita Bekeruk on 01/12/2025.
//

#ifndef BOOKINGENTRY_H
#define BOOKINGENTRY_H
#include "Date.h"


class BookingEntry {
    int AnimalID;
    int KennelID;
    Date StartDate;
    Date EndDate;

    BookingEntry(int AnimalID, int KennelID, Date StartDate, Date EndDate):
    AnimalID(AnimalID), KennelID(KennelID), StartDate(StartDate), EndDate(EndDate) {}
};



#endif //BOOKINGENTRY_H
