//
// Created by Nikita Bekeruk on 06/11/2025.
//

#ifndef KENNEL_H
#define KENNEL_H

#include<string>
#include<vector>

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
    static int STANDART_CAPACITY;

    Kennel(const string& size, int capacity);
    Kennel(int ID, const string& size, int capacity);
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

    static int KennelSizeToSpace(const string& size);
    int GetFullSpace() const;
};



#endif //KENNEL_H
