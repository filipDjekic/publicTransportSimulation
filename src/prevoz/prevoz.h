#ifndef PREVOZ_H
#define PREVOZ_H

#include <iostream>
#include <string.h>
#include <algorithm>
#include "../ulica/ulica.h"
#include <unistd.h>

using namespace std;

class Prevoz{
private:
    static int _counter;

    int _id;
    string _naziv;
    int _maxBrzina;
    int _trenutnaBrzina;
    Ulica* _ulica;
public:
    Prevoz(string, int);
    ~Prevoz();
    
    int getID() const;
    string getNaziv() const;
    int getMaxBrzina() const;

    virtual bool dodajPutnika(int) = 0;
    virtual void skloniPutnika(int) = 0;
    virtual double izracunajCenu(Ulica*,Ulica*) = 0;

    void setUlica(Ulica* ulica);
    Ulica* getUlica() const;
    
    virtual void stampa() const = 0;
};

#endif