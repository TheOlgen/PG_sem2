//
// Created by olgar on 22.04.2024.
//

#ifndef UNTITLED1_ZOLW_H
#define UNTITLED1_ZOLW_H
#include "Zwierze.h"
#define SILA_ZOLWIA 2
#define INICJATYWA_ZOLWIA 1

class Swiat;
class Zolw : public Zwierze{

public:
    Zolw(Swiat& swiat, int x, int y);

    ~Zolw();
    std::string GetNazwa() override;
    Organizm *dziecko(int x, int y) override;
    void Akcja(char command) override;
    bool Unik(Organizm* atakujacy, Organizm* zaatakowany) override;
};


#endif //UNTITLED1_ZOLW_H
