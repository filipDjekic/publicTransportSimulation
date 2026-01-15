#ifndef IMAVOZACA_H
#define IMAVOZACA_H

#include "../prevoz.h"
#include "../../putnik/putnik.h"
#include "../../ulica/ulica.h"
#include <map>
#include <utility>
#include <algorithm>
#include <vector>

class ImaVozaca : public Prevoz{
private:
    int _maxSedista;
    int _sedistaZauzeto;

    int _stanica;
    vector<pair<int,bool>> putnici;
public:
    ImaVozaca(string, int, int);
    ~ImaVozaca();

    virtual void stampa() const = 0;
    
    virtual bool dodajPutnika(int) = 0;
    virtual void skloniPutnika(int) = 0;
    virtual double izracunajCenu(Ulica*, Ulica*) = 0;

    vector<pair<int,bool>> getPutnici() const;
    void setPutnici(vector<pair<int,bool>>);

    int getMaxSedista() const;
    int getSedistaZauzeto() const;

    void setSedistaZauzeto(int);

    void setStanica(int);
    void removeStanica();
};

#endif