#include "putnik.h"

int Putnik::_counter = 1;

Putnik::Putnik(string ime, bool invalid, bool penzioner, double budzet) :   
    _id(_counter++), _ime(ime), _penzioner(penzioner), _invalid(invalid), _budzet(budzet) {
        _stanica = nullptr;
        _vozilo = nullptr;
        _ulica = nullptr;
        _trenutnoVreme = 0;
}


Putnik::~Putnik() {}

int Putnik::getID() const{
    return _id;
}

double Putnik::getBudzet() const{
    return _budzet;
}

void Putnik::setVreme(int vreme){
    _trenutnoVreme = vreme;
}

void Putnik::stampa() const{
    cout << "-----------------------------" << endl;
    cout << "ID: " << _id << endl;
    cout << "Ime: " << _ime << endl;
    cout << "Budzet: " << _budzet << endl;
    cout << "Ulica: " << _ulica->getNaziv()<<endl;
    cout << "-----------------------------" << endl;
}

Stanica* Putnik::getStanica() const{
    return _stanica;
}

Ulica* Putnik::getUlica() const{
    return _ulica;
}

void Putnik::udjiUVozilo(Prevoz* vozilo){
    if(vozilo->izracunajCenu(_ulica, _destinacija) > _budzet){
        cout << "Nemate dovoljno sredstava za ovaj prevoz" << endl;
        return;
    }
    else{
        _vozilo = vozilo;
        vozilo->dodajPutnika(_id);
    }
}

void Putnik::izljiIzVozila(){
    _vozilo->skloniPutnika(_id);
    _vozilo = nullptr;
}


void Putnik::setStanica(Stanica* stanica){
    _stanica = stanica;
    stanica->dodajPutnika(_id);
}


void Putnik::setUlica(Ulica* ulica){
    _ulica = ulica;
}


void Putnik::izadjiIzStanice(){
    _stanica->ukloniPutnika(_id);
    _stanica = nullptr;
}

void Putnik::izadjiIzUlice(){
    _ulica = nullptr;
}

void Putnik::setDestinacija(Ulica* destinacija){
    _destinacija = destinacija;
}

Ulica* Putnik::getDestinacija() const{
    return _destinacija;
}

void Putnik::skiniSaBudzeta(double vrednost){
    _budzet -= vrednost;
}

bool Putnik::jeInvalid() const{
    return _invalid;
}
bool Putnik::jePenzioner() const{   
    return _penzioner;
}

void Putnik::uracunajPopust(double popust){
    _budzet *= popust;
}