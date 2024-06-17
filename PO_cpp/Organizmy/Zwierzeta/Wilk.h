//
// Created by olgar on 21.04.2024.
//

#ifndef UNTITLED1_WILK_H
#define UNTITLED1_WILK_H

#define SILA_WILKA 9
#define INICJATYWA_WILKA 5

#include "Zwierze.h"

class Wilk :
        public Zwierze{

public:
    Wilk(Swiat& swiat, int x, int y);

    ~Wilk() override;
    std::string GetNazwa() override;
    Organizm *dziecko(int x, int y) override;
};




#endif //UNTITLED1_WILK_H
