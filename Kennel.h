//
// Created by Nikita Bekeruk on 06/11/2025.
//

#ifndef KENNEL_H
#define KENNEL_H

#include<string>
#include<vector>
#include <__random/uniform_int_distribution.h>

#include "Animal.h"
using namespace std;

class Kennel {
private:
    int ID;
    string size;
    int capacity;
    string type;
    vector<Animal*> animals;
    bool isEmpty;
public:
    Kennel(int ID, const string& size, int capacity, bool isEmpty);
    Kennel(int ID, const string& size, int capacity, const string& type, bool isEmpty, vector<Animal*> animals);
    ~Kennel();

    string GetSize() const;
    void SetSize(const string& size);
    int GetCapacity() const;
    void SetCapacity(int capacity);
    string GetType() const;
    void SetType(const string& type);
    vector<Animal*> GetAnimals() const;
    void SetAnimals(vector<Animal*> animals);
    void AddAnimal(Animal* animal);

    bool GetIsEmpty();
    void SetIsEmpty(bool isEmpty);
    int GetID() const;
    void SetID(int ID);
    bool CheckAvailability();
    int GetTakenSpots() const;
    int GetFreeSpots() const;
};



#endif //KENNEL_H
