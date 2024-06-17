//
// Created by olgar on 21.04.2024.
//

#include <iostream>
#include "Wilk.h"
Wilk::Wilk(Swiat &swiat, int x, int y)
        : Zwierze(swiat, x, y, INICJATYWA_WILKA, SILA_WILKA, 'W')
{
    std::cout << "stworzenie Wilka" << std::endl;
}
Wilk::~Wilk(){
    std::cout << "destrukcja Wilka" << std::endl;
}

std::string Wilk::GetNazwa() {
    return "Wilk";
}
Organizm * Wilk::dziecko(int x, int y)
{
    Organizm * dziecko = new Wilk(this->swiat, x, y);
    return dziecko;
}