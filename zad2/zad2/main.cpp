#include <stdio.h>
#include <iostream>
#include <gmpxx.h>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
struct Liczba
{
    mpz_t licznik,mianownik;
};
inline bool comp(const Liczba& l1, const Liczba& l2)
{
    mpz_t val1, val2;
    mpz_init(val1);
    mpz_init(val2);
    mpz_set(val1, l1.licznik);
    mpz_mul(val1, val1, l2.mianownik);
    mpz_set(val2, l2.licznik);
    mpz_mul(val2, val2, l1.mianownik);
    int result = mpz_cmp(val1, val2);
    return (result >= 0);
}
struct comparator
{
    inline bool operator() (const Liczba& l1, const Liczba& l2)
    {
        return (!comp(l1, l2));
    }
};

int d,n = 0,p = 1;
vector<Liczba> v;

void wypisz_z_zerami(mpz_t number)
{
    char* chars = NULL;
    chars = mpz_get_str(chars, 10, number);
	string charStr(chars);
	if(charStr.size() < d + 1)
	{
		string tmp = "";
		for(int i=0; i < d+1 - charStr.size(); i++)
		{
			tmp += "0";
		}
		charStr = tmp + charStr;
	}
	charStr = charStr.substr(0, charStr.size() - d) + "." + charStr.substr(charStr.size() - d, charStr.size());
	charStr = charStr.substr(0, charStr.find_last_not_of('0') + 1);
	if(charStr[charStr.length()-1] == '.')
		charStr = charStr.substr(0, charStr.length()-1);
	cout << charStr << endl;
};
string get_mpz_t_string(mpz_t number)
{
    char* chars = NULL;
    chars = mpz_get_str(chars, 10, number);
	string charStr(chars);
	return charStr;
};

void chi_kwadrat(mpz_t multiplayer)
{
    int k = 10;
    vector<Liczba> A;
    vector<Liczba> Y;
    vector<Liczba> P;

//punkty wyznaczajace przedzialy
    for(int i=0; i<=k; i++)
    {
        Liczba a;
        mpz_init(a.licznik);
        mpz_init(a.mianownik);
        mpz_set_si(a.licznik, i*i);
        mpz_set_si(a.mianownik, 100);
        A.push_back(a);
    }
//wyznaczenie prawdopodobienst p_i - rowne sa a_i - a_(i-1)

        Liczba p;
        mpz_init(p.licznik);
        mpz_init(p.mianownik);
        mpz_set_si(p.licznik, 0);
        mpz_set_si(p.mianownik, 0);
        P.push_back(p);

    for(int i=1; i<=k; i++) //miejsce zerowe bedzie nieuzywane
    {
        mpz_t licznik;
        mpz_init(licznik);
        mpz_set(licznik, A[i].licznik);
        mpz_sub(licznik, licznik, A[i-1].licznik);

        Liczba p;
        mpz_init(p.licznik);
        mpz_init(p.mianownik);
        mpz_set(p.licznik, licznik);
        mpz_set_si(p.mianownik, 100);
        P.push_back(p);
    }

//inicjalizacja wektora Y
    for(int i=0; i<=k; i++) //miejsce zerowe bedzie nieuzywane
    {
        Liczba y;
        mpz_init(y.licznik);
        mpz_init(y.mianownik);
        mpz_set_si(y.licznik, 0);
        mpz_set_si(y.mianownik, 1);
        Y.push_back(y);
    }

//wypelnianie wektora Y
    for(int i=0; i<n; i++)
    {
        for(int j=1; j<=k; j++)
        {
//jezeli X z wektora v wpada konkretnie w dany przedzial, zwiekszamy licznik
            if(((comp(A[j-1], v[i]) == 0) || (comp(A[j-1], v[i]) < 0)) && (comp(A[j], v[i]) > 0))
            {
                mpz_add_ui(Y[j].licznik, Y[j].licznik, 1);
                break;
            }
        }
    }

//obliczanie V - rozwiniety wzor. Oryginalnie bylo suma (Yi - n*pi)^2/ n*pi
//pamietajac ze nasze Y ma w mianowniku 1
//wiec zeby bylo tylko jedno dzielenie to przeksztalcone do suma (p.mianownik * y - n * p.licznik)^2 / n * p.licznik * p.mianownik
//gdzie y to liczba z licznika Y

    vector<Liczba> V; //ciag zsumujemy na koncu, tu beda jego kolejne elementy

    for(int i=1; i<=k; i++)
    {
        mpz_t n_p_licznik;
        mpz_init(n_p_licznik);
        mpz_set_si(n_p_licznik, n);
        mpz_mul(n_p_licznik, n_p_licznik, P[i].licznik);

        Liczba kupa;
        mpz_init(kupa.licznik);
        mpz_init(kupa.mianownik);
        mpz_set(kupa.licznik, P[i].mianownik);
        mpz_mul(kupa.licznik, kupa.licznik, Y[i].licznik);
        mpz_sub(kupa.licznik, kupa.licznik, n_p_licznik);
        mpz_mul(kupa.licznik, kupa.licznik, kupa.licznik);

        mpz_set_si(kupa.mianownik, n);
        mpz_mul(kupa.mianownik, kupa.mianownik, P[i].licznik);
        mpz_mul(kupa.mianownik, kupa.mianownik, P[i].mianownik);

        V.push_back(kupa);
    }
    //teraz trzeba to posumowac, ale to wymaga wspolnego mianownika
    int V_size = V.size();
    Liczba V_sum;
    mpz_init(V_sum.licznik);
    mpz_init(V_sum.mianownik);
    mpz_set_si(V_sum.licznik, 0);
    mpz_set_si(V_sum.mianownik, 1);

    for(int i=0; i<V_size; i++)
    {
        mpz_t val2;
        mpz_init(val2);

        mpz_set(val2, V[i].licznik);
        mpz_mul(val2, val2, V_sum.mianownik);

        mpz_mul(V_sum.licznik, V_sum.licznik, V[i].mianownik);
        mpz_add(V_sum.licznik, V_sum.licznik, val2);

        mpz_mul(V_sum.mianownik, V_sum.mianownik, V[i].mianownik);

    }


//dopisanie zer
    mpz_mul(V_sum.licznik, V_sum.licznik, multiplayer);

    mpz_t V_result;
    mpz_init(V_result);
    mpz_tdiv_q(V_result, V_sum.licznik, V_sum.mianownik);

    wypisz_z_zerami(V_result);
}

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		d = atoi(argv[1]);
	}
	else //d na sztywno jeśli parametr nie zostanie podany
	{
        d = 5;
	}
	string num, licznikStr, mianownikStr;
	vector<Liczba> KplusVec, KminusVec;
    bool mian = true;
    Liczba l;

/*********************WCZYTYWANIE, SORTOWANIE I LICZENIE:***************************/

	while(cin >> num)
	{
        for(int i = 0; i < num.size(); i++)
        {
            if(num[i] == '/')
            {
                licznikStr = num.substr(0, i);
                mianownikStr = num.substr(i + 1, num.size());
                break;
            }
        }
        mpz_init(l.licznik);
        mpz_set_str (l.licznik, licznikStr.c_str(), 10);
        mpz_init(l.mianownik);
        mpz_set_str (l.mianownik, mianownikStr.c_str(), 10);
        mian = true;
        v.push_back(l);
	}
	n = v.size();
	sort(v.begin(), v.end(), comparator());

//WSPÓLNE MIANOWNIKI ODJEMNYCH I ODJEMNIKÓW:
	for(int j = 0; j<n; j++)
	{
        Liczba x;
        mpz_init(x.licznik);
        mpz_init(x.mianownik);
        mpz_set_si(x.licznik, j+1);
        mpz_set_si(x.mianownik, n);
        mpz_mul(x.licznik, x.licznik, v[j].mianownik);
        mpz_t odjemnik;
        mpz_init(odjemnik);
        mpz_set(odjemnik, v[j].licznik);
        mpz_mul(odjemnik, odjemnik, x.mianownik);
        mpz_sub(x.licznik, x.licznik, odjemnik);
        mpz_mul(x.mianownik, x.mianownik, v[j].mianownik);
        KplusVec.push_back(x);
	}
	int KplusIndex = 0;
	for(int i = 1; i < n; i++)
	{
        if(comp(KplusVec[i], KplusVec[KplusIndex]))
            KplusIndex = i;
	}

		for(int j = 0; j<n; j++)
	{
        Liczba x;
        mpz_init(x.licznik);
        mpz_init(x.mianownik);
        mpz_set(x.licznik, v[j].licznik);
        mpz_set(x.mianownik, v[j].mianownik);
        mpz_mul_si(x.licznik, x.licznik, n);
        mpz_t odjemnik;
        mpz_init(odjemnik);
        mpz_set_si(odjemnik, j);
        mpz_mul(odjemnik, odjemnik, x.mianownik);
        mpz_sub(x.licznik, x.licznik, odjemnik);
        mpz_mul_si(x.mianownik, x.mianownik, n);
        KminusVec.push_back(x);
	}
	int KminusIndex = 0;
	for(int i = 1; i < n; i++)
	{
        if(comp(KminusVec[i], KminusVec[KminusIndex]))
            KminusIndex = i;
	}
//DOPISANIE ZER:
	string multiplayerStr = "1";
	mpz_t multiplayer, Kplus, Kminus;
	mpz_init(multiplayer);
	mpz_init(Kplus);
	mpz_init(Kminus);
	for(int i = 0; i < d; i++)
    {
        multiplayerStr += '0';
    }

    mpz_set_str (multiplayer, multiplayerStr.c_str(), 10);
//OBLICZENIE K+ i K-
    mpz_set(Kplus, KplusVec[KplusIndex].licznik);
    mpz_mul(Kplus, Kplus, multiplayer);
    mpz_tdiv_q(Kplus, Kplus, KplusVec[KplusIndex].mianownik);

    mpz_set(Kminus, KminusVec[KminusIndex].licznik);
    mpz_mul(Kminus, Kminus, multiplayer);
    mpz_tdiv_q(Kminus, Kminus, KminusVec[KminusIndex].mianownik);

/********************LICZENIE CHI KWADRAT:*************************/
    chi_kwadrat(multiplayer); //i wypisywanie tez

/********************KONIEC LICZENIA CHI KWADRAT:*************************/

/*********************WYPISYWANIE:***************************/

	wypisz_z_zerami(Kplus);
	wypisz_z_zerami(Kminus);

/********************KONIEC WYPISYWANIA:*************************/

/********************LICZENIE TESTU PAR:*************************/

//    int k_pomoc = 3;
//    int k_pomoc_kwadrat = k_pomoc * k_pomoc;
//
//    vector<string> mozliwe_pary;
//
//    vector<Liczba> A_pom;
//    vector<Liczba> V_nowe;
//    vector<Liczba> Y;
//    vector<Liczba> P;
//
//    mozliwe_pary.push_back(string("00"));//miejsce zerowe bedzie nieuzywane
////inicjalizacja tablicy pomocniczej do psrawdzania co to za para
//    for(int i=1; i<=k_pomoc; i++)
//    {
//        for(int j=1; j<=k_pomoc; j++)
//        {
//            int costam = i*10 + j;
//            char *para;
//            sprintf(para, "%d", costam);
//
//            mozliwe_pary.push_back(string(para));
//        }
//    }
//
////punkty wyznaczajace przedzialy - zero niuzywane
//    for(int i=0; i<=k_pomoc; i++)
//    {
//        Liczba a;
//        mpz_init(a.licznik);
//        mpz_init(a.mianownik);
//        mpz_set_si(a.licznik, i);
//        mpz_set_si(a.mianownik, k_pomoc);
//        A_pom.push_back(a);
//    }
//
////przekonwertowanie wejsciowych ulamkow na numer przedzialu
//    for(int i=0; i<n; i++)
//    {
//        for(int j=1; j<=k_pomoc; j++)
//        {
////jezeli X z wektora v wpada konkretnie w dany przedzial, konwertujemy ta liczbe na numer tego przedzialu
//            if(((comp(A_pom[j-1], v[i]) == 0) || (comp(A_pom[j-1], v[i]) < 0)) && (comp(A_pom[j], v[i]) > 0))
//            {
//                Liczba v2;
//                mpz_init(v2.licznik);
//                mpz_init(v2.mianownik);
//                mpz_set_si(v2.licznik, j);
//                mpz_set_si(v2.mianownik, 1);
//                V_nowe.push_back(v2);
//                break;
//            }
//        }
//    }
//
//    //jezeli nieparzyscie to usuwamy ostatnia
//    if(V_nowe.size() % 2 != 0)
//    {
//        V_nowe.pop_back();
//    }
//
//    //inicjalizacja wektora Y
//    for(int i=0; i<=k_pomoc_kwadrat; i++) //miejsce zerowe bedzie nieuzywane
//    {
//        Liczba y;
//        mpz_init(y.licznik);
//        mpz_init(y.mianownik);
//        mpz_set_si(y.licznik, 0);
//        mpz_set_si(y.mianownik, 1);
//        Y.push_back(y);
//    }
//
//
//    //wypelnianie wektora Y
//    for(int i=0; i<=(n-1); i=i+2)
//    {
//        string para = get_mpz_t_string(V_nowe[i].licznik) + get_mpz_t_string(V_nowe[i+1].licznik);
//        for(int j=1; j<=k_pomoc_kwadrat; j++)
//        {
//            if(para.compare(mozliwe_pary[j])==0)
//            {
//                mpz_add_ui(Y[j].licznik, Y[j].licznik, 1);
//                break;
//            }
//        }
//    }
//
//
//    //wyznaczenie prawdopodobienst p_i - wszystkie rowne 1/k^2
//    for(int i=0; i<=k_pomoc; i++) //miejsce zerowe bedzie nieuzywane?
//    {
//        Liczba p;
//        mpz_init(p.licznik);
//        mpz_init(p.mianownik);
//        mpz_set_si(p.licznik, 1);
//        mpz_set_si(p.mianownik, k_pomoc*k_pomoc);
//        P.push_back(p);
//    }
//
//
//    chi_kwadrat(multiplayer); //i wypisywanie tez

/********************KONIEC LICZENIA TESTU PAR:*************************/

	return 0;
}
