//
// Created by olgar on 22.04.2024.
//

#ifndef UNTITLED1_LIS_H
#define UNTITLED1_LIS_H

#define SILA_LISA 3
#define INICJATYWA_LISA 7

#include "Zwierze.h"

class Lis :
        public Zwierze{

public:
    Lis(Swiat& swiat, int x, int y);

    ~Lis() override;
    std::string GetNazwa() override;
    void Akcja(char command) override;
    Organizm *dziecko(int x, int y) override;
};

#endif //UNTITLED1_LIS_H
