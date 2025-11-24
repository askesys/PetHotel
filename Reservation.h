//
// Created by Nikita Bekeruk on 06/11/2025.
//

#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include<string>
#include<vector>
#include"Animal.h"

using namespace std;

class Reservation {
private:
    int ID;
    string startDate;
    string endDate;
    vector<Animal*> animals;
    bool putTogether;
    bool IsDurationValid() const;
public:
    Reservation(int ID, const string& startDate, const string& endDate, const vector<Animal*>& animals, bool putTogether);
    ~Reservation();

    string GetStartDate() const;
    void SetStartDate(const string&);
    string GetEndDate() const;
    void SetEndDate(const string&);
    vector<Animal*> GetAnimals() const;
    void SetAnimals(vector<Animal*>);
    bool GetPutTogether() const;
    void SetPutTogether(bool);
    int GetID() const;
    void SetID(int);
};



#endif //RESERVATIONS_H
