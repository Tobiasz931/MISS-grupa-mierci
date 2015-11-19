#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	unsigned int *LFGs;


/*********************WCZYTYWANIE***************************/
//kolejnosc parametrow: n-m j k m LFG0 LFG1 (...) LFGk-1
//obowiazkowe sa parametry do k wlacznie, reszta opcjonalna
	string num, nStr, mStr;
	unsigned int liczba_min,liczba_max,j,k,m;
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

	liczba_min = atoi(nStr.c_str());
	liczba_max = atoi(mStr.c_str());
	j = atoi(argv[2]);
	k = atoi(argv[3]);

	if (argc >= 4)
	{
		m = atoi(argv[4]);
	}

	if (liczba_max > k)
	{
		LFGs = new unsigned int[liczba_max+1];
	}
	else
	{
		LFGs = new unsigned int[k+1];
	}

    int index = 0;
	for (int i = 5; i < argc; ++i) {
        LFGs[index] = (atoi(argv[i]));
        index++;
    }
/*********************LICZENIE***************************/
	for (int i = k; i <liczba_max; i++)
	{
		LFGs[i] = min(LFGs[i-j], LFGs[i-k]) % m;
	}
/*********************WYPISYWANIE***************************/
for (int i = liczba_min; i <liczba_max; i++)
	{
		printf("%d ", LFGs[i]);
	}
/*********************SPRZATANIE***************************/
	delete[] LFGs;
	return 0;
}
