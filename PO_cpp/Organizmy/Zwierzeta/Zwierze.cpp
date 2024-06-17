//
// Created by olgar on 18.04.2024.
//

#include <iostream>
#include "Zwierze.h"
Zwierze::Zwierze(Swiat &swiat, int x, int y, const int inicjatywa,
                 const int sila, const char symbol)
        : Organizm(swiat, x, y, inicjatywa, sila, symbol)
{}

void Zwierze::Akcja(char command)
{
    int px,py;
    if(!this->LosujPola(&px, &py))
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

bool Zwierze::Kolizja(Organizm *zaatakowany)
{
    if(zaatakowany == NULL){
        return true;
    }
    if(this->CzyTenSamGatunek(zaatakowany))
    {
        std::cout << "Hormony szaleja! ";
        this->ZrobDzieci(x,y);
        return false;
    }
    if(zaatakowany->GetInicjatywa() == 0)
        return zaatakowany->Kolizja(this);
    return this->Walka(zaatakowany);
}
bool Zwierze::Walka(Organizm *zaatakowany)
{
    std::cout << this->GetNazwa() << " spotyka " << zaatakowany->GetNazwa()<< ", zaraz bedzie krwawa walka" << std::endl;
    if(this->Unik( zaatakowany, this)){
        return false;
    }
    if(zaatakowany->Unik(this, zaatakowany)){
        return false;
    }
    if(zaatakowany->GetSila()>this->sila)
    {
        this->Umrzyj(zaatakowany);
        return false;
    }
    else
    {
        zaatakowany->Umrzyj(this);
    }
    return true;
}

bool Zwierze::Unik(Organizm* atakujacy, Organizm* zaatakowany)
{
    return false;
}
void Zwierze::ZrobDzieci(const int &x, const int &y)
{
    int px,py, licznik=0;
    while(!LosujPola(&px, &py) || !swiat.CzyPoleJestPuste(x+px, y+py))
    {
        licznik+=1;
        if(licznik==6)
        {
            py =0;
            px =0;
            break;
        }
        //5continue;
    }
    std::cout << this->GetNazwa() << " plodzi i rodzi dziecko" << std::endl;
    Organizm *dzieciak = this->dziecko(x+px, y+py) ;
}
std::string Zwierze::GetNazwa()
{
    return "Zwierze";
}