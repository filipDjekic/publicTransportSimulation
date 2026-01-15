#include "imaVozaca.h"

ImaVozaca::ImaVozaca(string naziv, int maxBrzina, int maxSedsita) :
    Prevoz(naziv, maxBrzina), _maxSedista(maxSedsita), _sedistaZauzeto(0) {
    _stanica = 0;
}

ImaVozaca::~ImaVozaca() {}

void ImaVozaca::setStanica(int stanica) {
    _stanica = stanica;
}

void ImaVozaca::removeStanica() {
    _stanica = 0;
}

int ImaVozaca::getMaxSedista() const {
    return _maxSedista;
}

int ImaVozaca::getSedistaZauzeto() const {
    return _sedistaZauzeto;
}

void ImaVozaca::setSedistaZauzeto(int sedistaZauzeto) {
    _sedistaZauzeto = sedistaZauzeto;
}


vector<pair<int,bool>> ImaVozaca::getPutnici() const {
    return putnici;
}   
void ImaVozaca::setPutnici(vector<pair<int,bool>> putnici) {
    this->putnici = putnici;
}   