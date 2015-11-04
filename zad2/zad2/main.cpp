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
    return (result > 0);
}
struct comparator
{
    inline bool operator() (const Liczba& l1, const Liczba& l2)
    {
        return (!comp(l1, l2));
    }
};
int d,n = 0,p = 1;

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
	string num;
	vector<Liczba> v, KplusVec, KminusVec;
    bool mian = true;
    Liczba l;

/*********************WCZYTYWANIE, SORTOWANIE I LICZENIE:***************************/

	while(cin >> num)
	{
        if(mian)
        {
            mpz_init(l.licznik);
            mpz_set_str (l.licznik, num.c_str(), 10);
            mian = false;
        }
        else
        {
            mpz_init(l.mianownik);
            mpz_set_str (l.mianownik, num.c_str(), 10);
            mian = true;
            v.push_back(l);
        }
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

/*********************WYPISYWANIE K+ i K-:***************************/

	char* KplusChars = NULL;
    KplusChars = mpz_get_str(KplusChars, 10, Kplus);
	string KplusStr(KplusChars);
	if(KplusStr.size() < d + 1)
	{
		string tmp = "";
		for(int i=0; i < d+1 - KplusStr.size(); i++)
		{
			tmp += "0";
		}
		KplusStr = tmp + KplusStr;
	}
	KplusStr = KplusStr.substr(0, KplusStr.size() - d) + "." + KplusStr.substr(KplusStr.size() - d, KplusStr.size());
	KplusStr = KplusStr.substr(0, KplusStr.find_last_not_of('0') + 1);
	if(KplusStr[KplusStr.length()-1] == '.')
		KplusStr = KplusStr.substr(0, KplusStr.length()-1);
	cout << KplusStr << endl;

    char* KminusChars = NULL;
    KminusChars = mpz_get_str(KminusChars, 10, Kminus);
	string KminusStr(KminusChars);
	if(KminusStr.size() < d + 1)
	{
		string tmp = "";
		for(int i=0; i < d+1 - KminusStr.size(); i++)
		{
			tmp += "0";
		}
		KminusStr = tmp + KminusStr;
	}
	KminusStr = KminusStr.substr(0, KminusStr.size() - d) + "." + KminusStr.substr(KminusStr.size() - d, KminusStr.size());
	KminusStr = KminusStr.substr(0, KminusStr.find_last_not_of('0') + 1);
	if(KminusStr[KminusStr.length()-1] == '.')
		KminusStr = KminusStr.substr(0, KminusStr.length()-1);
	cout << KminusStr << endl;

/********************KONIEC WYPISYWANIA K+ i K-:*************************/

/********************LICZENIE CHI KWADRAT:*************************/
    int k = 10;
    vector<Liczba> A;
    vector<Liczba> Y;
    //wg eti2011 prawd. tu wszedzie jest rowne i wynosi 1/l.przedzialow = 1/k, wiec zrobie jedno p
    Liczba p;
    mpz_init(p.licznik);
    mpz_init(p.mianownik);
    mpz_set_si(p.licznik, 1);
    mpz_set_si(p.mianownik, k);

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
//inicjalizacja wektora Y
    for(int i=0; i<=n; i++)
    {
        Liczba y;
        mpz_init(y.licznik);
        mpz_init(y.mianownik);
        mpz_set_si(y.licznik, 0);
        mpz_set_si(y.mianownik, 1);
        Y.push_back(y);
    }
//wypelnianie wektora Y
    for(int i=0; i<=n; i++)
    {
        for(int j=1; j<=k; j++)
        {
//jezeli X z wektora v wpada konkretnie w dany przedzial, zwiekszamy licznik
            if(((comp(A[j-1], v[i]) == 0) || (comp(A[j-1], v[i]) < 0)) && (comp(A[j], v[i]) > 0))
            {
                mpz_set(Y[j].licznik, Y[j].licznik+1);
                break;
            }
        }
    }

//obliczanie V - rozwiniety wzor. Oryginalnie bylo suma (Yi - n*pi)^2/ n*pi
//pamietajac ze nasze Y ma w mianowniku 1 a kazde p_i to 1/k
//wiec zeby bylo tylko jedno dzielenie to przeksztalcone do suma k(ky-n)^2 / n
//gdzie y to liczba z licznika Y, a ze mianownik wspolny to nawet przeksztalcac nie trzeba

    Liczba V;
    mpz_init(V.licznik);
    mpz_init(V.mianownik);
    mpz_set_si(V.licznik, 0);
    mpz_set_si(V.mianownik, n);

    for(int i=0; i<=k; i++)
    {
        mpz_t licznik;
        mpz_init(licznik);
        mpz_set_si(licznik, k);
        mpz_mul(licznik, licznik, Y[i].licznik);
        mpz_sub_ui(licznik, licznik, n);
        mpz_mul(licznik, licznik, licznik);
        mpz_mul_ui(licznik, licznik, k);
        mpz_add(V.licznik, V.licznik, licznik);

    }
    mpz_t V_sum;
    mpz_init(V_sum);
    mpz_tdiv_q(V_sum, V.licznik, V.mianownik);

/********************KONIEC LICZENIA CHI KWADRAT:*************************/

	return 0;
}
