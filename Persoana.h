//
// Created by Adrian on 22.05.2022.
//

#ifndef PROIECT_C___PERSOANA_H
#define PROIECT_C___PERSOANA_H
#include <string>
#include <iostream>
#include <list>
#include "Postare.h"
#include "map"
using namespace std;

class Persoana {
string nume;
string prenume;
int zi,luna,an;
int id;
public:
    friend istream & operator >> (istream &, Persoana &);

    friend ostream & operator << (ostream &, const Persoana &);
    friend void incarcare_persoana(Persoana &x,int id);
    friend void sterge_cont(int id);
};


#endif //PROIECT_C___PERSOANA_H
