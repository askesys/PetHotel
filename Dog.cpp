//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Dog.h"

#include <iostream>
#include <ostream>

int Dog::GetWeight() const {
    return this->weight;
}

void Dog::SetWeight(int weight) {
    this->weight = weight;
}

void Dog::MakeSound(){
    cout << "Dog makes *bark *bark!" << endl;
}

string Dog::GetType(){
    return "Dog";
}
