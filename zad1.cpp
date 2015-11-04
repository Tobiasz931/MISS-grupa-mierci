#include <stdio.h>
#include <iostream>
#include <gmpxx.h>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
int d,n = 0,p = 1;

string fixed(mpf_class x)
{
    ostringstream ss;
    ss << fixed << setprecision(d) << x;
    string str = ss.str();
	str = str.substr(0, str.find_last_not_of('0') + 1);
	if(str[str.length()-1] == '.')
		return str.substr(0, str.length()-1);
	else
		return str;
}

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		d = atoi(argv[1]);
	}
	string num;
	mpz_t x, sum, sum2, count, omg;
	mpz_init(x);
	mpz_init(sum);
	mpz_init(sum2);
	mpf_class xn = 0;
	vector<double> v;
	while(cin >> num)
	{
		xn = num;
		int zeros = d;
		for(int i = 0; i < num.size(); i++)
		{
			if(num[i] == '.')
			{
				zeros -= num.size() - i - 1;
				num = num.substr(0, i) + num.substr(i + 1, num.size());
				break;
			}
		}
		for(int i = 0; i < zeros; i++)
		{
			num += '0';
		}
		mpz_set_str (x, num.c_str(), 10);
		mpz_add(sum, sum, x);
		mpz_mul(x, x, x);
		mpz_add(sum2, sum2, x);
		v.push_back((double)xn.get_d());
		n++;		
	}
	mpz_init_set_si (count, n);
	mpz_init_set_si (omg, 0);
	mpz_add(omg, omg, sum);
	mpz_mul(omg, omg, omg);
	mpz_tdiv_q(omg, omg, count);
	mpz_tdiv_q(omg, omg, count);
	mpz_tdiv_q(sum, sum, count);
	mpz_tdiv_q(sum2, sum2, count);
	mpz_mul(x, sum, sum);
	mpz_sub(sum2, sum2, omg);
	char* chars = NULL;
	chars = mpz_get_str(chars, 10, sum2);
	string temp(chars);
	if(temp.size() > d)
	{
		temp = temp.substr(0, temp.size()-d);
		mpz_set_str (sum2, temp.c_str(), 10);
	}
	else
		mpz_set_si(sum2, 0);

	char* sumChars = NULL;
	sumChars = mpz_get_str(sumChars, 10, sum);
	string sumStr(sumChars);
	if(sumStr.size() < d + 1)
	{
		string tmp = "";
		for(int i=0; i < d+1 - sumStr.size(); i++)
		{
			tmp += "0";
		}
		sumStr = tmp + sumStr;
	}
	sumStr = sumStr.substr(0, sumStr.size() - d) + "." + sumStr.substr(sumStr.size() - d, sumStr.size());
	//sumStr = sumStr.substr(0, sumStr.size()-1);
	sumStr = sumStr.substr(0, sumStr.find_last_not_of('0') + 1);
	if(sumStr[sumStr.length()-1] == '.')
		sumStr = sumStr.substr(0, sumStr.length()-1);
	cout << sumStr << endl;

	char* sum2Chars = NULL;
	sum2Chars = mpz_get_str(sum2Chars, 10, sum2);
	string sum2Str(sum2Chars);
	if(sum2Str.size() < d + 1)
	{
		string tmp = "";
		for(int i=0; i < d+1 - sum2Str.size(); i++)
		{
			tmp += "0";
		}
		sum2Str = tmp + sum2Str;
	}
	sum2Str = sum2Str.substr(0, sum2Str.size() - d) + "." + sum2Str.substr(sum2Str.size() - d, sum2Str.size());

	//sum2Str = sum2Str.substr(0, sum2Str.size()-1);
	sum2Str = sum2Str.substr(0, sum2Str.find_last_not_of('0') + 1);
	if(sum2Str[sum2Str.length()-1] == '.')
		sum2Str = sum2Str.substr(0, sum2Str.length()-1);
	cout << sum2Str << endl;

	p = n;
	for(int i = 1; i < v.size(); i++)
	{
		bool success = true;
		int initial = i;
		for(int j = 0; i < v.size() && j < initial; j++, i++)
		{
			if(v[j] != v[i])
			{
				success = false;
				break;
			}
		}
		if(success)
		{
			for(int j = 0; i < v.size(); i++, j++)
			{
				if(v[i] != v[j%initial])
				{
					success = false;
					break;
				}
			}
		}
		if(success)
		{
			p = initial;
			break;
		}
		i = initial;
	}
	cout << p << endl;
	return 0;
}
