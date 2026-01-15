#ifndef ULICA_H
#define ULICA_H

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <limits>
#include "../enum/tipoviSmerovaUlica.h"
#include "../stanica/stanica.h"

using namespace std;

class Ulica {
private:
    static int _counter;

    int _id;
    string _naziv;
    Ulica* _ulicaLevo; // ulica u koju trenutna ulazi levo
    Ulica* _ulicaDesno; // ulica u koju trenutna ulazi desno
    bool _jednosmerna;
    TipoviSmerovaUlica _smer; // koristi se samo kada je ulica jednosmerna
    vector<Ulica*> _povezaneUlice; // sve ulice koje ulaze u ovu ulicu i u njih moze skrenuti (znaci nisu jednosmerne sa suprotnim smerom)
    int _dozvoljenaBrzina; // maximalna brzina
    float _duzina;
    bool _podzemna;
    bool _pomorska;
    int zona;
    Stanica* _stanica;
public:
    // Dvosmerna
    Ulica(string, Ulica*, Ulica*, int, float, bool, bool, int);
    // Jednosmerna
    Ulica(string, Ulica*, Ulica*, TipoviSmerovaUlica, int, float, bool, bool, int);
    ~Ulica();

    void printUlica() const;
    void promenaMaxBrzine(int);
    void dodajPovezanuUlicu(Ulica*);
    int getDozvoljenaBrzina() const;

    
    int getID() const;
    int getZona() const;

    float getDuzina() const;
    string getNaziv() const;
    void setStanica(Stanica*);
    Stanica* getStanica() const;
    vector<Ulica*> getPovezaneUlice() const;

    Ulica* nadjiNajblizuUlicuSaStanicom(Ulica*, const vector<Stanica*>&);
    float najmanjaDuzina(const Ulica*) const;//najmanja duzina od ulice do ulica, za trenutnu ulicu prosledjujem drugu i vraca float

    Ulica* getUlicaLevo() const;
    Ulica* getUlicaDesno() const;

    void setulicaLevo(Ulica*);
    void setulicaDesno(Ulica*);

    bool jePodzemna() const;
    bool jePomorska() const;
};

#endif