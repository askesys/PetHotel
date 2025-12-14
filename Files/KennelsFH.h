//
// Created by Nikita Bekeruk on 25/11/2025.
//

#ifndef KENNELSFH_H
#define KENNELSFH_H

#include "../Kennel.h"
#include <map>
#include <string>
#include <vector>


class KennelsFH {
private:
    string path{"Files/Kennels.csv"};
    string name{"Kennels DB"};

public:
    vector<Kennel*> Read(map<int, Animal*> *animalsMap);
    void Write(Kennel* kennel);
    void WriteAll(vector<Kennel*> kennels);
    //void Delete(Kennel* kennel);
    //void Update(Kennel* kennel);
};



#endif //KENNELSFH_H
