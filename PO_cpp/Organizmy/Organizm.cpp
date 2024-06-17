//
// Created by olgar on 18.04.2024.
//
#include <iostream>
#include "Organizm.h"


Organizm::Organizm(Swiat &swiat, int x, int y, const int inicjatywa,
                   const int sila, const char symbol)
        : swiat(swiat), x(x), y(y), sila(sila), inicjatywa(inicjatywa),
          symbol(symbol), zyje(true)
{
    swiat.dodajOrganizm(this);
}
Organizm::~Organizm()
{
    //std::cout << "zniszczenie oragnizmu bez nazwy" << std::endl;
}
void Organizm::Naysowanie()
{
    //TODO
    std::cout << '[' << this->symbol << ']';
}
int Organizm::GetX() const
{
    return x;
}
int Organizm::GetY() const
{
    return y;
}
void Organizm::SetPozycja(const int x, const int y)
{
    this->x = x;
    this->y = y;
}
void Organizm::SetSila(int dodajsile) {
    this->sila += dodajsile;
}
int Organizm::GetInicjatywa() const
{
    return inicjatywa;
}
char Organizm::GetSymbol()
{
    return symbol;
}
int Organizm::GetSila() const
{
    return sila;
}
bool Organizm::CzyZywy() const
{
    return zyje;
}
bool Organizm::CzyTenSamGatunek(Organizm *drugi)
{
    return (this->symbol == drugi->symbol);
}
void Organizm::Umrzyj(Organizm * zabijajacy)
{
    zyje=false;
    if(this->symbol != ',' && this->symbol != '.')
        std::cout << zabijajacy->GetNazwa() << " Zjada "<< this->GetNazwa() << std::endl;
    swiat.WyczyscPole(this->x, this->y);
}
bool Organizm::LosujPola(int *px, int* py)
{
    *px = rand()%3 - 1;
    if (*px != 0)
        *py = rand()%3 - 1;
    else
    {
        if(rand()%2 == 0)
            *py = -1;
        else
            *py = 1;
    }
    //std::cout << *px << " " << *py << std::endl;
    if (swiat.CzyPoleJestPrawidlowe(x + *px, y + *py))
    {
        return true;
    }
    return false;
}
void Organizm::RuszSie(int px, int py)
{
    swiat.ZmienPozycje(this->x, this->y, px, py);
    this->SetPozycja(x+px, y+py);
}
