#ifndef VELIKO_H
#define VELIKO_H

#include "../imaVozaca.h"
#include "../../../enum/tipoviVeliko.h"
#include "../../../ruta/ruta.h"
#include "../../../putnik/putnik.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <iostream>
#include <unistd.h> 

class Veliko : public ImaVozaca{
private:
    TipoviVeliko _tip;
    int maxStoje;
    int zauzetoStoje;

    Ruta* _ruta;
    int _stanica;

    vector<pair<int,bool>> putnici;
public:
    Veliko(string, int, int,Ulica*, TipoviVeliko, int, Ruta*); // tip, maxstoje, ruta
    ~Veliko();

    virtual bool dodajPutnika(int) override;
    virtual void skloniPutnika(int) override;
    virtual double izracunajCenu(Ulica*, Ulica*) override;
    void promeniStanicu(int);

    Ruta* getRuta() const;

    virtual void stampa() const override;

    void zapocniKretanje(vector<int>, Ulica* , Ulica*, vector<Putnik*>&, vector<Ulica*>&);
};
#endif