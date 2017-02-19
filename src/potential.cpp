#include "potential.h"

Potential::Potential(int m) // constructor
{
	n = m;
	data = new double [n * n];
}

double & Potential::operator() (int i, int j)
{
	return data[i + n * j];
}

