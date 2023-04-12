//
// Created by Adrian on 22.05.2022.
//

#include "Persoana.h"
#include <string>
ostream & operator << (ostream &st, const Persoana &x)
{
   st<<x.nume<<" "<<x.prenume<<" "<<x.id;
   return st;
}

istream & operator >>(istream &st, Persoana &x)
{
    st>>x.nume>>x.prenume>>x.id>>x.zi>>x.luna>>x.an;
    return st;
}