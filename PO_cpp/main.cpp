#include <iostream>
#include "Swiat.h"
#include "Organizmy/Zwierzeta/Owca.h"
#include "Organizmy/Zwierzeta/Wilk.h"
#include "Organizmy/Zwierzeta/Antylopa.h"
#include "Organizmy/Zwierzeta/Lis.h"
#include "Organizmy/Zwierzeta/Zolw.h"
#include "Organizmy/Zwierzeta/Czlowiek.h"
#include "Organizmy/Rosliny/Trawa.h"
#include "Organizmy/Rosliny/Mlecz.h"
#include "Organizmy/Rosliny/Guarana.h"
#include "Organizmy/Rosliny/WilczaJagoda.h"
#include "Organizmy/Rosliny/Barszcz.h"

using namespace std;

int main() {
    int wys, szer;
    char c;
    cout << "1. rozpocznij nowa gre" << endl << "2. wczytaj gre z pliku"<< endl;
    cin >> c;
    if(c == '1') {
        cout << "Napisz wymiary twojej planszy" << endl;
        cin >> wys >> szer;
    }
    else{
        FILE * slot;
        slot= fopen("C:\\Users\\olgar\\CLionProjects\\untitled1\\slot1.txt", "r");
        if (slot == nullptr) {
            std::cerr << "Błąd otwierania pliku." << std::endl;
            return 0;
        }
        fscanf(slot, "%d %d\n", &szer, &wys);
        cout <<wys << " " << szer;
        fclose(slot);
    }
        Swiat s(wys,szer);

    if(c == '1'){
        int x = 0, y = 0;
        Organizm* o1 = new Czlowiek(s, x, y);
        Organizm* o2 = new Zolw(s, x, y);
        Organizm* o3 = new Zolw(s, x, y);
        Organizm* o4 = new Antylopa(s, x, y);
        Organizm* o5 = new Antylopa(s, x, y);
        Organizm* o6 = new Antylopa(s, x, y);
        Organizm* o7 = new Antylopa(s, x, y);
        Organizm* o8 = new Wilk(s, x, y);
        Organizm* o9 = new Wilk(s, x, y);
        Organizm* o10 = new Wilk(s, x, y);
        Organizm* o11 = new Lis(s, x, y);
        Organizm* o12 = new Lis(s, x, y);
        Organizm* o13 = new Lis(s, x, y);
        Organizm* o14 = new Lis(s, x, y);
        Organizm* o15 = new Owca(s, x, y);
        Organizm* o16 = new Owca(s, x, y);
        Organizm* o17 = new Owca(s, x, y);
        Organizm* o18 = new Owca(s, x, y);
        Organizm* o19 = new Barszcz(s, x, y);
        Organizm* o20 = new Guarana(s, x, y);
        Organizm* o21 = new Mlecz(s, x, y);
        Organizm* o22 = new Trawa(s, x, y);
        Organizm* o23 = new WilczaJagoda(s, x, y);
    }
    else{
        int ile, x, y, sila;
        char nazwa[20];
        FILE * slot;
        slot= fopen("C:\\Users\\olgar\\CLionProjects\\untitled1\\slot1.txt", "r");
        if (slot == nullptr) {
            std::cerr << "Błąd otwierania pliku." << std::endl;
            return 0;
        }
        fscanf(slot, "%d \n", &ile);
        for(int i =0; i<ile; i++)
        {
            fscanf(slot, "%s %d %d %d\n", nazwa, &x, &y, &sila);
            if(nazwa[0] == 'C'){
                Czlowiek* o = new Czlowiek(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'W'){
                Wilk* o = new Wilk(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'Z'){
                Zolw* o = new Zolw(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'A'){
                Antylopa* o = new Antylopa(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'L'){
                Lis* o = new Lis(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'B'){
                Barszcz* o = new Barszcz(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'G'){
                Guarana* o = new Guarana(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'J'){
                WilczaJagoda* o = new WilczaJagoda(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'T'){
                Trawa* o = new Trawa(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
            if(nazwa[0] == 'M'){
                Mlecz* o = new Mlecz(s, x, y);
                o->SetSila(sila - o->GetSila());
            }
        }
        fclose(slot);
    }


    char command='w';//startowe ulożenie
    while(command!='q')
    {
        s.wykonajTure(&command);
        if(command=='q') break;
        std::cin >> command;
    }
    cout << "Twoj czlowiek umarl, PRZEGRALES" << endl;
    s.wyczyscPamiec();
    return 0;
}
