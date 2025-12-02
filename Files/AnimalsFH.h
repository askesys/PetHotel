//
// Created by Nikita Bekeruk on 25/11/2025.
//

#include <string>
#include <vector>
#include "../Animal.h"

using namespace std;

#ifndef ANIMALSFH_H
#define ANIMALSFH_H


class AnimalsFH {
private:
    string path{"Files/Animals.csv"};
    string name{"Animals DB"};

public:
    vector<Animal*> Read();
    void Write(Animal* animal);
    void WriteAll(vector<Animal*> animals);
};



#endif //ANIMALSFH_H
