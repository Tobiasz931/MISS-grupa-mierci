#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

double f(double x, double y)
{
	double result = 3 * x * x - 2 * y * y;//-2*x*y;
	return result;
}

double calculate_next_point(double last_x, double last_y, double h)
{
	double result = last_y + h * f(last_x, last_y);
	return result;
}

int main(int argc, char **argv)
{
	double x0 = 0;
	double y0, epsilon, h, last_x, last_y;
	string temp_str;


/*********************WCZYTYWANIE***************************/
//kolejnosc parametrow:
	temp_str = string(argv[1]);
	y0 = strtod(temp_str.c_str(), NULL);
	temp_str = string(argv[2]);
	epsilon = strtod(temp_str.c_str(), NULL);
	h = epsilon;
/*********************LICZENIE***************************/
	ofstream output_file, command_file;
	output_file.open("euler.pg");
	output_file << x0 << " " << y0 << endl;

	last_x = x0;
	last_y = y0;

	for (double i = 0; i <= 1; i += epsilon)
	{
		output_file << i << " ";
		double next_point = calculate_next_point(last_x, last_y, h);
		output_file << next_point << endl;
		last_x = i;
		last_y = next_point;
	}
	output_file.close();
/*********************WYPISYWANIE***************************/
	system("gnuplot -p -e \"plot './euler.pg' with lines\"");
	return 0;
}
