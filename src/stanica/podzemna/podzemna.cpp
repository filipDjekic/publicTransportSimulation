#include "podzemna.h"


Podzemna::Podzemna(string naziv, int ulica, double cenaUlaza, vector<TipoviUlaza> tipoviUlaza) :
    Stanica(naziv, ulica), _cenaUlaza(cenaUlaza), _tipoviUlaza(tipoviUlaza){}

Podzemna::~Podzemna(){}

void Podzemna::dodajTipUlaza(TipoviUlaza tip){
    _tipoviUlaza.push_back(tip);
}

bool Podzemna::imaTipUlaza(TipoviUlaza tip){
    for (const auto& t : _tipoviUlaza) {
        if (t == tip) {
            return true;
        }
    }
    return false;
}

void Podzemna::stampa() const{
    cout << "Stanica: " << Stanica::getIme() << endl;
}

void Podzemna::dodajPutnika(int putnik){
    vector<int> redPutnika = getRedPutnika();
    redPutnika.push_back(putnik);
    setRedPutnika(redPutnika);
}
