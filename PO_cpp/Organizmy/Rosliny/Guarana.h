//
// Created by olgar on 24.04.2024.
//

#ifndef UNTITLED1_GUARANA_H
#define UNTITLED1_GUARANA_H

#define SILA_GUARANY 0
#define PRAWDO_ZASIANIA_GUARANY 15

#include "Roslina.h"

class Guarana : public Roslina
{

public:
    Guarana(Swiat &swiat, int x, int y);
    ~Guarana();
    std::string GetNazwa() override;
    Organizm* dziecko(int x, int y);
    bool Kolizja(Organizm * atakujacy) override;
};

#endif //UNTITLED1_GUARANA_H
