//
// Created by olgar on 24.04.2024.
//

#ifndef UNTITLED1_WILCZAJAGODA_H
#define UNTITLED1_WILCZAJAGODA_H

#define SILA_JAGODY 99
#define PRAWDO_ZASIANIA_JAGODY 15

#include "Roslina.h"

class WilczaJagoda : public Roslina
{

public:
    WilczaJagoda(Swiat &swiat, int x, int y);
    ~WilczaJagoda();
    std::string GetNazwa() override;
    Organizm* dziecko(int x, int y);
    bool Kolizja(Organizm * atakujacy) override;
};

#endif //UNTITLED1_WILCZAJAGODA_H
