//
// Created by olgar on 22.04.2024.
//

#include <iostream>
#include "Lis.h"
Lis::Lis(Swiat &swiat, int x, int y)
        : Zwierze(swiat, x, y, INICJATYWA_LISA, SILA_LISA, 'L')
{
    std::cout << "stworzenie Lisa" << std::endl;
}
Lis::~Lis(){
    std::cout << "destrukcja Lis" << std::endl;
}

std::string Lis::GetNazwa() {
    return "Lis";
}

void Lis::Akcja(char command) {
    int px,py;
    if(!this->LosujPola(&px, &py))
    {
        return;
    }
    if(!swiat.CzyPoleJestPuste(x+px, y+py))
    {
        if(swiat.dajSileZOrganizmu(x+px, y+py) > this->GetSila())
            return;
        if(Kolizja(swiat.dajOrganizmZPola(x+px, y+py)))
            this->RuszSie(px,py);
    }
    else
        this->RuszSie(px,py);
}
Organizm * Lis::dziecko(int x, int y)
{
    Organizm * dziecko = new Lis(this->swiat, x, y);
    return dziecko;
}