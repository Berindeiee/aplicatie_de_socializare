//
// Created by Adrian on 17.05.2022.
//
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <bitset>
#include <regex>
#include <fstream>

using namespace std;

#ifndef PROIECT_C___CONECTARE_H
#define PROIECT_C___CONECTARE_H

class Conectare {
    string email;
    string parola;
    int id;
public:
    Conectare(string email = "", string parola = "", int id = 0);

friend void schimba_email(int);
friend void schimba_parola(int);
friend void sterge_cont(int id);
    bool validare_conectare(int &id);


};



#endif //PROIECT_C___CONECTARE_H
