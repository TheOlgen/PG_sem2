//
// Created by olgar on 24.04.2024.
//

#include <iostream>
#include "WilczaJagoda.h"
WilczaJagoda::WilczaJagoda(Swiat &swiat, int x, int y)
        : Roslina(swiat, x, y, SILA_JAGODY, '*', PRAWDO_ZASIANIA_JAGODY)
{
    //std::cout << "stworzenie WilczaJagoda" << std::endl;
}
WilczaJagoda::~WilczaJagoda(){
    //std::cout << "destrukcja WilczaJagoda" << std::endl;
}

std::string WilczaJagoda::GetNazwa() {
    return "Jagody Wilcze";
}
Organizm* WilczaJagoda::dziecko(int x, int y){
    Organizm * dziecko = new WilczaJagoda(this->swiat, x, y);
    return dziecko;
}
bool WilczaJagoda::Kolizja(Organizm *atakujacy) {
    this->Umrzyj(atakujacy);
    std::cout << atakujacy->GetNazwa() <<  " zatrul sie jagodami i umiera"<<std::endl;
    if(atakujacy->GetSymbol()=='@')
        swiat.zabijczlowieka();
    swiat.WyczyscPole(atakujacy->GetX(), atakujacy->GetY());
    return true;
}