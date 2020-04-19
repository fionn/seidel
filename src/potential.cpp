#include <iostream>
#include "potential.hpp"

Potential::Potential(int m)
{
	n = m;
	data = new double [n * n];
}

double & Potential::operator() (int i, int j)
{
	return data[i + n * j];
}

