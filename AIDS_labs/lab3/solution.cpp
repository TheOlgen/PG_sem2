#include <iostream>


using namespace std;


void quicksort(int packages[15][2], double indexes[15], int first, int last)
{
    if (first >= last)
    {
        return;
    }
    int p = first, q = last;

    p--;
    q++;
    double numb = indexes[(first + last) / 2];
    while (true)
    {
        while (numb > indexes[++p]);
        while (indexes[--q] > numb);
        if (p <= q)
        {
            int x[] = { packages[p][0], packages[p][1] };
            double y = indexes[p];
            packages[p][0] = packages[q][0];
            packages[p][1] = packages[q][1];
            indexes[p] = indexes[q];
            packages[q][0] = x[0];
            packages[q][1] = x[1];
            indexes[q] = y;
        }
        else
            break;
    }

    if (q > first)
    {
        quicksort(packages, indexes, first, q);
    }

    if (p < last)
    {
        quicksort(packages, indexes, p, last);
    }
}

int calculateProfit(int packages[15][2], int ile_przedmiotow, int maxmasa)
{
    int n = pow(2, ile_przedmiotow), profit=0;

    for (int j = 0; j < n; j++)
    {
        int waga = 0;
        int suma_wyplaty = 0;
        for (int k = 0; k < ile_przedmiotow; k++)
        {
            if (j & (1 << k))
            {
                waga += packages[k][1];
                suma_wyplaty += packages[k][0];
            }
        }
        if (waga <= maxmasa)
        {
            if (profit < suma_wyplaty) {
                profit = suma_wyplaty;
            }
        }
    }
    return profit;
}


int main()
{
    for (int j = 0; j < 500; j++)
    {
        int n, maxmasa;
        cin >> n;

        int packages[15][2];
        double indexes[15];

        for (int i = 0; i < n; i++)
        {
            cin >> packages[i][0];      //ceny przedmiotów
        }
        for (int i = 0; i < n; i++)
        {
            cin >> packages[i][1];      //wagi przedmiotów
            indexes[i] = (double)packages[i][0] / (double)packages[i][1];   //index wartości    cena/waga
        }

        cin >> maxmasa;
        quicksort(packages, indexes, 0, n - 1);
        cout << calculateProfit(packages, n, maxmasa) << endl;

    }
}
