#include "malo.h"

Malo::Malo(string naziv, int maxBrzina, int maxSedista, TipoviMalo tip, vector<Zona> cenovnik) :
    ImaVozaca(naziv, maxBrzina, maxSedista), _tip(tip), _cenovnik(cenovnik) {
        _zauzeto = false;
        _trenutnaRuta = make_pair(nullptr, nullptr);
    }


Malo::~Malo() {}


void Malo::stampa() const{
    cout << "ID: " << Prevoz::getID();
    cout << "Naziv: " << ImaVozaca::getNaziv();
    cout << "Tip: " << _tip << endl;
}

bool Malo::dodajPutnika(int putnik){
    if(getSedistaZauzeto() + 1 <= getMaxSedista()){
        putnici.push_back(putnik);
        setSedistaZauzeto(getSedistaZauzeto() + 1);
        if(_tip == TipoviMalo::taksi){
            _zauzeto = true;
        }
    }
}

void Malo::skloniPutnika(int putnik){
    auto it = find(putnici.begin(), putnici.end(), putnik);
    if(it != putnici.end()){
        putnici.erase(it);
        setSedistaZauzeto(getSedistaZauzeto() - 1);
        if(_tip == TipoviMalo::taksi){
            _zauzeto = false;
        }
    }
}

double Malo::izracunajCenu(Ulica* pocetna, Ulica* krajnja){
    pair<Ulica*, Ulica*> par = make_pair(pocetna, krajnja);
    _trenutnaRuta = par;
    _ruta = nadjiNajkraciPut(pocetna, krajnja);
    
    double daljina = pocetna->najmanjaDuzina(krajnja);
    int zona = krajnja->getZona();
    int cenaPoZoni;

    for(const auto& zonce : _cenovnik){
        if(zonce.id == zona){
            cenaPoZoni = zonce.cena;
        }
    }
    cout << daljina << endl;
    cout << cenaPoZoni << endl;
    return cenaPoZoni * daljina * 0.1;
}

typedef pair<float, Ulica*> Pair;


vector<int> Malo::nadjiNajkraciPut(Ulica* pocetna, Ulica* target) {
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
            for(auto ulica : putIzmedju){
                cout << ulica << endl;
            }
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

vector<int> Malo::getRuta() const{
    return _ruta;
} 

TipoviMalo Malo::getTip() const{
    return _tip;
}

void Malo::zapocniKretanje(vector<int> ruta, Ulica* pocetna, Ulica* krajnja, vector<Putnik*>& sviPutnici, vector<Ulica*>& ulice){  
    for(int i = 0 ; i < ruta.size();i++)
    {
        cout << "Usao" << endl;
        int id = ruta.at(i);

        Ulica* trenutnaUlica = nullptr;

        for(auto& ulica : ulice){
            if(ulica->getID() == id){
                trenutnaUlica = ulica;
                break;
        }

        for(auto pr : putnici){
            for(auto p : sviPutnici){
                if(p->getID() == pr){
                    if(p->getDestinacija()->getID() == trenutnaUlica->getID()){
                        p->izljiIzVozila();
                        p->skiniSaBudzeta(izracunajCenu(p->getUlica(), p->getDestinacija()));
                        p->setUlica(trenutnaUlica);
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
}