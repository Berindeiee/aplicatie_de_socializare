#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <stdio.h>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include<sstream>

#include <regex>
#include <stdlib.h>
#include "Conectare.h"
#include "Persoana.h"
using namespace std;
int id_postare;

void codare(string &x) {
    for (int i = 0; i < x.length(); i++) {
        x[i] = ((unsigned char) x[i]) << 1;  // shifting each char bits to the left
    }
}

void scrie_persoana(int zi, int luna, int an, string nume, string prenume, string email, string parola, int id)
{
    fstream out;
    out.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\Persoane.txt)", ios::app);
    out<<nume<<" "<<prenume<<" "<<id<<" "<<zi<<" "<<luna<<" "<<an<<" "<<endl;
    out.close();


    out.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\email_parola.txt)", ios::app);
    codare(email);codare(parola);
    out<<email<<" "<<parola<<" "<<id<<endl;
    out.close();
}
void meniu();
void citire_persoana()
{
    fstream in;
    Persoana A;
    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\Persoane.txt)", ios::in);
    in>>A;
    in.close();
}

bool date_validator(int zi,int luna,int an){
    if(1900 <= an && an <= 2004)
    {
        if((luna == 1 || luna == 3 || luna == 5 || luna == 7 || luna == 8 || luna == 10 || luna == 12) && zi > 0 && zi <= 31)
            return true;
        else
        if(luna == 4 || luna == 6 || luna == 9 || luna == 11 && zi > 0 && zi <= 30)
            return true;
        else
        if(luna == 2)
        {
            if((an % 400 == 0 || (an % 100 != 0 && an % 4 == 0)) && zi > 0 && zi <= 29)
                return true;
            else if(zi > 0 && zi <= 28)
                return true;
            else {
                cout << "Data invalida!\n";
                return false;
            }
        }
        else {
            cout << "Data invalida!\n";
            return false;
        }
    }
    else {
        if(((luna == 1 || luna == 3 || luna == 5 || luna == 7 || luna == 8 || luna == 10 || luna == 12) && zi > 0 && zi <= 31)||(luna == 4 || luna == 6 || luna == 9 || luna == 11 && zi > 0 && zi <= 30)||((luna == 2))&&(((an % 400 == 0 || (an % 100 != 0 && an % 4 == 0)) && zi > 0 && zi <= 29)||(zi > 0 && zi <= 28))) cout << "Trebuie sa aveti 18 ani pentru a continua!\n";
        else cout << "Data invalida!\n";
        return false;

    }
}
void ddecodare(string &x) {
    for (int i = 0; i < x.length(); i++) {
        x[i] = ((unsigned char) x[i]) >> 1;  // shifting each char bits to the right
    }
}
bool verificare_email(const string& email) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@e-uvt.ro");

    if (regex_match(email, pattern))
    {
        fstream in;
        string imail,parola,id;
        in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\email_parola.txt)", ios::in);

        while (in>>imail>>parola>>id) {
            ddecodare(imail);
            if(imail==email) {
                cout<<"Acest email exista deja inregistrat\n";
                return false;
            }
        }
        in.close();
        return true;
    }
    else {
        cout<<"Email invalid!\n";
        return false;
    }
}

bool verificare_int(string str){
    for(int i=0;i<str.size();i++)
        if(isdigit(str[i])==0) return false;
    return true;
}

bool verificare_string(string str){
    for(int i=0;i<str.size();i++)
        if(isalpha(str[i])==0) return false;
    return true;
}
void meniu_secundar(int);
void login(){
    string email,pass;
    int alegere;
    int id;
    while(1){
        cout << "Email:" << endl;
        cin >> email;
        cout << "Parola:" << endl;
        cin >> pass;
        Conectare a(email,pass);
        id=-1;
        if(a.validare_conectare(id)) {
            //incarcare(id)
            break;
        }
        else{
            cout<<"Email-ul sau parola este invalida!"<<endl;
            cout<<"Pentru a continua cu autentificarea apasati tasta 1"<<endl;
            cout<<"Pentru a reveni la meniul principal apasati tasta 2"<<endl;
            cin>>alegere;
            switch(alegere){
                case 1:
                    login();
                case 2:
                    meniu();
            }
        }
    }
    cout<<"Autentificare reusita!"<<endl;
    meniu_secundar(id);
    //

}

vector<string> split(const string& str) {
    size_t start, end = 0;
    vector<string> parts;
    const string& delim = " /.";
    while (end < str.size()) {
        start = end;
        while (start < str.size() && (delim.find(str[start]) != string::npos)) {
            start++;
        }
        end = start;
        while (end < str.size() && (delim.find(str[end]) == string::npos)) {
            end++;
        }
        if (end-start != 0) {
            parts.push_back(string(str, start, end-start));
        }
    }
    return parts;
}


void inregistrare(){
    string nume,prenume,email,parola,parola_verif,day="a",month="b",year="c";
    int zi,luna,an=2000,ok=0;
    do {
        cout<<"Nume:";
        cin >> nume;
    }while(!verificare_string(nume));
    do {
        cout<<"Prenume:";
        cin >> prenume;
    }while(!verificare_string(prenume));
    do{
        cout<<"Data nasterii:";
        string data;
        if(!ok) {
            cin.get();
            ok = 1;
        };
        std::getline(std::cin,data);
        if((data[2]==' ' && data[5]==' ')||(data[2]=='/' && data[5]=='/')||(data[2]=='.' && data[5]=='.')){
            day = split(data).front();
            month = split(data).at(1);
            year = split(data).back();
        }
        if(verificare_int(day)&&verificare_int(month)&&verificare_int(year)){
            zi = stoi(day);
            luna = stoi(month);
            an = stoi(year);
        }
    } while(!date_validator(zi,luna,an));

    do {
        cout<<"Email:";
        cin >> email;
        if(email=="0")
        {
            meniu();
            break;
        }
    }while(!verificare_email(email));
    cout<<"Parola:";
    cin>>parola;
    do {
        cout << "Confirmare parola:";
        cin >> parola_verif;
    }while(parola!=parola_verif);
    fstream in,out;
    int id;
    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\id.txt)", ios::in);
    in>>id;
    in>>id_postare;
    id++;
    in.close();
    scrie_persoana(zi,luna,an,nume,prenume,email,parola,id);

    remove(R"(C:\Users\Adrian\CLionProjects\proiect c++\id.txt)");
    out.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\id.txt)", ios::out);
    out<<id<<" ";
    out<<id_postare;
    out.close();

    ofstream writer;
    stringstream ss;
    ss<<"C:\\Users\\Adrian\\CLionProjects\\proiect c++\\"<<id<<".txt";
    writer.open(ss.str());
    writer.close();

    cout<<"Cont Inregistrat!\n";
    meniu();
}

void meniu(){
    string alegere;
    cout<<"                  Bine ati venit la Backbook\n\n\n";
    cout<<"Pentru Login apasati tasta 1\n";
    cout<<"Nu aveti cont? Pentru a va inregistra apasati tasta 2\n";
    cout<<"Pentru a iesi apasati tasta 0\n";
    cin>>alegere;
    if(verificare_int(alegere)==0) meniu();
    else{
        int a=stoi(alegere);
        switch (a){
            case 1:
                login();
                break;
            case 2:
                inregistrare();
                break;
            case 0:
                exit(0);
            default:
                meniu();
        }
    }
}
void incarcare_persoana(Persoana &x,int id)
{
    fstream in;
    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\Persoane.txt)", ios::in);
    string a,nume,prenume;
    int zi,luna,an;
    while (in>>nume>>prenume>>a>>zi>>luna>>an) {
        if(stoi(a)==id)
        {
            x.nume=nume;
            x.prenume=prenume;
            x.id=id;
            x.zi=zi;
            x.luna=luna;
            x.an=an;
        }
    }
    in.close();
}
void creare_postare(int id)
{
    Persoana Ana;
    incarcare_persoana(Ana,id);
Postare P;
string alegere;

cin>>P;
    cout<<"Doriti sa publicati postarea creata?"<<endl;
    cout<<"DA tasta 1(reveniti la pagina principala)"<<endl;
    cout<<"NU tasta 2(scrieti alta postare)"<<endl;
    cout<<"Mergeti la pagina principala \n";

    cin>>alegere;

    if(verificare_int(alegere)==0)
    {
        cout<<"Input gresit";
        creare_postare(id);
    }
int a=stoi(alegere);
    switch(a){
        case 1:
        {

            fstream out,in;
            stringstream ss;
            int idd;
            in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\id.txt)", ios::in);
            in>>idd>>id_postare;
            in.close();
            ss<<"C:\\Users\\Adrian\\CLionProjects\\proiect c++\\"<<id<<".txt";
            out.open(ss.str(),ios::app);
            id_postare++;

            out<<P.nume<<endl<<P.descriere<<endl<<P.data_ora<<id_postare<<endl;
out.close();

            remove(R"(C:\Users\Adrian\CLionProjects\proiect c++\id.txt)");
            out.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\id.txt)", ios::out);

            out<<idd<<" ";
            cout<<id_postare;
            out<<id_postare;
            out.close();

            out<<id_postare<<endl<<P.descriere<<endl<<P.data_ora<<endl;
            out.close();
            meniu_secundar(id);
            break;
        }
        case 2:
            creare_postare(id);
            break;
        default:
        {
            cout<<"Input gresit";
            creare_postare(id);
            break;
        }
    }
}
void vizualizare_postari(int id)
{
    fstream in,jn;
    string s;
    fstream out;
    string a,nume,prenume,data,descriere;
    int zi,luna,an;
    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\Persoane.txt)", ios::in);


    while(in>>nume>>prenume>>a>>zi>>luna>>an)
    {
        stringstream ss;
        fstream inn;
        ss<<"C:\\Users\\Adrian\\CLionProjects\\proiect c++\\"<<a<<".txt";
        inn.open(ss.str(),ios::in);
       //afisare numele persoanei ce detine postarea/postarile
       if(inn>>a) {
           inn.close();
           inn.open(ss.str(),ios::in);
           cout << "------------------------------------------------\n";
           cout << nume << " " << prenume << endl;

           while (getline(inn, nume)) {
               getline(inn, descriere);
               getline(inn, data);
               getline(inn, a);
               cout << "         " << nume << endl;
               cout << descriere << endl;
               cout << data << endl;
               cout << "id postare:" << a << endl;
               cout << endl;
           }
           cout << "------------------------------------------------\n";
           inn.close();
       }
       else
       {
           cout << nume << " " << prenume <<" Nu are postari"<< endl;
           inn.close();
       }
    }
    in.close();
    cout<<"\nApasati orice tasta pentru a reveni la pagina principala\n";
    cin>>s;
    meniu_secundar(id);
}
void sterge_postare(int id){
    fstream in,temp;
    stringstream ss,s;
string n;
int k=1;
    ss<<"C:\\Users\\Adrian\\CLionProjects\\proiect c++\\"<<id<<".txt";
    in.open(ss.str(),ios::in);
    s<<"C:\\Users\\Adrian\\CLionProjects\\proiect c++\\temp.txt";
    temp.open(s.str(),ios::app);
    string a,nume,prenume,data,descriere;
    cout<<"Ce postare doriti sa stergeti?\n";
    cin>>n;

    while (getline(in, nume)) {
        getline(in, descriere);
        getline(in, data);
        getline(in, a);
        if(a!=n) {
            temp << nume << endl;
            temp << descriere << endl;
            temp << data << endl;
            temp << a << endl;
        }
        else
            k=0;
    }
    in.close();
    temp.close();
    char t[2000];
    string m=ss.str();
    strcpy(t, m.c_str());

    remove(t);
    rename("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\temp.txt",t);
    if(k==1)
    {cout<<"Postarea nu exista!!\n";
        meniu_secundar(id);}
cout<<"Postare stearsa, apasati orice tasta sa reveniti la meniul principal\n";
    cin>>a;
    meniu_secundar(id);
}

void schimba_email(int id)
{
    string email;
    do {
        cout<<"Introduceti noul email:";
        cin >> email;
    }while(!verificare_email(email));
    fstream in,temp;
    Conectare a;
    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\email_parola.txt)",ios::in);
    temp.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\temp.txt)", ios::app);
    while (in>>a.email>>a.parola>>a.id) {
        if(a.id==id) {
            codare(email);
            temp<<email<<" "<<a.parola<<" "<<id<<endl;
        }
        else
        temp<<a.email<<" "<<a.parola<<" "<<a.id<<endl;
    }
    in.close();
    temp.close();
    remove("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\email_parola.txt");
    rename("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\temp.txt","C:\\Users\\Adrian\\CLionProjects\\proiect c++\\email_parola.txt");
    meniu_secundar(id);
}
void schimba_parola(int id)
{
    string parola, parola_verif;
    cout<<"Parola:";
    cin>>parola;
    do {
        cout << "Confirmare parola:";
        cin >> parola_verif;
        if(parola_verif=="0")
            meniu_secundar(id);
    }while(parola!=parola_verif);


    fstream in,temp;
    Conectare a;
    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\email_parola.txt)",ios::in);
    temp.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\temp.txt)", ios::app);
    while (in>>a.email>>a.parola>>a.id) {
        if(a.id==id) {
            codare(parola);
            temp<<a.email<<" "<<parola<<" "<<id<<endl;
        }
        else
        temp<<a.email<<" "<<a.parola<<" "<<a.id<<endl;
    }
    in.close();
    temp.close();
    remove("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\email_parola.txt");
    rename("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\temp.txt","C:\\Users\\Adrian\\CLionProjects\\proiect c++\\email_parola.txt");
    meniu_secundar(id);
}
void sterge_cont(int id)
{
    string alegere;
    cout<<"Sunteti sigur ca doriti sa stergeti contul?\n tsatati DA sau apasati orce alta tasta pentru a refuza\n";
    cin>>alegere;
    if(alegere!="DA")
    {
        meniu_secundar(id);
    }
    else
    {
        stringstream ss;
        ss<<"C:\\Users\\Adrian\\CLionProjects\\proiect c++\\"<<id<<".txt";
        char t[2000];
        string m=ss.str();
        strcpy(t, m.c_str());
        remove(t);
        Persoana a;
        fstream in, temp;
        in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\Persoane.txt)",ios::in);
        temp.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\temp.txt)", ios::app);
        while (in>>a.nume>>a.prenume>>a.id>>a.zi>>a.luna>>a.an) {
            if(a.id!=id) {
                temp << a.nume << " " << a.prenume<< " " << a.id <<" "<<a.zi<<" "<<a.luna<<" "<<a.an<< endl;
            }
        }
        in.close();
        temp.close();
        remove("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\Persoane.txt");
        rename("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\temp.txt","C:\\Users\\Adrian\\CLionProjects\\proiect c++\\Persoane.txt");

        Conectare b;
        in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\email_parola.txt)",ios::in);
        temp.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\temp.txt)", ios::app);
        while (in>>b.email>>b.parola>>b.id) {
            if(b.id!=id) {
                temp<<b.email<<" "<<b.parola<<" "<<b.id<<endl;
            }
        }
        in.close();
        temp.close();
        remove("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\email_parola.txt");
        rename("C:\\Users\\Adrian\\CLionProjects\\proiect c++\\temp.txt","C:\\Users\\Adrian\\CLionProjects\\proiect c++\\email_parola.txt");


        cout<<"\nCont sters!!\n";
        meniu();
    }


}
void setari_cont(int id){
    string alegere;
    Persoana P;
    incarcare_persoana(P,id);
    cout<<"                  Setarile contului\n\n\n";
    cout<<P<<endl;
    cout<<"Pentru a schimba emailul apasati tasta 1\n";
    cout<<"Pentru a schimba parola apasati tasta 2\n";
    cout<<"Pentru a sterge contul apasati tasta  3\n";
    cout<<"Pentru a reveni la pagina principala apasti tasta 0\n";
    cin>>alegere;
    if(verificare_int(alegere)==0) setari_cont(id);
    else{
        int a=stoi(alegere);
        switch (a){
            case 1:
                schimba_email(id);
                break;
            case 2:
                schimba_parola(id);
                break;
            case 3:
                sterge_cont(id);
                break;
            case 0:
                meniu_secundar(id);
                break;
            default:
                setari_cont(id);
                break;
        }
    }
}

void meniu_secundar(int id)
{

    string alegere;
    cout<<"                  Bine ati venit pe pagina principala a Backbook\n\n\n";
    cout<<"Pentru a vedea toate postarile apasati 1\n";
    cout<<"Pentru a crea o postare apasati tasta 2\n";
    cout<<"Pentru a sterge o postare apasati tasta 3\n";
    cout<<"Pentru setarile contului apasti tasta 4\n";
    cout<<"Pentru delogare apasati tasta 0\n";
    cin>>alegere;
    if(verificare_int(alegere)==0) meniu_secundar(id);
    else{
        int a=stoi(alegere);
        switch (a){
            case 1:
                vizualizare_postari(id);
                break;
            case 2:
                creare_postare(id);
                break;
            case 3:
                sterge_postare(id);
                break;
            case 4:
                setari_cont(id);
            break;
            case 0:
                meniu();
                break;
            default:
                meniu_secundar(id);
        }
    }
}



int main() {
    fstream in;

    in.open(R"(C:\Users\Adrian\CLionProjects\proiect c++\id.txt)", ios::in);
    in>>id_postare;
    in>>id_postare;
    meniu();
    return 0;
}
