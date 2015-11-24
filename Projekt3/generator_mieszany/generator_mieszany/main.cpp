#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	unsigned int *LFGs;
	unsigned int *LFSRs;
	unsigned int *results;


/*********************WCZYTYWANIE***************************/
//kolejnosc parametrow: n-m k LFG0 LFG1 (...) LFGk-1 LFSR0 LFSR1 (...) LFSRk-1
	string num, nStr, mStr;
	unsigned int liczba_min,liczba_max,k;
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
	k = atoi(argv[2]);

	LFGs = new unsigned int[k+1];

	int index = 0;
	int LFSRs_start_index = k+3;
	for (int i = 3; i < (LFSRs_start_index); i++) {
        LFGs[index] = (atoi(argv[i]));
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
	for (int j = 0; j <k; j++)
	{
		int result = LFGs[j] - LFSRs[j];
		results[j] = result;
	}
/*********************WYPISYWANIE***************************/
for (int i = liczba_min; i <liczba_max; i++)
	{
		printf("%d ", results[i]);
	}
/*********************SPRZATANIE***************************/
	delete[] LFSRs;
	delete[] LFGs;
	delete[] results;
	return 0;
}
