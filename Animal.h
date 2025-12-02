//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include<string>

#ifndef ANIMAL_H
#define ANIMAL_H

using namespace std;


class Animal {
private:
    string name;
    string birthDate;
    string breed;
    string careSchedule;

protected:
    int ID;

public:
    Animal(const string &name, const string &birthDate, const string &breed);

    virtual ~Animal();

    string GetName() const;
    void SetName(const string&);
    string GetBirthDate() const;
    void SetBirthDate(const string&);
    string GetBreed() const;
    void SetBreed(const string&);
    int GetID() const;
    void SetID(int);
    virtual void MakeSound() = 0;
    virtual string GetType() = 0;
    int CalculateAge() const;
    string GetCareSchedule() const;
    void SetCareSchedule(const string&);

    static string CarvinoresWeightToSize(int weight);
    static string RecommendCareSchedule(const string& type, int weight);
    static string RecommendCareSchedule(const string& type, const string& rodentType);
};



#endif //ANIMAL_H
