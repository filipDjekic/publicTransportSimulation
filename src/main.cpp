#include "ulica/ulica.h"
#include "putnik/putnik.h"
#include "prevoz/prevoz.h"
#include "prevoz/imaVozaca/imaVozaca.h"
#include "prevoz/imaVozaca/veliko/veliko.h"
#include "prevoz/samousluzno/samousluzno.h"
#include "prevoz/imaVozaca/malo/malo.h"
#include "ruta/ruta.h"
#include "stanica/stanica.h"
#include "stanica/podzemna/podzemna.h"
#include "stanica/nadzemna/nadzemna.h"
#include <typeinfo>
#include <iostream>

using namespace std;

int main()
{

    // UNOSENJE SVEGA
    vector<Ulica *> ulice;

    Ulica ulica1("Kordonboyu", nullptr, nullptr, 50, 200, false, false, 1);
    ulice.push_back(&ulica1);
    Ulica ulica2("Alsancak", &ulica1, nullptr, 50, 150, false, false, 1);
    ulice.push_back(&ulica2);
    Ulica ulica3("Bornova Caddesi", nullptr, &ulica2, 50, 150, false, false, 1);
    ulice.push_back(&ulica3);
    Ulica ulica4("Konak Meydanı", nullptr, &ulica2, 50, 80, false, false, 1);
    ulice.push_back(&ulica4);
    Ulica ulica5("Karşıyaka Çarşısı", &ulica4, &ulica2, 50, 150, false, false, 2);
    ulice.push_back(&ulica5);
    Ulica ulica6("Güzelyalı Mahallesi", &ulica4, &ulica3, 40, 170, false, false, 2);
    ulice.push_back(&ulica6);
    Ulica ulica7("Buca Caddesi", &ulica6, &ulica3, 40, 170, false, false, 2);
    ulice.push_back(&ulica7);
    Ulica ulica8("Balçova", &ulica7, &ulica3, TipoviSmerovaUlica::desno, 40, 170, false, false, 3);
    ulice.push_back(&ulica8);
    Ulica ulica9("İsmet Kaptan", &ulica4, &ulica8, 30, 145, false, false, 3);
    ulice.push_back(&ulica9);
    Ulica ulica10("Çankaya", &ulica9, &ulica3, 40, 170, false, false, 4);
    ulice.push_back(&ulica10);
    Ulica ulica11("Güzelbahçe", nullptr, nullptr, 40, 170, true, false, 1);
    ulice.push_back(&ulica11);
    Ulica ulica12("Konak Meydanı", nullptr, nullptr, 50, 150, true, false, 1);
    ulice.push_back(&ulica12);
    Ulica ulica13("Karaköy", nullptr, nullptr, 50, 200, true,false,1);
    ulice.push_back(&ulica13);

    ulica11.setulicaDesno(&ulica12);
    ulica12.setulicaDesno(&ulica13);
    ulica13.setulicaDesno(&ulica11);
    // PREVOZI
    vector<Prevoz *> prevozi;

    Ruta r1("Ruta Alsancak - Konak Meydan", 100);
    Ruta r2("Ruta Buca Cadessi - İsmet Kaptan", 55);
    Ruta r3("Ruta Güzelbahçe - Konak Meydanı", 250);


    Veliko v1("Autobus Alsancak - Konak Meydan", 80, 30, &ulica2, TipoviVeliko::autobus, 20, &r1);
    prevozi.push_back(&v1);
    Veliko v2("Tramvaj Buca Cadessi - İsmet Kaptan", 60, 30, &ulica7, TipoviVeliko::tramvaj, 20, &r2);
    prevozi.push_back(&v2);
    Veliko v3("Metro Güzelbahçe - Konak Meydanı", 60, 30, &ulica11, TipoviVeliko::metro, 20, &r3);
    prevozi.push_back(&v3);
    Samousluzno sm1("Bicikl 1", 40, 50);
    prevozi.push_back(&sm1);
    Samousluzno sm2("Trotinet 1", 40, 5, 6000, 5);
    prevozi.push_back(&sm2);
    vector<Zona> cenovnik1 = {
        {1, 5.0},
        {2, 10.0},
        {3, 15.0}};

    Malo m1("Taksi 255", 50, 50, TipoviMalo::taksi, cenovnik1);
    prevozi.push_back(&m1);
    vector<Zona> cenovnik2 = {
        {1, 50.0},
        {2, 30.0},
        {3, 40.0}};
    Malo m2("Dolmus 1", 50, 50, TipoviMalo::dolmus, cenovnik2);

    // RUTE
    vector<Ruta> rute;

    vector<int> ruta1;
    ruta1.push_back(2);
    ruta1.push_back(5);
    ruta1.push_back(4);
    r1.setRuta(ruta1, v1.getID());
    rute.push_back(r1);

    vector<int> ruta2;
    ruta2.push_back(7);
    ruta2.push_back(8);
    ruta2.push_back(9);
    r2.setRuta(ruta2, v2.getID());
    rute.push_back(r2);

    vector<int> ruta3;
    ruta3.push_back(11);
    ruta3.push_back(12);
    ruta3.push_back(13);
    r3.setRuta(ruta3, v3.getID());
    rute.push_back(r3);

    // STANICE
    vector<Stanica*> stanice;

    // NADZEMNE
    Nadzemna nd1("Alsancak - Konak Meydan - 1", ulica2.getID());
    ulica2.setStanica(&nd1);
    Nadzemna nd2("Alsancak - Konak Meydan - 2", ulica5.getID());
    ulica5.setStanica(&nd2);
    Nadzemna nd3("Alsancak - Konak Meydan - 3", ulica4.getID());
    ulica4.setStanica(&nd3);

    Nadzemna nd4("Buca Cadessi - İsmet Kaptan - 1", ulica7.getID());
    ulica7.setStanica(&nd4);
    Nadzemna nd5("Buca Cadessi - İsmet Kaptan - 2", ulica8.getID());
    ulica8.setStanica(&nd5);
    Nadzemna nd6("Buca Cadessi - İsmet Kaptan - 3", ulica9.getID());
    ulica9.setStanica(&nd6);

    // PODZEMNE
    vector<TipoviUlaza> tipoviUlaza;
    tipoviUlaza.push_back(TipoviUlaza::lift);
    Podzemna pd1("Metro Güzelbahçe - Konak Meydanı 1", ulica11.getID(), 50.0, tipoviUlaza);
    ulica11.setStanica(&pd1);
    Podzemna pd2("Metro Güzelbahçe - Konak Meydanı 2", ulica12.getID(), 50.0, tipoviUlaza);
    ulica12.setStanica(&pd2);
    Podzemna pd3("Metro Güzelbahçe - Konak Meydanı 3", ulica13.getID(), 50.0, tipoviUlaza);
    ulica13.setStanica(&pd3);

    stanice.push_back(&nd1);
    stanice.push_back(&nd2);
    stanice.push_back(&nd3);
    stanice.push_back(&nd4);
    stanice.push_back(&nd5);
    stanice.push_back(&nd6);
    stanice.push_back(&pd1);
    stanice.push_back(&pd2);
    stanice.push_back(&pd3);

    vector<Putnik *> putnici;
    // UNOSENJE MENE
    cout << "-----------------------------" << endl;
    cout << "UNESITE POTREBNE PODATKE: " << endl;
    cout << "-----------------------------" << endl;
    cout << "Ime: ";
    cout << "-----------------------------" << endl;
    string ime;
    cin >> ime;
    cout << "Da li ste invalid(1/0):";
    cout << "-----------------------------" << endl;
    bool invalid = false;
    int inv;
    cin >> inv;
    if (inv == 1)
    {
        invalid = true;
    }
    cout << "Da li ste penzioner(1/0):";
    cout << "-----------------------------" << endl;
    bool penzioner = false;
    int pen;
    cin >> pen;
    if (pen == 1)
    {
        invalid = true;
    }
    cout << "Unesite svoj budzet: ";
    cout << "-----------------------------" << endl;
    double b;
    cin >> b;
    Putnik ja(ime, invalid, penzioner, b);
    putnici.push_back(&ja);

    int mojaUlica;
    cout << "-----------------------------" << endl;
    cout << "Unesite gde se nalazite (izaberite ID ulice): " << endl;
    cout << "-----------------------------" << endl;
    cout << "Ulice kojima možete pristupiti: " << endl;
    cout << "" << endl;
    for (auto ulica : ulice)
    {
        cout << ulica->getID() << "." << ulica->getNaziv() << endl;
    }
    cin >> mojaUlica;
    for (auto &ulica : ulice)
    {
        if (ulica->getID() == mojaUlica)
        {
            ja.setUlica(ulica);
            break;
        }
    }
    cout << "" << endl;
    bool usaoUPrevoz = false;
    int nasaoRezervu = 0;
    ja.stampa();
    while (!usaoUPrevoz)
    {
        int dest;
        cout << "Unesite gde zelite da idete (izaberite ID ulice): " << endl;
        for (auto ulica : ulice)
        {
            if(ulica != ja.getUlica() && (ulica->jePodzemna() == ja.getUlica()->jePodzemna() && ulica->jePomorska() == ja.getUlica()->jePomorska())){
                cout << ulica->getID() << ". " << ulica->getNaziv() << endl;
            }
        }
        cin >> dest;
        for (auto &ulica : ulice)
        {
            if (ulica->getID() == dest)
            {
                ja.setDestinacija(ulica);
                break;
            }
        }

        if (ja.getUlica()->getID() == ja.getDestinacija()->getID())
        {
            cout << "Iste ulice, molimo unesite opet!!!" << endl;
            continue;
        }
        for (Ruta r : rute)
        {
            if (r.nalaziSeNaRuti(ja.getUlica()->getID(), ja.getDestinacija()->getID()))
            {
                for (auto p : prevozi)
                { // sva veca vozila
                    if (p == dynamic_cast<Veliko *>(p))
                    {
                        ja.setStanica(ja.getUlica()->getStanica());
                        dynamic_cast<Veliko *>(p)->zapocniKretanje(r.getRuta(), ja.getUlica(), ja.getDestinacija(), putnici, ulice);
                        double popust = 1.0;
                        if (ja.jeInvalid())
                        {
                            popust -= 0.3;
                        }
                        if (ja.jePenzioner())
                        {
                            popust -= 0.3;
                        }
                        ja.skiniSaBudzeta(p->izracunajCenu(ja.getUlica(), ja.getDestinacija()) * popust);
                        usaoUPrevoz = true;
                    }
                }
            }
        }
        int nasaoRezervu = 0;
        while((ja.jeInvalid() && nasaoRezervu < 2) || (nasaoRezervu<4)){
            if (ja.jeInvalid())
            {
                cout << "-----------------------------" << endl;
                cout << "Nema postojece rute za ovaj prevoz, mozda da birate drugo\n(1-Taksi, 2-Dolmus)" << endl;
                cout << "-----------------------------" << endl;
            }
            else
            {
                cout << "-----------------------------" << endl;
                cout << "Nema postojece rute za ovaj prevoz, mozda da pozovete da birate drugo\n(1-Taksi, 2-Dolmus, 3-Bicikl, 4-Trotinet):" << endl;
                cout << "-----------------------------" << endl;
            }
            int indeks;
            cin >> indeks;
            if(indeks < 0 && indeks > 2 && ja.jeInvalid()){
                while(indeks < 0 || indeks > 2){
                    cout << "Pogresan unos!" << endl;
                    cout << "Unesite ponovo (1-Taksi, 2-Dolmus): ";
                    cin >> indeks;
                }
            }
            else{
                while(indeks < 0 || indeks > 4){
                    cout << "Pogresan unos!" << endl;
                    cout << "Unesite ponovo (1-Taksi, 2-Dolmus, 3-Bicikl, 4-Trotinet): ";
                    cin >> indeks;
                }
            }
            switch (indeks)
            {
            case 1: // taksi
            {
                for (auto p : prevozi)
                {
                    if (p == dynamic_cast<Malo *>(p))
                    {
                        TipoviMalo tip = dynamic_cast<Malo *>(p)->getTip();
                        if(tip == 0 && ja.getBudzet() - p->izracunajCenu(ja.getUlica(), ja.getDestinacija()) >= 0){
                            p->stampa();
                        }
                    }
                }
                cout << "Izaberite jednom vozilo (birate ID vozila): ";
                int id;
                cin >> id;
                Prevoz* prevoz;
                for (auto p : prevozi)
                {
                    if(p->getID() == id){
                        prevoz = dynamic_cast<Malo*>(prevoz);
                    }
                }
                double popust = 1.0;
                if (ja.jeInvalid())
                {
                    popust -= 0.3;
                }
                if (ja.jePenzioner())
                {
                    popust -= 0.4;
                }
                ja.skiniSaBudzeta(prevoz->izracunajCenu(ja.getUlica(), ja.getDestinacija()) * popust);
                usaoUPrevoz = true;
                nasaoRezervu+=100;
                dynamic_cast<Malo *>(prevoz)->zapocniKretanje(dynamic_cast<Malo *>(prevoz)->getRuta(), ja.getUlica(), ja.getDestinacija(), putnici, ulice);
                break;
            }
            case 2:
            { // dolmus
                for (auto p : prevozi)
                {
                    if (p == dynamic_cast<Malo *>(p))
                    {
                        double popust = 1.0;
                            if (ja.jeInvalid())
                            {
                                popust -= 0.3;
                            }
                            if (ja.jePenzioner())
                            {
                                popust -= 0.4;
                            }
                        TipoviMalo tip = dynamic_cast<Malo *>(p)->getTip();
                        if (ja.getBudzet() - p->izracunajCenu(ja.getUlica(), ja.getDestinacija()) >= 0 && tip == 1)
                        {
                            ja.skiniSaBudzeta(p->izracunajCenu(ja.getUlica(), ja.getDestinacija()) * popust);
                            usaoUPrevoz = true;
                            nasaoRezervu+=100;
                            dynamic_cast<Malo *>(p)->zapocniKretanje(dynamic_cast<Malo *>(p)->getRuta(), ja.getUlica(), ja.getDestinacija(), putnici, ulice);
                        }
                    }
                }
                break;
            }
            case 3:
            { // bicikl
                for (auto p : prevozi)
                {
                    Samousluzno *samousluzno = dynamic_cast<Samousluzno *>(p);
                    if (samousluzno && samousluzno->getTip() == 1)
                    {
                        double popust = 1.0;
                            if (ja.jeInvalid())
                            {
                                popust -= 0.3;
                            }
                            if (ja.jePenzioner())
                            {
                                popust -= 0.4;
                            }
                        if ((ja.getBudzet() - p->izracunajCenu(ja.getUlica(), ja.getDestinacija())*popust))
                        {
                            ja.skiniSaBudzeta(p->izracunajCenu(ja.getUlica(), ja.getDestinacija()) * popust);
                            usaoUPrevoz = true;
                            nasaoRezervu+=100;
                            dynamic_cast<Samousluzno *>(p)->zapocniKretanje(samousluzno->getRuta(), ja.getUlica(), ja.getDestinacija(), putnici, ulice);
                        }
                    }
                }
                break;
            }
            case 4:
            { // trotinet
                for (auto p : prevozi)
                {
                    if (p == dynamic_cast<Samousluzno *>(p))
                    {
                        double popust = 1.0;
                            if (ja.jeInvalid())
                            {
                                popust -= 0.3;
                            }
                            if (ja.jePenzioner())
                            {
                                popust -= 0.4;
                            }
                        TipoviSamousluzno tip = dynamic_cast<Samousluzno *>(p)->getTip();
                        if (ja.getBudzet() - p->izracunajCenu(ja.getUlica(), ja.getDestinacija()) >= 0 && tip == 0)
                        {
                            ja.skiniSaBudzeta(p->izracunajCenu(ja.getUlica(), ja.getDestinacija()) * popust);
                            usaoUPrevoz = true;
                            nasaoRezervu+=100;
                            dynamic_cast<Samousluzno *>(p)->zapocniKretanje(dynamic_cast<Samousluzno *>(p)->getRuta(), ja.getUlica(), ja.getDestinacija(), putnici, ulice);
                        }
                    }
                }
                break;
            }
            default:{
                break;
            }
            }   
        }
        if (!usaoUPrevoz)
        {
            cout << "-----------------------------" << endl;
            cout << "Birajte opet!" << endl;
            cout << "-----------------------------" << endl;
            cout << "-----------------------------" << endl;
            cout << "Nemate dovoljno para ni za jedan moguci prevoz, pesacite..." << endl;
            cout << "-----------------------------" << endl;
            return 1;
        }
        else if (usaoUPrevoz)
        {
            cout << "-----------------------------" << endl;
            cout << "Stigao sam na destinaciju!" << endl;
            cout << "-----------------------------" << endl;
            ja.stampa();
            cout << "-----------------------------" << endl;
            cout << "Kraj" << endl;
            cout << "-----------------------------" << endl;
            break;
        }
    }
}