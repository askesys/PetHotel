//
// Created by Nikita Bekeruk on 06/11/2025.
//

#ifndef DOG_H
#define DOG_H
#include "Animal.h"
#include <stdexcept>


class Dog: public Animal {
private:
    int weight = -1;

public:
    Dog(int ID, const string &name, const string &birthDate, const string &breed, const string &careSchedule, int weight):
        Animal(ID, name, birthDate, breed, careSchedule), weight(weight) {}

    int GetWeight() const;
    void SetWeight(int weight);
    void MakeSound() override;
    string GetType() override;
};



#endif //DOG_H
