//
// Created by Nikita Bekeruk on 25/11/2025.
//

#ifndef ANIMALSFH_H
#define ANIMALSFH_H

#include <string>
#include <vector>
#include "../Animal.h"

using namespace std;

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
