//
// Created by olgar on 24.04.2024.
//

#include "Roslina.h"
Roslina::Roslina(Swiat &swiat, int x, int y, const int sila, const char symbol, double prawdoZasiania)
: Organizm(swiat, x, y, INICJATYWA_ROSLINY, sila, symbol), prawdoZasiania(prawdoZasiania)
{}
Roslina::~Roslina()
{}

double Roslina::GetPrawdoZasiania() const {
    return prawdoZasiania;
}

void Roslina::Akcja(char command) {
    sprobujZasiac();
}

bool Roslina::sprobujZasiac() {
    int px,py;
    if(!this->LosujPola(&px, &py) || rand() %prawdoZasiania > 0)
    {
        return false;
    }
    if(swiat.CzyPoleJestPuste(x+px, y+py))
    {
        this->dziecko(x+px, y+py);
        return true;
    }
    return false;
}

bool Roslina::Kolizja(Organizm *atakujacy) {
    this->Umrzyj(atakujacy);
    return true;
}

std::string Roslina::GetNazwa() {
    return "Roslina";
}

bool Roslina::Unik(Organizm *atakujacy, Organizm *zaatakowany) {
    return false;
}

void Roslina::ZrobDzieci(const int &x, const int &y) {
    //nic
}

Organizm *Roslina::dziecko(int x, int y) {
    return nullptr;
}
