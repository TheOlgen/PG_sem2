//
// Created by olgar on 20.04.2024.
//

#ifndef UNTITLED1_ZWIERZE_H
#define UNTITLED1_ZWIERZE_H


#include "../Organizm.h"
class Swiat;
class Zwierze : public Organizm {

public:
    Zwierze(Swiat &swiat, int x, int y, const int inicjatywa,
            const int sila, const char symbol);

    virtual void Akcja(char command) override;

    virtual bool Kolizja(Organizm* zaatakowany) override;
    virtual bool Walka(Organizm* zaatakowany);
    virtual bool Unik(Organizm* atakujacy, Organizm* zaatakowany); //true jesli organizm odparl atak albo uciekl
    virtual void ZrobDzieci(const int &x, const int &y) override; //Zwraca organizm swojego typu np wilka czy mlecza

    virtual std::string GetNazwa() override;
    virtual Organizm *dziecko(int x, int y) = 0;
};


#endif //UNTITLED1_ZWIERZE_H
