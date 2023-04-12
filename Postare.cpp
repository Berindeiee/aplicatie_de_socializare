//
// Created by Adrian on 22.05.2022.
//
#include "Postare.h"
#include "Persoana.h"

 istream & operator >> (istream &in, Postare &x){
     time_t now = time(0);
     string dt = ctime(&now);
     cout<<"\nIntroduceti numele postarii:";
     in>>x.nume;
cin.get();
     cout<<"\nIntroduceti descrierea postarii:";
     getline(in,x.descriere);
     x.data_ora=dt;
     return in;
}
ostream & operator << (ostream &out, Postare &x) {
    out<<"         "<<x.nume<<endl;
    out<<x.descriere<<endl;
    out<<x.data_ora<<endl;
}
