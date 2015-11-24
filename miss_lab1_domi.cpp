#include <stdio.h>
#include <gmpxx.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

std::string fixed(mpf_class x, int prec)
{

    std::ostringstream ss;
    ss << std::fixed;
	ss << std::setprecision(prec);
	ss << x;
    std::string str = ss.str();
    return str.substr(0, str.find_last_not_of('0') + 1);






}

int main(int argc, char **argv)
{

	int d = 20; //dokladnosc
	int n = 0; //ilosc liczb
	int p = 1; //okres

	if(argc > 1)
	{
		d = atoi(argv[1]);
	}
	double bits_per_digit = 3.32192809488736234789; //log2(10)
	//mpf_set_default_prec((21+d)*bits_per_digit + 1);
	//bo d dotyczy tego co po kropce, a z przodu moze byc jeszcze jakies ok. 20 cyfr dla 2^64
	//a jednak wincyj niz 20, jak w wariancji w przykladzie 4, jest jakies 40 przed kropka..
	//no i jak to oszacowac? moze po prostu od razu 100, po co sie rozdrabniac?
	mpf_set_default_prec((100+d)*bits_per_digit + 1);

	std::string sxn;
	mpf_class xn;xn = 0;
	mpf_class xn_sum; xn_sum = 0;
	mpf_class xn_2sum; xn_2sum = 0;

	std::vector<float> XXX;
	float closeInaf;
	while(std::cin >> sxn)
	{
		xn = sxn;
		xn_sum += xn;
		xn_2sum += (xn*xn);
		closeInaf = (float)xn.get_d();
		XXX.push_back(closeInaf);
		if(n!= 0 && XXX[n-p] != closeInaf)
		{
			p++;
		}
		n+=1;
	}

	mpf_class avg = xn_sum / n;
	mpf_class vari = (xn_2sum / n) - avg*avg;

	std::cout.setf(std::ios_base::fixed);

	std::cout << fixed(avg, d) << std::endl;
	//std::cout << avg.get_str(exp, 10, (size_t)d) << std::endl;
	std::cout << fixed(vari, d) << std::endl;
	std::cout << p << "\n";
	return 0;
}
