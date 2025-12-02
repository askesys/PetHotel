//
// Created by Nikita Bekeruk on 24/11/2025.
//

#ifndef CAT_H
#define CAT_H
#include "../Animal.h"


class Cat: public Animal{
private:
    int weight;

public:
    Cat(const string &name, const string &birthDate, const string &breed, int weight);
    Cat(int ID, const string &name, const string &birthDate, const string &breed, int weight);

    ~Cat() override;

    int GetWeight() const;
    void SetWeight(int weight);
    void MakeSound() override;
    string GetType() override;
};



#endif //CAT_H
