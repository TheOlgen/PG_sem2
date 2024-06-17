//
// Created by olgar on 24.04.2024.
//

#ifndef UNTITLED1_BARSZCZ_H
#define UNTITLED1_BARSZCZ_H

#define SILA_BARSZCZU 10
#define PRAWDO_ZASIANIA_BARSZCZU 15

#include "Roslina.h"

class Barszcz : public Roslina
{
private:
    void zabijDookola(int x, int y);

public:
    Barszcz(Swiat &swiat, int x, int y);
    ~Barszcz();
    std::string GetNazwa() override;
    Organizm* dziecko(int x, int y);
    void Akcja(char command) override;
    bool Kolizja(Organizm * atakujacy) override;

};

#endif //UNTITLED1_BARSZCZ_H
