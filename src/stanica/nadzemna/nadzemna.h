#ifndef NADZEMNA_H
#define NADZEMNA_H

#include "../stanica.h"
#include "../../enum/tipoviUlaza.h"
#include <vector>

class Nadzemna : public Stanica{
public:
    Nadzemna(string, int);
    ~Nadzemna();

    virtual void stampa() const override;

    virtual void dodajPutnika(int) override;
};

#endif