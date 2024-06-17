//
// Created by olgar on 24.04.2024.
//

#include "Mlecz.h"
Mlecz::Mlecz(Swiat &swiat, int x, int y)
        : Roslina(swiat, x, y, SILA_MLECZA, '.', PRAWDO_ZASIANIA_MLECZ)
{
    //std::cout << "stworzenie trawy" << std::endl;
}
Mlecz::~Mlecz(){
    //std::cout << "destrukcja Trawy" << std::endl;
}

std::string Mlecz::GetNazwa() {
    return "Mlecz";
}
Organizm* Mlecz::dziecko(int x, int y){
    Organizm * dziecko = new Mlecz(this->swiat, x, y);
    return dziecko;
}
void Mlecz::Akcja(char command) {
    sprobujZasiac();
    sprobujZasiac();
    sprobujZasiac();
}
