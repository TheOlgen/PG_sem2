//
// Created by olgar on 21.04.2024.
//

#ifndef UNTITLED1_OWCA_H
#define UNTITLED1_OWCA_H
#include "Zwierze.h"
#define SILA_OWCY 4
#define INICJATYWA_OWCY 4

class Swiat;
class Owca : public Zwierze{

public:
    Owca(Swiat& swiat, int x, int y);

    ~Owca();
    std::string GetNazwa() override;
    Organizm *dziecko(int x, int y) override;
};


#endif //UNTITLED1_OWCA_H
