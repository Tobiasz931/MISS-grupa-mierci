#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>

using namespace std;

void print_binary_to_decimal(long n) /* Function to convert binary to decimal.*/
{
    int decimal=0, i=0, rem;
    while (n!=0)
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(2,i);
        ++i;
    }
    printf("%d ", decimal);
    return;
}

int main(int argc, char **argv)
{
	unsigned int *a;
	unsigned int *LFSRs;


/*********************WCZYTYWANIE***************************/
//kolejnosc parametrow: n-m k a1 a2 (...) ak LFSR0 LFSR1 (...) LFSRk-1
//n-m powinno zawierac wielokrotnosc 32, bo inaczej nie wiem jak ostatnia liczbe zlozy
	string num, nStr, mStr;
	unsigned int k;
	unsigned long long int liczba_min,liczba_max;
	num = string(argv[1]);
	for(int i = 0; i < num.size(); i++)
	{
		if(num[i] == '-')
		{
			nStr = num.substr(0, i);
			mStr = num.substr(i + 1, num.size());
			break;
		}
	}

	liczba_min = strtoull(nStr.c_str(), NULL, 10);

	liczba_max = strtoull(mStr.c_str(), NULL, 10);

	k = atoi(argv[2]);

	a = new unsigned int[k+1];

	int index = 1;
	a[0] = 0; //bo we wzorze idzie od 1
	int LFSRs_start_index = k+3;
	for (int i = 3; i < (LFSRs_start_index); i++) {
        a[index] = (atoi(argv[i]));
        index++;
    }

	if (liczba_max > k)
	{
		LFSRs = new unsigned int[liczba_max+1];
	}
	else
	{
		LFSRs = new unsigned int[k+1];
	}

	if (argc >= (LFSRs_start_index))
	{
		index = 0;
		for (int i = LFSRs_start_index; i < argc; i++) {
			LFSRs[index] = (atoi(argv[i]));
			index++;
		}
	}
/*********************LICZENIE***************************/
	for (int j = k; j <liczba_max; j++)
	{
		int result = 0;
		//printf("b%d = ", j);
		for (int i=1; i <= k; i++)
		{
			result += a[i] * LFSRs[j-i];
		}
		LFSRs[j] = result % 2;
	}
/*********************WYPISYWANIE***************************/
int z=0, next_bin;
string binary_str;

for (int i = liczba_min; i <liczba_max; i++)
	{
        next_bin = LFSRs[i];
        string tmp; // brzydkie rozwiązanie
        sprintf((char*)tmp.c_str(), "%d", next_bin);
        string str = tmp.c_str();
        binary_str = binary_str + str;
        z++;
		if (z == 32)
		{
            z = 0;
            printf("%llu ", strtoull(binary_str.c_str(), NULL, 2));
            binary_str = "";
		}
	}
/*********************SPRZATANIE***************************/
	delete[] LFSRs;
	delete[] a;
	return 0;
}
