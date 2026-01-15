#include "veliko.h"


Veliko::~Veliko() {}


Veliko::Veliko(string naziv, int maxBrzina, int maxSedista,Ulica* ulica, TipoviVeliko tip, int maxStoje, Ruta* ruta) :
    ImaVozaca(naziv, maxBrzina, maxSedista), _tip(tip), maxStoje(maxStoje), zauzetoStoje(0), _ruta(ruta) {
        _stanica = 0;
        setUlica(ulica);
}

void Veliko::promeniStanicu(int stanica){
    _stanica = stanica;
}   

double Veliko::izracunajCenu(Ulica* pocetak, Ulica* kraj) {
    double cena = _ruta->cena(pocetak->getID(),kraj->getID());
    return cena;
}

bool Veliko::dodajPutnika(int putnik) {
    if(getSedistaZauzeto() + 1 <= getMaxSedista()){
        setSedistaZauzeto(getSedistaZauzeto() + 1);
        putnici.push_back(make_pair(putnik, false));
        return true;
    }
    else if(zauzetoStoje + 1 <= maxStoje){
        zauzetoStoje = zauzetoStoje + 1;
        putnici.push_back(make_pair(putnik, true));
        return true;
    }
    else{
        cout << this->getNaziv() << " je pun!" << endl;
        return false;
    }
}

void Veliko::skloniPutnika(int putnik) {
    putnici.erase(remove_if(putnici.begin(), putnici.end(),
        [putnik](const pair<int, bool>& p) { return p.first == putnik; }),
        putnici.end());
}

void Veliko::stampa() const {
    cout << "Naziv: " << getNaziv() << endl;
}

Ruta* Veliko::getRuta() const{
    return _ruta;
}

void Veliko::zapocniKretanje(vector<int> ruta, Ulica* pocetna, Ulica* krajnja, vector<Putnik*>& sviPutnici, vector<Ulica*>& ulice){
    for(int i = 0; i < ruta.size(); i++){
        int id = ruta.at(i);
        
        Ulica* trenutnaUlica = nullptr;

        for(auto& ulica : ulice){
            if(ulica->getID() == id){
                trenutnaUlica = ulica;
                break;
        }
        }

        for(auto pr : putnici){
            for(auto p : sviPutnici){
                if(p->getID() == pr.first){
                    if(p->getDestinacija()->getID() == trenutnaUlica->getID()){
                        cout << "Putnik(" << p->getID() << ") izlazi iz vozila!" << endl;
                        sleep(3);
                        p->izljiIzVozila();
                        p->skiniSaBudzeta(izracunajCenu(p->getUlica(), p->getDestinacija()));
                        p->setUlica(trenutnaUlica);
                    }
                }
            }
        }

        Stanica* trenutnaStanica = trenutnaUlica->getStanica();
        if(trenutnaStanica->brojPutnika() > 0)
        {
            vector<int> red = trenutnaStanica->getRedPutnika();
            for(int j = 0; j < red.size(); j++){
                for(auto p : sviPutnici){
                    if(red[j] == p->getID()){
                        cout << "Putnik(" << p->getID() << ") ulazi u vozilo!" << endl;
                        sleep(3);
                        p->udjiUVozilo(this);
                        p->izadjiIzStanice();
                        trenutnaStanica->ukloniPutnika(red[j]);
                    }
                }
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
            cout << "Vozilo krece sa prve stanice" << endl;
            cout << "Stanica: " << trenutnaStanica->getIme() << endl;
            sleep(vreme);
            this->setUlica(trenutnaUlica);
        }
        else if(trenutnaUlica->getID() == krajnja->getID())
        {
            cout << "Vozilo staje na poslednjoj stanici" << endl;
            cout << "Stanica: " << trenutnaStanica->getIme() << endl;
            this->setUlica(trenutnaUlica);
            break;
        }
        else{
            cout << "Vozilo je na stanici" << trenutnaStanica->getIme() << endl;
            cout << "Stanica: " << trenutnaStanica->getIme() << endl;
            sleep(vreme);
            this->setUlica(trenutnaUlica);
        }

    }
}