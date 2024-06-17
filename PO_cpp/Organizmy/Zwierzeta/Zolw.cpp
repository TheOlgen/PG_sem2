//
// Created by olgar on 22.04.2024.
//
#include <iostream>
#include "Zolw.h"
Zolw::Zolw(Swiat &swiat, int x, int y)
        : Zwierze(swiat, x, y, INICJATYWA_ZOLWIA, SILA_ZOLWIA, 'Z')
{
    std::cout << "stworzenie Zolwia" << std::endl;
}
Zolw::~Zolw(){
    std::cout << "destrukcja Zolwia" << std::endl;
}

std::string Zolw::GetNazwa() {
    return "Zolw";
}
Organizm * Zolw::dziecko(int x, int y)
{
    Organizm * dziecko = new Zolw(this->swiat, x, y);
    return dziecko;
}
void Zolw::Akcja(char command)
{
    int px,py;
    if(!this->LosujPola(&px, &py) || rand()%4 != 0)
    {
        return;
    }
    if(!swiat.CzyPoleJestPuste(x+px, y+py))
    {
        if(Kolizja(swiat.dajOrganizmZPola(x+px, y+py)))
            this->RuszSie(px,py);
    }
    else
        this->RuszSie(px,py);
}
bool Zolw::Unik(Organizm* atakujacy, Organizm* zaatakowany)
{
    if(atakujacy->GetSila() < 5)
    {
        std::cout << "Zolw oslonil sie przed atakiem" << std::endl;
        return true;
    }
    return false;
}