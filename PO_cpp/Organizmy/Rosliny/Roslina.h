//
// Created by olgar on 24.04.2024.
//

#ifndef UNTITLED1_ROSLINA_H
#define UNTITLED1_ROSLINA_H
#define INICJATYWA_ROSLINY 0

#include "../Organizm.h"

class Roslina : public Organizm {

protected:
    int prawdoZasiania; //prawdopodobieństwo zasiania, mniejsze liczby maja wieksze prawdopodobienstwo
    double GetPrawdoZasiania() const;
    bool sprobujZasiac();

public:
    Roslina(Swiat &swiat, int x, int y, const int sila, const char symbol, double prawdoZasiania);

    virtual ~Roslina();

    virtual void Akcja(char command) override;
    virtual Organizm* dziecko(int x, int y);
    virtual bool Kolizja(Organizm * atakujacy) override;
    virtual std::string GetNazwa() override;
    virtual bool Unik(Organizm* atakujacy, Organizm* zaatakowany) override; //true jesli organizm odparl atak albo uciekl
    virtual void ZrobDzieci(const int &x, const int &y) override;
};


#endif //UNTITLED1_ROSLINA_H
