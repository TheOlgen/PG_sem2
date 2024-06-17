//
// Created by olgar on 22.04.2024.
//

#ifndef UNTITLED1_ANTYLOPA_H
#define UNTITLED1_ANTYLOPA_H

#define SILA_ANTYLOPY 4
#define INICJATYWA_ANTYLOPY 4

#include "Zwierze.h"

class Antylopa :
        public Zwierze{

public:
    Antylopa(Swiat& swiat, int x, int y);

    ~Antylopa() override;
    std::string GetNazwa() override;
    bool LosujPola(int *px, int* py) override;
    bool Unik(Organizm* atakujacy, Organizm* zaatakowany) override;
    Organizm *dziecko(int x, int y) override;
};


#endif //UNTITLED1_ANTYLOPA_H
