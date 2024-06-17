//
// Created by olgar on 24.04.2024.
//

#ifndef UNTITLED1_MLECZ_H
#define UNTITLED1_MLECZ_H

#define SILA_MLECZA 0
#define PRAWDO_ZASIANIA_MLECZ 4

#include "Roslina.h"

class Mlecz : public Roslina
{

public:
    Mlecz(Swiat &swiat, int x, int y);
    ~Mlecz();
    std::string GetNazwa() override;
    Organizm* dziecko(int x, int y);
    void Akcja(char command) override;
};

#endif //UNTITLED1_MLECZ_H
