//
// Created by Adrian on 22.05.2022.
//

#ifndef PROIECT_C___POSTARE_H
#define PROIECT_C___POSTARE_H
#include <string>
#include <iostream>
#include <list>
#include <ctime>
#include "Persoana.h"
using namespace std;
class Postare {
string nume;
string descriere;
string data_ora;

public:
    Postare(){};
    friend istream & operator >> (istream &, Postare &);
    friend ostream & operator << (ostream &, Postare &);
    friend void creare_postare(int id);
};


#endif //PROIECT_C___POSTARE_H
