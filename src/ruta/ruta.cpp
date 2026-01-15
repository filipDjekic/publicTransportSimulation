#include "ruta.h"

int Ruta::_counter = 1;

Ruta::Ruta(string naziv, double cenaKarte) :
    _naziv(naziv), _cenaKarte(cenaKarte) {
        _id = _counter++;
    }

Ruta::~Ruta() {}

void Ruta::setRuta(vector<int> ruta, int prevoz) {
    _ruta = ruta;
    _prevoz = prevoz;
}

void Ruta::setPrevoz(int prevoz) {
    _prevoz = prevoz;
}

double Ruta::cena(int pocetna, int krajnja) {
    float cena = 0.0;
    int brojStanica = 0;
    bool brojim = false;

    for(const auto& par : _ruta){
        if(par == pocetna){
            brojim = true;
        }

        if(brojim){
            brojStanica++;
        }

        if(par == krajnja){
            break;
        }
    }
    brojStanica--;
    return brojStanica * _cenaKarte;
}

int Ruta::getID() const {
    return _id;
}

void Ruta::stampa() const {
    cout << "Naziv: " << _naziv << endl;
    cout << "Cena karte: " << _cenaKarte << endl;
}

vector<int> Ruta::getRuta(){
    return _ruta;
}

bool Ruta::nalaziSeNaRuti(int ulica1, int ulica2) {
    bool foundStanica1 = false;
    bool foundStanica2 = false;

    for (int stanica : _ruta) {
        if (stanica == ulica1) {
            foundStanica1 = true;
        }
        if (stanica == ulica2) {
            foundStanica2 = true;
        }
        if (foundStanica1 && foundStanica2) {
            return true;
        }
    }

    return false;
}
