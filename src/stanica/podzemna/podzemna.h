#ifndef PODZEMNA_H
#define PODZEMNA_H

#include "../stanica.h"
#include "../../enum/tipoviUlaza.h"
#include <vector>

class Podzemna : public Stanica{
private:
    double _cenaUlaza;
    vector<TipoviUlaza> _tipoviUlaza;
public:
    Podzemna(string, int, double, vector<TipoviUlaza>);
    ~Podzemna();

    void dodajTipUlaza(TipoviUlaza);
    bool imaTipUlaza(TipoviUlaza);

    virtual void stampa() const override;

    virtual void dodajPutnika(int) override;
};

#endif