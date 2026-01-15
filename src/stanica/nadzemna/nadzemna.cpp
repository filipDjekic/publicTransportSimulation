#include "nadzemna.h"

Nadzemna::Nadzemna(string naziv, int ulica) : Stanica(naziv, ulica){}

Nadzemna::~Nadzemna(){}

void Nadzemna::stampa() const{
    cout << "Stanica: " << Stanica::getIme() << endl;
}

void Nadzemna::dodajPutnika(int putnik){
    vector<int> redPutnika = getRedPutnika();
    redPutnika.push_back(putnik);
    setRedPutnika(redPutnika);
}