//
// Created by Nikita Bekeruk on 25/11/2025.
//


using namespace std;

#ifndef RESERVATIONSFH_H
#define RESERVATIONSFH_H

#include <map>
#include <string>
#include <vector>
#include "../Reservation.h"


class ReservationsFH {
private:
    string path{"Files/Reservations.csv"};
    string name{"Reservations DB"};

public:
    vector<Reservation*> Read(map<int, Animal*> *animalsMap);
    void Write(Reservation* reservation);
    void WriteAll(vector<Reservation*> reservations);
    void Delete(Reservation* reservation);
};



#endif //RESERVATIONSFH_H
