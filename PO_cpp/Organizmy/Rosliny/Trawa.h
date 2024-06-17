//
// Created by olgar on 24.04.2024.
//

#ifndef UNTITLED1_TRAWA_H
#define UNTITLED1_TRAWA_H
#define SILA_TRAWY 0
#define PRAWDO_ZASIANIA_TRAWA 3

#include "Roslina.h"

class Trawa : public Roslina
        {

public:
    Trawa(Swiat &swiat, int x, int y);
    ~Trawa();
    std::string GetNazwa() override;
    Organizm* dziecko(int x, int y);
};


#endif //UNTITLED1_TRAWA_H
