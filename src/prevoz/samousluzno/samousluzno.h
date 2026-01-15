#ifndef SAMOUSLUZNO_H
#define SAMOUSLUZNO_H

#include "../prevoz.h"
#include "../../enum/tipoviSamousluzno.h"
#include "../../ulica/ulica.h"
#include "../../putnik/putnik.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Samousluzno : public Prevoz{
private:
    TipoviSamousluzno _tip;

    int _korisnik;

    double kapacitetBaterije;
    double potrosnjaPoKm;
    int _satnica;
    double _razdaljina;

    pair<Ulica*, Ulica*> _trenutnaRuta;
    vector<int> _ruta;
    int _duzinaPuta;
public:
    Samousluzno(string, int, int);
    Samousluzno(string, int, int, double, double);
    ~Samousluzno();

    double izracunajSatnicu(double);
    virtual bool dodajPutnika(int) override;
    virtual void skloniPutnika(int) override;
    virtual double izracunajCenu(Ulica*, Ulica*) override;

    TipoviSamousluzno getTip() const;

    vector<int> nadjiNajkraciPut(Ulica*, Ulica*);
    void zapocniKretanje(vector<int>, Ulica* , Ulica*, vector<Putnik*>&,vector<Ulica*>&);

    vector<int> getRuta() const;
    virtual void stampa() const override;
};

#endif