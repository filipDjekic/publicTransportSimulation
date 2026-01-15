#include "prevoz.h"

int Prevoz::_counter = 1;

Prevoz::Prevoz(string naziv, int maxBrzina) :
    _naziv(naziv), _maxBrzina(maxBrzina) {
        _id = _counter++;
    }

Prevoz::~Prevoz() {}

int Prevoz::getID() const {
    return _id;
}

string Prevoz::getNaziv() const {
    return _naziv;
}

int Prevoz::getMaxBrzina() const {
    return _maxBrzina;
}

void Prevoz::setUlica(Ulica* ulica) {
    _ulica = ulica;
}

Ulica* Prevoz::getUlica() const {
    return _ulica;
}
