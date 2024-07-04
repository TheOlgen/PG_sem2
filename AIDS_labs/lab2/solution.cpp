#include <iostream>
#include <string>

using namespace std;


bool compareStrings(string& x, string& y) // true jesli a>b false jeśli a<b
{
        if (x.length() > y.length())
                return true;
        else if (x.length() < y.length())
                return false;
        else
        {
                for (int i = 0; i < x.length(); i++)
                {
                        if (x[i] > y[i]) return true;
                        if (x[i] < y[i]) return false;
                }
        }
        return false;
}

void quicksort(string* numbers, int first, int last)
{
        if (first >= last)
        {
                return;
        }
        int p = first, q = last;

        p--;
        q++;
        string numb = numbers[(first + last) / 2];
        while (true)
        {
                while (compareStrings(numb, numbers[++p]));
                while (compareStrings(numbers[--q], numb));
                if (p <= q)
                {
                        string x = numbers[p];
                        numbers[p] = numbers[q];
                        numbers[q] = x;
                }
                else
                        break;
        }

        if (q > first)
        {
                quicksort(numbers, first, q);
        }
                
        if (p < last)
        {
        quicksort(numbers, p, last);
        }
                
}


int main()
{
        int n;
        cin >> n;
        string* numbers = new string[n];

        for (int i = 0; i < n; i++)
        {
                cin >> numbers[i];
        }

        quicksort(numbers, 0, n - 1);

        for (int i = 0; i < n; i++)
        {
                cout << numbers[i] << endl;
        }
        delete[] numbers;
}
