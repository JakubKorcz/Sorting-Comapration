#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>

using namespace std;

void wypisywanie(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << tab[i] << " ";
    }
    cout << endl;
}

void dopisywanie(int n, int* czas, int* il_com, int* il_swa,int il)
{
    string p = "; ";
    fstream plik;
    plik.open("plik.txt", ios::app);
    if (plik.good() == true)
    {
        plik << n << p;
        for (int i = 0; i < il; i++)
        {
            plik << czas[i] << p << il_com[i] << p << il_swa[i] << p;
        }
        plik << endl;
    }
    else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
    plik.close();
}

void przerwa_w_pliku() 
{
    fstream plik;
    plik.open("plik.txt", ios::app);
    if (plik.good() == true)
        plik << endl;
    plik.close();
}

void swap(int* tab, int a, int b)
{
    int pom = tab[a];
    tab[a] = tab[b];
    tab[b] = pom;
}

void kopiowanie(int* tab, int n, int* tab1, int* tab2, int* tab3, int* tab4, int* tab5, int* tab6)
{
    for (int i = 0; i < n; i++)
    {
        tab1[i] = tab[i];
        tab2[i] = tab[i];
        tab3[i] = tab[i];
        tab4[i] = tab[i];
        tab5[i] = tab[i];
        tab6[i] = tab[i];
    }
}

void bubblesort(int* tab, int n, int* wskcom, int* wskswa)
{
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            a++;
            if (tab[j] > tab[j + 1])
            {
                b++;
                swap(tab, j, j + 1);
            }
        }
    }
    *wskcom = a;
    *wskswa = b;
}

void selectionsort(int* tab, int n, int* wskcom, int* wskswa)
{
    int a = 0, b = 0;
    for (int i = 0; i < n; i++)
    {
        int min = tab[i];
        int p = i;
        for (int j = i; j < n; j++)
        {
            a++;
            if (min > tab[j])
            {
                min = tab[j];
                p = j;  //wskaźnik miejsca najmniejszego elementu
            }
        }
        b++;
        swap(tab, i, p);
    }
    *wskcom = a;
    *wskswa = b;
}

void insertionsort(int* tab, int n, int* wskcom, int* wskswa) {
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        int j = i; //wskaźnik na miejsce które jest analizowne
        while (j >= 0 && tab[j - 1] > tab[j]) {
            b++; a++;
            swap(tab, j, j - 1);
            j--;
        }
        a++;
    }
    *wskcom = a;

}

int partycjaqs(int* tab, int l, int r, int* wskcom, int* wskswa)
{
    int a = *wskcom; int b = *wskswa;
    int pivot = tab[r]; //pivot od prawej strony
    int i = l - 1;

    for(int j=l;j<r;j++)
    {
        a++;
        if(tab[j]<pivot)
        {
            i++;
            b++;
            swap(tab, i, j);
        }
    }
    b++;
    swap(tab, i + 1, r);
    
    *wskcom = a; *wskswa = b;
    return i + 1;
}

void quicksort(int* tab, int l, int r, int* wskcom, int* wskswa) 
{
    if (l < r)
    {
        int pivot = partycjaqs(tab, l, r, wskcom, wskswa);
    
        quicksort(tab, l, pivot - 1,wskcom,wskswa);
        quicksort(tab, pivot + 1, r, wskcom, wskswa);
    }
}

void merge(int* tab, int l, int m, int r, int* wskcom)
{
    int a = *wskcom;
    int* pom;
    pom = new int[r + 1];       //Tablica pomocnicza

    for (int i = 0; i <= r; i++)
    {
        pom[i] = tab[i];        //Przepisanie kazdego elementu z tab do pom
    }
    int current = l;
    int wsk1 = l;
    int wsk2 = m + 1;

    while (wsk1 <= m && wsk2 <= r)
    {
        if (pom[wsk1] < pom[wsk2])
        {
            tab[current] = pom[wsk1];
            wsk1++;
        }
        else
        {
            tab[current] = pom[wsk2];
            wsk2++;
        }
        current++;
        a++;
    }
    while (wsk1 <= m)
    {
        tab[current] = pom[wsk1];
        wsk1++;
        current++;
    }
    *wskcom = a;
    delete[] pom;
}

void mergesort(int* tab, int l, int r, int* wskcom)
{
    if (l < r)
    {
        int half = l + (r - l) / 2;

        mergesort(tab, l, half, wskcom);
        mergesort(tab, half + 1, r, wskcom);
        merge(tab, l, half, r, wskcom);
    }
}

void kopcuj(int* tab, int n, int rod, int* wskcom, int* wskswa)
{
    int a = *wskcom; int b = *wskswa;
    int max = rod;
    int lchild = rod * 2 + 1;
    int rchild = rod * 2 + 2;
    a++;
    if (lchild<n && tab[lchild]>tab[max])
    {
        max = lchild;
    }
    a++;
    if (rchild<n && tab[rchild]>tab[max])
    {
        max = rchild;
    }
    a++;
    if (max != rod)
    {
        b++;
        swap(tab, max, rod);
        *wskcom = a;
        *wskswa = b;
        kopcuj(tab, n, max, wskcom, wskswa);
    }
}

void heapsort(int* tab, int n, int* wskcom, int* wskswa)
{
    int najmrodzic = n / 2 - 1;
    for (int i = najmrodzic; i >= 0; i--)
    {
        kopcuj(tab, n, i, wskcom, wskswa);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(tab, 0, i);
        kopcuj(tab, --n, 0, wskcom, wskswa);
    }
}

void playmaker(int* tab, int n)
{
    int il_com[6] = { 0 };         //ilość porównań
    int il_swa[6] = { 0 };         //ilość zamian
    int czas[6] = { 0 };
    int il = 6;

    int* tab1, * tab2, * tab3, * tab4, * tab5, * tab6;

    tab1 = new int[n];
    tab2 = new int[n];
    tab3 = new int[n];
    tab4 = new int[n];
    tab5 = new int[n];
    tab6 = new int[n];

    kopiowanie(tab, n, tab1, tab2, tab3, tab4, tab5, tab6);

    auto begin = chrono::high_resolution_clock::now();
    bubblesort(tab1, n, &il_com[0], &il_swa[0]);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    czas[0] = elapsed.count();

    auto begin1 = chrono::high_resolution_clock::now();
    selectionsort(tab2, n, &il_com[1], &il_swa[1]);
    auto end1 = chrono::high_resolution_clock::now();
    auto elapsed1 = chrono::duration_cast<chrono::nanoseconds>(end1 - begin1);
    czas[1] = elapsed1.count();

    auto begin2 = chrono::high_resolution_clock::now();
    insertionsort(tab3, n, &il_com[2], &il_swa[2]);
    auto end2 = chrono::high_resolution_clock::now();
    auto elapsed2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    czas[2] = elapsed2.count();

    auto begin3 = chrono::high_resolution_clock::now();
    heapsort(tab4, n, &il_com[3], &il_swa[3]);
    auto end3 = chrono::high_resolution_clock::now();
    auto elapsed3 = chrono::duration_cast<chrono::nanoseconds>(end3 - begin3);
    czas[3] = elapsed3.count();

    auto begin4 = chrono::high_resolution_clock::now();
    //quicksort(tab5, 0, n - 1, &il_com[4], &il_swa[4]);
    auto end4 = chrono::high_resolution_clock::now();
    auto elapsed4 = chrono::duration_cast<chrono::nanoseconds>(end4 - begin4);
    czas[4] = elapsed4.count();

    auto begin5 = chrono::high_resolution_clock::now();
    mergesort(tab6, 0, n - 1, &il_com[5]);
    auto end5 = chrono::high_resolution_clock::now();
    auto elapsed5 = chrono::duration_cast<chrono::nanoseconds>(end5 - begin5);
    czas[5] = elapsed5.count();

    delete[] tab1;
    delete[] tab2;
    delete[] tab3;
    delete[] tab4;
    delete[] tab5;
    delete[] tab6;

    il_swa[5] = 0;
    dopisywanie(n, czas, il_com, il_swa,il);
}

void losowatablica(int* tab, int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % 10000;
    }
}

void tablicarosnaca(int* tab, int n)
{
    int a;
    losowatablica(tab, n);
    mergesort(tab, 0, n - 1, &a);
}

void tablicamalejaca(int* tab, int n)
{
    tablicarosnaca(tab, n);
    for(int i=0;i<n/2;i++)
    {
        swap(tab,i,n-1-i);
    }
}

void tablicaA(int *tab,int n)
{
    tablicarosnaca(tab, n);
    int* tab1;
    tab1 = new int[n];

    for(int i=0;i<n;i=i+2)
    {
        int a = i / 2;
        tab1[a] = tab[i];
        if (i + 1 < n) {
            tab1[n - a - 1] = tab[i + 1];
        }
    }
    for(int i=0;i<n;i++)
    {
        tab[i] = tab1[i];
    }
}

void tablicaV(int* tab, int n)
{
    tablicamalejaca(tab, n);
    int* tab1;
    tab1 = new int[n];

    for (int i = 0; i < n; i = i + 2)
    {
        int a = i / 2;
        tab1[a] = tab[i];
        if (i + 1 < n) {
            tab1[n - a - 1] = tab[i + 1];
        }
    }
    for (int i = 0; i < n; i++)
    {
        tab[i] = tab1[i];
    }
}

void bbspom(int* czas, int* a, int* b,int *tab,int i,int pom)
{
    auto begin = chrono::high_resolution_clock::now();
    bubblesort(tab, i, &a[pom], &b[pom]);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    czas[pom] = elapsed.count();
}

void sspom(int* czas, int* a, int* b, int* tab, int i, int pom)
{
    auto begin = chrono::high_resolution_clock::now();
    selectionsort(tab, i, &a[pom], &b[pom]);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    czas[pom] = elapsed.count();
}

void ispom(int* czas, int* a, int* b, int* tab, int i, int pom)
{
    auto begin = chrono::high_resolution_clock::now();
    insertionsort(tab, i, &a[pom], &b[pom]);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    czas[pom] = elapsed.count();
}

void hspom(int* czas, int* a, int* b, int* tab, int i, int pom)
{
    auto begin = chrono::high_resolution_clock::now();
    heapsort(tab, i, &a[pom], &b[pom]);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    czas[pom] = elapsed.count();
}

void qspom(int* czas, int* a, int* b, int* tab, int i, int pom)
{
    auto begin = chrono::high_resolution_clock::now();
    //quicksort(tab, 0,i-1);//, &a[pom], &b[pom]
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    czas[pom] = elapsed.count();
}

void mspom(int* czas, int* a, int* tab, int i, int pom)
{
    auto begin = chrono::high_resolution_clock::now();
    mergesort(tab, 0,i-1, &a[pom]);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    czas[pom] = elapsed.count();
}

int main()
{
    int* tab;
    int czas[5];
    int a[5];
    int b[5]={0};

    //wykres1 bubblesort
        for (int i = 1000; i <= 10000; i = i + 1000)
        {
            tab = new int[i];
            int pom = 0;

            tablicarosnaca(tab, i);
            bbspom(czas, a, b, tab, i, pom);
            pom++;

            tablicamalejaca(tab, i);
            bbspom(czas, a, b, tab, i, pom);
            pom++;

            losowatablica(tab, i);
            bbspom(czas, a, b, tab, i, pom);
            pom++;

            tablicaA(tab, i);
            bbspom(czas, a, b, tab, i, pom);
            pom++;

            tablicaV(tab, i);
            bbspom(czas, a, b, tab, i, pom);
            pom = 0;
            
            dopisywanie(i, czas, a, b, 5);
            delete[] tab;
            cout << "Wykres1.1 bubblesort" << endl;
        }  
    przerwa_w_pliku();
    //wykres2 selectionsort
    for (int i = 1000; i <= 10000; i = i + 1000)
    {
        tab = new int[i];
        int pom = 0;

        tablicarosnaca(tab, i);
        sspom(czas, a, b, tab, i, pom);
        pom++;

        tablicamalejaca(tab, i);
        sspom(czas, a, b, tab, i, pom);
        pom++;

        losowatablica(tab, i);
        sspom(czas, a, b, tab, i, pom);
        pom++;

        tablicaA(tab, i);
        sspom(czas, a, b, tab, i, pom);
        pom++;

        tablicaV(tab, i);
        sspom(czas, a, b, tab, i, pom);

        dopisywanie(i, czas, a, b, 5);
        delete[] tab;
        cout << "Wykres1.2 selectionesort" << endl;
    }
    przerwa_w_pliku();
    //wykres3 insertionsort
    for (int i = 1000; i <= 10000; i = i + 1000)
    {
        tab = new int[i];
        int pom = 0;

        tablicarosnaca(tab, i);
        ispom(czas, a, b, tab, i, pom);
        pom++;

        tablicamalejaca(tab, i);
        ispom(czas, a, b, tab, i, pom);
        pom++;

        losowatablica(tab, i);
        ispom(czas, a, b, tab, i, pom);
        pom++;

        tablicaA(tab, i);
        ispom(czas, a, b, tab, i, pom);
        pom++;

        tablicaV(tab, i);
        ispom(czas, a, b, tab, i, pom);

        dopisywanie(i, czas, a, b, 5);
        delete[] tab;
        cout << "Wykres1.3 insertionesort" << endl;
    }
    przerwa_w_pliku();
    //wykres4 heapsort
    for (int i = 1000; i <= 10000; i = i + 1000)
    {
        tab = new int[i];
        int pom = 0;

        tablicarosnaca(tab, i);
        hspom(czas, a, b, tab, i, pom);
        pom++;

        tablicamalejaca(tab, i);
        hspom(czas, a, b, tab, i, pom);
        pom++;

        losowatablica(tab, i);
        hspom(czas, a, b, tab, i, pom);
        pom++;

        tablicaA(tab, i);
        hspom(czas, a, b, tab, i, pom);
        pom++;

        tablicaV(tab, i);
        hspom(czas, a, b, tab, i, pom);

        dopisywanie(i, czas, a, b, 5);
        delete[] tab;
        cout << "Wykres1.4 heapsort" << endl;
    }
    przerwa_w_pliku();
    //wykres5 quicksort
    for (int i = 10000; i <= 100000; i = i + 10000)
    {
        tab = new int[i];
        int pom = 0;

        tablicarosnaca(tab, i);
        qspom(czas, a, b, tab, i, pom);
        pom++;

        tablicamalejaca(tab, i);
        qspom(czas, a, b, tab, i, pom);
        pom++;

        losowatablica(tab, i);
        qspom(czas, a, b, tab, i, pom);
        pom++;

        tablicaA(tab, i);
        qspom(czas, a, b, tab, i, pom);
        pom++;

        tablicaV(tab, i);
        qspom(czas, a, b, tab, i, pom);

        dopisywanie(i, czas, a, b, 5);
        delete[] tab;
        cout << "Wykres1.5 quicksort" << endl;
    }
    przerwa_w_pliku();
    //wykres 6 mergesort
    for (int i = 1000; i <= 10000; i = i + 1000)
    {
        tab = new int[i];
        int pom = 0;

        tablicarosnaca(tab, i);
        mspom(czas, a, tab, i, pom);
        pom++;

        tablicamalejaca(tab, i);
        mspom(czas, a, tab, i, pom);
        pom++;

        losowatablica(tab, i);
        mspom(czas, a, tab, i, pom);
        pom++;

        tablicaA(tab, i);
        mspom(czas, a, tab, i, pom);
        pom++;

        tablicaV(tab, i);
        mspom(czas, a, tab, i, pom);

        dopisywanie(i, czas, a, b, 5);
        delete[] tab;
        cout << "Wykres1.6 mergesort" << endl;
    }
    przerwa_w_pliku();
    //Wykres Tablica rosnaca 2.1
    for (int i = 1000; i <= 10000; i += 1000)
    {
        tab = new int[i];
        tablicarosnaca(tab, i);
        playmaker(tab, i);
        delete[] tab;
        cout << "Wykres Tablica rosnaca 2.1" << endl;
    }
    przerwa_w_pliku();
    //Wykres Tablica malejaca 2.2 
    for (int i = 1000; i <= 10000; i += 1000)
    {
        tab = new int[i];
        tablicamalejaca(tab, i);
        playmaker(tab, i);
        delete[] tab;
        cout << "Wykres Tablica malejaca 2.2 " << endl;
    }
    przerwa_w_pliku();
    //Wykres Tablica losowa 2.3 
    for (int i = 1000; i <= 10000; i += 1000)
    {
        tab = new int[i];
        losowatablica(tab, i);
        playmaker(tab, i);
        delete[] tab;
        cout << "Wykres Tablica losowa 2.3 " << endl;
    }
    przerwa_w_pliku();
    //Wykres TablicaA 2.4
    for (int i = 1000; i <= 10000; i += 1000)
    {
        tab = new int[i];
        tablicaA(tab, i);
        playmaker(tab, i);
        delete[] tab;
        cout << "Wykres TablicaA 2.4 " << endl;
    }
    przerwa_w_pliku();
    //Wykres TablicaV 2.5
    for (int i = 1000; i <= 10000; i += 1000)
    {
        tab = new int[i];
        tablicaV(tab, i);
        playmaker(tab, i);
        delete[] tab;
        cout << "Wykres TablicaV 2.5 " << endl;
    }    
return 0;
}


