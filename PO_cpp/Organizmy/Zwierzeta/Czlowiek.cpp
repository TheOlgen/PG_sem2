//
// Created by olgar on 23.04.2024.
//
#include <iostream>
#include "Czlowiek.h"
#include <Windows.h>
Czlowiek::Czlowiek(Swiat &swiat, int x, int y)
        :Zwierze(swiat, x, y, INICJATYWA_CZLOWIEKA, SILA_CZLOWIEKA, '@')
{
    std::cout << "stworzenie Czlowieka" << std::endl;
    this->silaNormalna = SILA_CZLOWIEKA;
    licznikTury = 0;
}
Czlowiek::~Czlowiek()
{
    std::cout << "destrukcja Czlowieka" << std::endl;
}

std::string Czlowiek::GetNazwa() {
    return "Czlowiek";
}
void Czlowiek::Akcja(char command)
{
    int px,py;
    if(!this->WybierzPola(&px, &py, command))
    {
        return;
    }
    if(sila > silaNormalna){
        sila -= 1;
        std::cout << "Supermoc dziala, aktualna sila: " << sila <<
        " bedziesz mogl kolejny raz uzyc supermocy po rundzie: "<<  licznikTury << std::endl;
    }
    if(!swiat.CzyPoleJestPuste(x+px, y+py))
    {
        if(Kolizja(swiat.dajOrganizmZPola(x+px, y+py)))
            this->RuszSie(px,py);
    }
    else
        this->RuszSie(px,py);
}
void Czlowiek::SetSila(int dodajsile) {
    this->sila += dodajsile;
    this->silaNormalna += dodajsile;
}
bool Czlowiek::WybierzPola(int *px, int *py, char command)
{
    switch(command)
    {
        case 'a' : //key_down:
            *px=-1;
            *py=0;
            break;

        case 's' : //key_down:
            *px=0;
            *py=1;
            break;

        case 'd' : //key_down:
            *px=1;
            *py=0;
            break;

        case 'w' : //key_down:
            *px=0;
            *py=-1;
            break;

        case 'n':
            supermoc();
            break;

        case 'z':
            swiat.zapiszDoPliku();
            break;
    }
    if (swiat.CzyPoleJestPrawidlowe(x + *px, y + *py))
    {
        return true;
    }
    return false;
}

void Czlowiek::supermoc() {
    if(swiat.getTura() < licznikTury){
        std::cout << "Jeszcze nie mozesz odblokowac supermocy"<< std::endl;
    }
    else{
        this->sila += 11;
        this->licznikTury = swiat.getTura() + 5;
    }
}
bool Czlowiek::Unik(Organizm* atakujacy, Organizm* zaatakowany)
{
    return false;
}
Organizm * Czlowiek::dziecko(int x, int y)
{
    Organizm * dziecko = new Czlowiek(this->swiat, x, y);
    return dziecko;
}
void Czlowiek::Umrzyj(Organizm * zabijajacy)
{
    zyje=false;
    std::cout << zabijajacy->GetNazwa() << " Zjada "<< this->GetNazwa() << std::endl;
    swiat.WyczyscPole(this->x, this->y);
    swiat.zabijczlowieka();
}