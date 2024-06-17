//
// Created by olgar on 22.04.2024.
//

#include <iostream>
#include "Antylopa.h"

Antylopa::Antylopa(Swiat &swiat, int x, int y)
:Zwierze(swiat, x, y, INICJATYWA_ANTYLOPY, SILA_ANTYLOPY, 'A')
{
    std::cout << "stworzenie Antylopy" << std::endl;
}
Antylopa::~Antylopa()
{
    std::cout << "destrukcja Antylopy" << std::endl;
}

std::string Antylopa::GetNazwa() {
    return "Antylopa";
}

bool Antylopa::LosujPola(int *px, int *py)
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
    if (swiat.CzyPoleJestPrawidlowe(x + (*px)*2, y + (*py)*2))
    {
        *px *=2;
        *py *=2;
        return true;
    }
    else if (swiat.CzyPoleJestPrawidlowe(x + *px, y + *py))
    {
        return true;
    }
    return false;
}

bool Antylopa::Unik(Organizm* atakujacy, Organizm* zaatakowany)
{
    if(zaatakowany->GetSymbol() == 'A') {
        if (rand() % 2 == 0) {
            std::cout << "Antylopa ucieka przed atakiem" << std::endl;
            int py, px;
            zaatakowany->LosujPola(&px, &py);
            zaatakowany->RuszSie(px, py);
            return true;
        }
    }
    return false;
}
Organizm * Antylopa::dziecko(int x, int y)
{
    Organizm * dziecko = new Antylopa(this->swiat, x, y);
    return dziecko;
}