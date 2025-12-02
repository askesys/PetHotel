//
// Created by Nikita Bekeruk on 27/11/2025.
//

#ifndef ANIMALFILTER_H
#define ANIMALFILTER_H
#include <map>
#include <string>
#include <vector>
#include "../Animal.h"

using namespace std;

enum AnimalKey {
    ID,
    Type,
    Name,
    BirthDate,
    Breed,
    CareSchedule
};

class AnimalFilter {
private:
    map<AnimalKey, string> keyMap;

public:
    AnimalFilter(map<AnimalKey, string> keyMap);
    void Filter(vector<Animal*>& animals);
};



#endif //ANIMALFILTER_H
