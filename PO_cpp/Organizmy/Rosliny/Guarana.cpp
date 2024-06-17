//
// Created by olgar on 24.04.2024.
//

#include <iostream>
#include "Guarana.h"
Guarana::Guarana(Swiat &swiat, int x, int y)
        : Roslina(swiat, x, y, SILA_GUARANY, '^', PRAWDO_ZASIANIA_GUARANY)
{
    //std::cout << "stworzenie Guarany" << std::endl;
}
Guarana::~Guarana(){
    //std::cout << "destrukcja Trawy" << std::endl;
}

std::string Guarana::GetNazwa() {
    return "Guarana";
}
Organizm* Guarana::dziecko(int x, int y){
    Organizm * dziecko = new Guarana(this->swiat, x, y);
    return dziecko;
}
bool Guarana::Kolizja(Organizm *atakujacy) {
    this->Umrzyj(atakujacy);
    atakujacy->SetSila(3);
    std::cout << atakujacy->GetNazwa() << " ma teraz sile rowna: " << atakujacy->GetSila() << std::endl;
    return true;
}