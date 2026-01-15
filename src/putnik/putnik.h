#ifndef PUTNIK_H
#define PUTNIK_H

#include <iostream>
#include <string>
#include <utility>
#include "../prevoz/prevoz.h"
#include "../ulica/ulica.h"
#include "../stanica/stanica.h"

using namespace std;

class Putnik{
private:
    static int _counter;

    int _id;
    string _ime;
    Stanica* _stanica;
    Prevoz* _vozilo;
    Ulica* _ulica;
    Ulica* _destinacija;
    bool _invalid;
    bool _penzioner;
    double _budzet;

    int _trenutnoVreme;
public:
    Putnik(string, bool,bool, double);
    ~Putnik();

    void udjiUVozilo(Prevoz*);
    void izljiIzVozila();

    void setStanica(Stanica*);
    Stanica* getStanica() const;
    void setUlica(Ulica*);
    Ulica* getUlica() const;

    void izadjiIzStanice();
    void izadjiIzUlice();

    void setDestinacija(Ulica*);
    Ulica* getDestinacija() const;

    void setVreme(int);
    int getID() const;
    double getBudzet() const;
    void skiniSaBudzeta(double);

    bool jeInvalid() const;
    bool jePenzioner() const;
    
    void uracunajPopust(double);

    void stampa() const;

    bool operator==(const Putnik& rhs) const {
        return _id == rhs.getID();  // Poredi ID-jeve
    }
};

#endif