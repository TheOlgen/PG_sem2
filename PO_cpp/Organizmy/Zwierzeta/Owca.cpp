//
// Created by olgar on 21.04.2024.
//

#include <iostream>
#include "Owca.h"
Owca::Owca(Swiat &swiat, int x, int y)
: Zwierze(swiat, x, y, INICJATYWA_OWCY, SILA_OWCY, 'O')
{
    std::cout << "stworzenie Owcy" << std::endl;
}
Owca::~Owca(){
    std::cout << "destrukcja Owcy" << std::endl;
}

std::string Owca::GetNazwa() {
    return "Owca";
}
Organizm * Owca::dziecko(int x, int y)
{
    Organizm * dziecko = new Owca(this->swiat, x, y);
    return dziecko;
}