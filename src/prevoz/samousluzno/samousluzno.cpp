#include "samousluzno.h"
#include <limits>
#include <queue>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>


Samousluzno::Samousluzno(string naziv, int maxBrzina, int satnica) : Prevoz(naziv, maxBrzina), _satnica(satnica) {
    _tip = TipoviSamousluzno::Bicikl;
}

Samousluzno::Samousluzno(string naziv, int maxBrzina, int satnica, double kapacitetBaterije, double potrosnja) : Prevoz(naziv, maxBrzina), _satnica(satnica), kapacitetBaterije(kapacitetBaterije), potrosnjaPoKm(potrosnja) {
    _tip = TipoviSamousluzno::Trotinet;
}

Samousluzno::~Samousluzno() {}

double Samousluzno::izracunajSatnicu(double sati) {
    return sati * _satnica;
}

double Samousluzno::izracunajCenu(Ulica* ulica1, Ulica* ulica2) {
    pair<Ulica*, Ulica*> par = make_pair(ulica1, ulica1);
    _trenutnaRuta = par;
    _ruta = nadjiNajkraciPut(ulica1, ulica2);
    double razdaljina = ulica1->najmanjaDuzina(ulica2);
    if(_tip == TipoviSamousluzno::Trotinet){
        if(kapacitetBaterije < potrosnjaPoKm * razdaljina){
            cout << "Trotinet nema dovoljno da predje dati put" << endl;
            return -1;
        }
    }

    double vreme = razdaljina / getMaxBrzina();
    double cena = izracunajSatnicu(vreme);
    return cena;
}
bool Samousluzno::dodajPutnika(int putnik) {
    _korisnik = putnik;
    return true;
}

void Samousluzno::skloniPutnika(int putnik) {
    _korisnik = -1;
}

void Samousluzno::stampa() const {
    cout << getNaziv() << "   " << getTip() << endl;
}

TipoviSamousluzno Samousluzno::getTip() const {
    return _tip;
}

void Samousluzno::zapocniKretanje(vector<int> ruta, Ulica* pocetna, Ulica* krajnja, vector<Putnik*>& sviPutnici, vector<Ulica*>& ulice) {
    for(int i = 0 ; i< ruta.size();i++){
        int id = ruta.at(i);
        Ulica* trenutnaUlica = nullptr;

        for(auto& ulica : ulice){
            if(ulica->getID() == id){
                trenutnaUlica = ulica;
                break;
            }
        }

        int brzina = trenutnaUlica->getDozvoljenaBrzina();
        double duzina = trenutnaUlica->getDuzina();
        int mojaBrzina = getMaxBrzina();
        if(getMaxBrzina() > brzina){
            mojaBrzina = brzina;
        }
        double vreme = duzina / mojaBrzina;


        if(trenutnaUlica->getID() == pocetna->getID()){
            cout << "Vozilo krece sa prve ulice" << endl;
            cout << "Ulica: " << trenutnaUlica->getNaziv() << endl;
            sleep(vreme);
            this->setUlica(trenutnaUlica);
        }
        else if(trenutnaUlica->getID() == krajnja->getID())
        {
            cout << "Vozilo staje na poslednjoj ulici" << endl;
            cout << "Ulica: " << trenutnaUlica->getNaziv() << endl;
            this->setUlica(trenutnaUlica);
            for(auto p : sviPutnici){
                if(p->getID() == _korisnik){
                    p->izljiIzVozila();
                    p->setDestinacija(trenutnaUlica);
                    p->setUlica(trenutnaUlica);
                }
            }
            break;
        }
        else{
            cout << "Vozilo je na ulici" << trenutnaUlica->getNaziv() << endl;
            cout << "Ulica: " << trenutnaUlica->getNaziv() << endl;
            sleep(vreme);
            this->setUlica(trenutnaUlica);
        }
    }
}

vector<int> Samousluzno::nadjiNajkraciPut(Ulica* pocetna, Ulica* target) {
    vector<int> putIzmedju;

    if (pocetna == nullptr || target == nullptr) {
        return putIzmedju; // Prazan vektor ako ne postoji pocetna ili ciljna ulica
    }

    unordered_map<Ulica*, float> najmanjaDuzinaDoUlice;
    unordered_map<Ulica*, Ulica*> prethodnaUlica;
    
    najmanjaDuzinaDoUlice[pocetna] = 0;

    priority_queue<pair<float, Ulica*>, vector<pair<float, Ulica*>>, greater<pair<float, Ulica*>>> red;
    red.push({0, pocetna});

    unordered_set<Ulica*> poseceneUlice;

    while (!red.empty()) {
        float trenutnaDuzina = red.top().first;
        Ulica* trenutnaUlica = red.top().second;
        red.pop();

        if (poseceneUlice.find(trenutnaUlica) != poseceneUlice.end()) {
            continue;
        }

        poseceneUlice.insert(trenutnaUlica);

        if (trenutnaUlica == target) {
            Ulica* prethodna = prethodnaUlica[trenutnaUlica];
            while (prethodna != pocetna) {
                putIzmedju.push_back(prethodna->getID());
                prethodna = prethodnaUlica[prethodna];
            }
            reverse(putIzmedju.begin(), putIzmedju.end());
            return putIzmedju;
        }

        vector<Ulica*> susedneUlice;
        for (Ulica* ulica : trenutnaUlica->getPovezaneUlice()) {
            susedneUlice.push_back(ulica);
        }

        if (trenutnaUlica->getUlicaLevo() != nullptr) {
            susedneUlice.push_back(trenutnaUlica->getUlicaLevo());
        }
        if (trenutnaUlica->getUlicaDesno() != nullptr) {
            susedneUlice.push_back(trenutnaUlica->getUlicaDesno());
        }

        for (Ulica* susednaUlica : susedneUlice) {
            if (poseceneUlice.find(susednaUlica) == poseceneUlice.end()) {
                float novaDuzina = trenutnaDuzina + susednaUlica->getDuzina();

                if (najmanjaDuzinaDoUlice.find(susednaUlica) == najmanjaDuzinaDoUlice.end() || novaDuzina < najmanjaDuzinaDoUlice[susednaUlica]) {
                    najmanjaDuzinaDoUlice[susednaUlica] = novaDuzina;
                    prethodnaUlica[susednaUlica] = trenutnaUlica;
                    red.push({novaDuzina, susednaUlica});
                }
            }
        }
    }

    return putIzmedju; // Ako ne postoji put do cilja, vraćamo prazan vektor
}
vector<int> Samousluzno::getRuta() const{
    return _ruta;
} 