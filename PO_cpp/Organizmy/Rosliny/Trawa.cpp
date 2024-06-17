//
// Created by olgar on 24.04.2024.
//

#include <iostream>
#include "Trawa.h"
Trawa::Trawa(Swiat &swiat, int x, int y)
: Roslina(swiat, x, y, SILA_TRAWY, ',', PRAWDO_ZASIANIA_TRAWA)
{
    //std::cout << "stworzenie trawy" << std::endl;
}
Trawa::~Trawa(){
    //std::cout << "destrukcja Trawy" << std::endl;
}

std::string Trawa::GetNazwa() {
    return "Trawa";
}
Organizm* Trawa::dziecko(int x, int y){
    Organizm * dziecko = new Trawa(this->swiat, x, y);
    return dziecko;
}