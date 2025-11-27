//
// Created by Nikita Bekeruk on 25/11/2025.
//

#include "../Kennel.h"
#include <map>
#include <string>
#include <vector>

#ifndef KENNELSFH_H
#define KENNELSFH_H




class KennelsFH {
private:
    string path{"Files/Kennels.csv"};
    string name{"Kennels DB"};

public:
    vector<Kennel*> Read(map<int, Animal*> *animalsMap);
    void Write(Kennel* kennel);
};



#endif //KENNELSFH_H
