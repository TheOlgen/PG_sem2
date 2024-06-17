//
// Created by olgar on 24.04.2024.
//

#include <iostream>
#include "Barszcz.h"
Barszcz::Barszcz(Swiat &swiat, int x, int y)
        : Roslina(swiat, x, y, SILA_BARSZCZU, '+', PRAWDO_ZASIANIA_BARSZCZU)
{
    //std::cout << "stworzenie Barszczu Sosnowskiego" << std::endl;
}
Barszcz::~Barszcz(){
    //std::cout << "destrukcja Barszczu sosnowskieho" << std::endl;
}

std::string Barszcz::GetNazwa() {
    return "Barszcz Sosnowskiego";
}
Organizm* Barszcz::dziecko(int x, int y){
    Organizm * dziecko = new Barszcz(this->swiat, x, y);
    return dziecko;
}
void Barszcz::Akcja(char command) {
    sprobujZasiac();
    zabijDookola(x+1, y+1);
    zabijDookola(x+1, y);
    zabijDookola(x+1, y-1);
    zabijDookola(x-1, y+1);
    zabijDookola(x-1, y);
    zabijDookola(x-1, y-1);
    zabijDookola(x, y+1);
    zabijDookola(x, y-1);
}

void Barszcz::zabijDookola(int x, int y) {
    if(swiat.CzyPoleJestPrawidlowe(x,y)){
        if(!swiat.CzyPoleJestPuste(x, y))
        {
            if(swiat.dajInicjatyweZOrganizmu(x,y)>0){
                swiat.dajOrganizmZPola(x,y)->Umrzyj(this);
            }
        }
    }

}
bool Barszcz::Kolizja(Organizm *atakujacy) {
    this->Umrzyj(atakujacy);
    std::cout << atakujacy->GetNazwa() <<  " zatrul sie Barszczem i umiera"<<std::endl;
    if(atakujacy->GetSymbol()=='@')
        swiat.zabijczlowieka();
    swiat.WyczyscPole(atakujacy->GetX(), atakujacy->GetY());
    return true;
}