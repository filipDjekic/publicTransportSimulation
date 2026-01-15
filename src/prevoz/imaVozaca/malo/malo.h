#ifndef MALO_H
#define MALO_h

#include "../imaVozaca.h"
#include "../../../ulica/ulica.h"
#include "../../../enum/tipoviMalo.h"
#include "../../../putnik/putnik.h"
#include <utility>
#include <algorithm>
#include <vector>

typedef struct zona{
    int id;
    double cena;
}Zona;

class Malo : public ImaVozaca{
private:
    TipoviMalo _tip;

    bool _zauzeto;
    vector<int> putnici;

    vector<Zona> _cenovnik;

    pair<Ulica*, Ulica*> _trenutnaRuta;
    vector<int> _ruta;

public:
    Malo(string, int, int, TipoviMalo, vector<Zona>);
    ~Malo();

    virtual void stampa() const override;

    virtual bool dodajPutnika(int) override;
    virtual void skloniPutnika(int) override;
    virtual double izracunajCenu(Ulica*, Ulica*) override;
    vector<int>nadjiNajkraciPut(Ulica*, Ulica*);
    void zapocniKretanje(vector<int>, Ulica* , Ulica*, vector<Putnik*>&, vector<Ulica*>&);
    TipoviMalo getTip() const;
    vector<int> getRuta() const;
};

#endif