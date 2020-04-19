#include <iostream>
#include "potential.hpp"
#include "gs.hpp"
#include "translate_y.hpp"

void translate_y(Potential u, int a, int da, int db, double alpha, double w)
// Moves the container vertically through the region,
// updating the field each time and printing the value
// of the integral L.
{
    for(int b = 0; b <= u.n; b += 1)
    {
        std::cout << b << "\t";
        double L = gs(u, a, b, da, db, alpha, w);
        std::cout << L << std::endl;
    }
}

