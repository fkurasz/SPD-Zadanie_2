/* Zadanie_2.cpp

    Filip Kurasz 249458
    Sterowanie Procesami Dyskretnymi

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <ctime>
#include "Dane.h"

using namespace std;

// usun z vectora o numerze indeksu
void remove_from_vec(vector<Dane>& rhs, int index)
{
    vector<Dane> temp;
    for (int i = 0; i < rhs.size(); i++)
    {
        if (i == index)
            continue;
        temp.push_back(rhs.at(i));
    }
    rhs = temp;
}

// kolejnosc elementow
void order(vector<Dane>& W, Dane e)
{
    int count = 0;
    // zlicz ilosc tych samych elementow
    for (int i = 0; i < W.size(); i++)
    {
        if (e.getIndex() == W.at(i).getIndex())
            count++;
    }
    // jesli mamy wiecej niz 1 ten sam element
    if (count > 1)
    {
        for (int i = 0; i < W.size(); i++)
        {
            if (e.getIndex() == W.at(i).getIndex())
            {
                // to usun pierwszy
                remove_from_vec(W, i);
                break;
            }
        }
    }
}

// oblicza Kare na podstawie kolejnoœci
int penalty(vector<Dane>& W)
{
    int t = 0;
    int penalty = 0;

    for (int i = 0; i < W.size(); i++)
    {
        //wykonanie na maszynie i zwiekszenie czasu
        t += W.at(i).getP();
        //jesli sie spoznimy, to dolicz kare
        if (W.at(i).getD() < t)
            penalty += W.at(i).getW() * (t - W.at(i).getD());
    }

    return penalty;
}

// dodaje 7 elementow ze slajdu
void add(vector<vector<Dane>>& n)
{
    vector<Dane> temp;
    temp.push_back(Dane(2, 3, 4, 1));
    temp.push_back(Dane(4, 3, 3, 2));
    temp.push_back(Dane(1, 4, 5, 3));
    temp.push_back(Dane(3, 2, 2, 4));

    n.push_back(temp);
}
// dodaje dane z pliku
void addFromFile(string path, vector<vector<Dane>>& n)
{
    ifstream file(path);
    string discard;
    

    int amount = 0;
    int p = 0;
    int w = 0;
    int d = 0;


    while (!file.eof())
    {
        while (getline(file, discard))
        {
            if (discard[0] != 'd')
                continue;
            else
                break;
        }

        if (file >> amount)
        {
            vector<Dane> temp_vec;
            for (int i = 0; i < amount; i++)
            {
                file >> p >> w >> d;
                temp_vec.push_back(Dane(p, w, d, i + 1));
            }
            n.push_back(temp_vec);
        }
        else
        {
            //file nie wczytal danych lub dane sa bledne (czyszczenie strumienia i porzucenie znakow)
            //np. dla napisu "data.1" w pliku 
            file.clear();
            file.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    file.close();
}

//pokazuje wczytane dane
void showData(vector<vector<Dane>>& n)
{
    for (int i = 0; i < n.size(); i++)
    {
        cout << n[i].size() << endl;
        for (int j = 0; j < n[i].size(); j++)
        {
            cout << n[i].at(j).getP() << " " << n[i].at(j).getW() << " " << n[i].at(j).getD() << endl;
        }
        cout << endl;
    }
}

int main()
{
    int C = 0;

    vector<vector<Dane>> N_vec;
    //wczytanie danych
    addFromFile("data.txt", N_vec);
    //add(N_vec);
    //showData(N_vec);


    // N = 2^n mozliwosc 
    for (int i = 0; i < N_vec.size(); i++)
    {
        int N = 1 << N_vec.at(i).size();
        int* F = new int[N];
        F[0] = 0;
        // od 1 do 2^N
        for (int bit = 1; bit < N; bit++)  // 0001 / 0010 // 0011 // 0100 // 0101 // 0110 // 0111 // 1000
        {
            C = 0;
            for (int j = 0, b = 1; j < N_vec.at(i).size(); j++, b *= 2)
            {
                // jesli bit z b jest takze 1 tak jak bit ze zmiennej bit
                if (bit & b)
                {
                    C += N_vec.at(i).at(j).getP();
                }
            }

            F[bit] = 999999;
            for (int k = 0, b = 1; k < N_vec.at(i).size(); k++, b *= 2)
            {
                if (bit & b)
                {
                    F[bit] = std::min(F[bit], F[bit - b] + N_vec.at(i).at(k).getW() * std::max(C - N_vec.at(i).at(k).getD() , 0));
                }
            }
        }
        cout << "Optymalne: " << F[N - 1] << endl;
        delete [] F;
    }
}

