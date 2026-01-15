#include "ulica.h"

int Ulica::_counter = 1;

//dvosmerna
Ulica::Ulica(string naziv, Ulica* ulicaLevo, Ulica* ulicaDesno, int dozvoljenaBrzina, float duzina, bool podzemna, bool pomorska, int zona) :
    _naziv(naziv), _ulicaLevo(ulicaLevo), _ulicaDesno(ulicaDesno), _dozvoljenaBrzina(dozvoljenaBrzina), _duzina(duzina), _podzemna(podzemna), _pomorska(pomorska), zona(zona) {
        _id = _counter++;
        if(ulicaLevo!=nullptr || (ulicaLevo!=nullptr && ulicaLevo->_pomorska == pomorska) || (ulicaLevo!=nullptr && ulicaLevo->_podzemna == podzemna))
        {
            ulicaLevo->_povezaneUlice.push_back(this);
        }
        if(ulicaDesno!=nullptr || (ulicaDesno!=nullptr && ulicaDesno->_pomorska == pomorska) || (ulicaDesno!=nullptr && ulicaDesno->_podzemna == podzemna))
        {
            ulicaDesno->_povezaneUlice.push_back(this);
        }
    }

//jednosmerna
Ulica::Ulica(string naziv, Ulica* ulicaLevo, Ulica* ulicaDesno, TipoviSmerovaUlica smer, int dozvoljenaBrzina, float duzina, bool podzemna, bool pomorska, int zona) :
    _naziv(naziv), _ulicaLevo(ulicaLevo), _ulicaDesno(ulicaDesno), _smer(smer), _dozvoljenaBrzina(dozvoljenaBrzina), _duzina(duzina), _podzemna(podzemna), _pomorska(pomorska), zona(zona) {
        _id = _counter++;

        if(ulicaLevo!=nullptr && smer == TipoviSmerovaUlica::levo){
            ulicaLevo->_povezaneUlice.push_back(this);
        }
        if(ulicaDesno!=nullptr && smer == TipoviSmerovaUlica::desno){
            ulicaDesno->_povezaneUlice.push_back(this);
        }
    }

Ulica::~Ulica() {}

string Ulica::getNaziv() const {
    return _naziv;
}

void Ulica::printUlica() const {
    cout << "Naziv: " << _naziv << endl;
    cout << "Dozvoljena brzina: " << _dozvoljenaBrzina << endl;
    cout << "Duzina: " << _duzina << endl;
    cout << "Podzemna: " << _podzemna << endl;
    cout << "Pomorska: " << _pomorska << endl;
    cout << "Zona: " << zona << endl;
}


void Ulica::promenaMaxBrzine(int maxBrzina) {
    _dozvoljenaBrzina = maxBrzina;
}

void Ulica::dodajPovezanuUlicu(Ulica* povezanaUlica) {
    _povezaneUlice.push_back(povezanaUlica);
}

int Ulica::getID() const {
    return _id;
}

float Ulica::getDuzina() const{
    return _duzina;
}

void Ulica::setStanica(Stanica* stanica) {
    _stanica = stanica;
}

int Ulica::getZona() const {
    return zona;
}

Stanica* Ulica::getStanica() const {
    return _stanica;
}

vector<Ulica*> Ulica::getPovezaneUlice() const {
    return _povezaneUlice;
}

Ulica* Ulica::nadjiNajblizuUlicuSaStanicom(Ulica* pocetna, const vector<Stanica*>& stanice) {
    if (!pocetna) {
        return nullptr;
    }

    // Kreiramo red za BFS i set za praćenje posećenih ulica
    queue<Ulica*> red;
    unordered_set<Ulica*> poseceneUlice;

    // Dodajemo početnu ulicu u red i set
    red.push(pocetna);
    poseceneUlice.insert(pocetna);

    // BFS pretraga
    while (!red.empty()) {
        Ulica* trenutnaUlica = red.front();
        red.pop();

        // Ako trenutna ulica ima stanicu
        Stanica* stanica = trenutnaUlica->getStanica();
        if (stanica != nullptr) {
            // Proveravamo da li je ta stanica u prosleđenom vektoru stanica
            for (Stanica* s : stanice) {
                if (s->getID() == stanica->getID()) {
                    return trenutnaUlica; // Vraćamo ulicu koja sadrži tu najbližu stanicu
                }
            }
        }

        // Dodajemo povezane ulice u red za dalju pretragu
        for (Ulica* povezanaUlica : trenutnaUlica->getPovezaneUlice()) {
            if (poseceneUlice.find(povezanaUlica) == poseceneUlice.end()) {
                red.push(povezanaUlica);
                poseceneUlice.insert(povezanaUlica);
            }
        }
    }

    // Ako ne pronađemo nijednu stanicu, vraćamo nullptr
    return nullptr;
}

int Ulica::getDozvoljenaBrzina() const{
    return _dozvoljenaBrzina;
}

float Ulica::najmanjaDuzina(const Ulica* target) const {
    if (target == nullptr) {
        return numeric_limits<float>::infinity();
    }

    unordered_map<const Ulica*, float> najmanjaDuzinaDoUlice;
    unordered_map<const Ulica*, const Ulica*> prethodnaUlica; // Praćenje prethodne ulice
    
    najmanjaDuzinaDoUlice[this] = 0;

    priority_queue<pair<float, const Ulica*>, vector<pair<float, const Ulica*>>, greater<pair<float, const Ulica*>>> red;
    red.push({0, this});

    unordered_set<const Ulica*> poseceneUlice;

    while (!red.empty()) {
        float trenutnaDuzina = red.top().first;
        const Ulica* trenutnaUlica = red.top().second;
        red.pop();

        if (poseceneUlice.find(trenutnaUlica) != poseceneUlice.end()) {
            continue;
        }

        poseceneUlice.insert(trenutnaUlica);

        if (trenutnaUlica == target) {
            // Povratak kroz prethodne ulice kako bi se isključile početna i krajnja
            float ukupnaDuzina = 0.0f;
            const Ulica* prethodna = prethodnaUlica[trenutnaUlica];
            while (prethodna != this) {
                ukupnaDuzina += najmanjaDuzinaDoUlice[prethodna] - najmanjaDuzinaDoUlice[prethodnaUlica[prethodna]];
                prethodna = prethodnaUlica[prethodna];
            }
            return ukupnaDuzina;
        }

        vector<const Ulica*> susedneUlice;
        for (Ulica* ulica : trenutnaUlica->getPovezaneUlice()) {
            susedneUlice.push_back(ulica);
        }
        
        if (trenutnaUlica->_ulicaLevo != nullptr) {
            susedneUlice.push_back(trenutnaUlica->_ulicaLevo);
        }
        if (trenutnaUlica->_ulicaDesno != nullptr) {
            susedneUlice.push_back(trenutnaUlica->_ulicaDesno);
        }

        for (const Ulica* susednaUlica : susedneUlice) {
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

    return numeric_limits<float>::infinity();
}

Ulica* Ulica::getUlicaLevo() const {    
    return _ulicaLevo;
}

Ulica* Ulica::getUlicaDesno() const {
    return _ulicaDesno;
}

void Ulica::setulicaLevo(Ulica* ulica) {
    _ulicaLevo = ulica;
    ulica->_povezaneUlice.push_back(this);
}

void Ulica::setulicaDesno(Ulica* ulica) {
    _ulicaDesno = ulica;
    ulica->_povezaneUlice.push_back(this);
}

bool Ulica::jePodzemna() const {
    return _podzemna;
}

bool Ulica::jePomorska() const {
    return _pomorska;
}