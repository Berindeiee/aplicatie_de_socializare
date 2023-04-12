//
// Created by Adrian on 17.05.2022.
//
#include "Conectare.h"

Conectare::Conectare(string email, string parola, int id) {
    this->email = email;
    this->parola = parola;
    this->id = id;
}

void decodare(string &x) {
    for (int i = 0; i < x.length(); i++) {
        x[i] = ((unsigned char) x[i]) >> 1;  // shifting each char bits to the right
    }
}

bool Conectare::validare_conectare(int &id) {
    fstream in;
    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\email_parola.txt)", ios::in);
    Conectare a;
    while (in>>a.email>>a.parola>>a.id) {
        decodare(a.email);
        decodare(a.parola);
        if (this->email == a.email && this->parola == a.parola) {
            id = a.id;
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}
