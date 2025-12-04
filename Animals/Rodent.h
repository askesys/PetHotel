//
// Created by Nikita Bekeruk on 24/11/2025.
//

#ifndef RODENT_H
#define RODENT_H
#include <string>
#include "../Animal.h"


class Rodent: public Animal {
private:
    string rodentType;

public:
    Rodent(const string &name, const string &birthDate, const string &breed,  const string& rodentType);
    Rodent(int ID, const string &name, const string &birthDate, const string &breed, const string& rodentType);

    ~Rodent() override;

    string GetRodentType() const;
    void SetRodentType(const string &rodentType);
    void MakeSound() override;
    string GetType() override;
    int GetSpace() const override;
};



#endif //RODENT_H
