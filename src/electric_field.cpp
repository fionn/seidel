#include "potential.h"
#include "electric_field.h"
#include <fstream>

double electric_field(Potential u, bool print = false)
// Calculates the x- and y-components of the field and
// returns the value of the integral L. Optionally prints
// the potential, E_x, E_y and their cross-section.
{
    Potential E_x(u.n);
    Potential E_y(u.n);

    using namespace std;
    ofstream pot, ex, ey, cs;
    if(print)
    {
        pot.open("u.dat");
        ex.open("ex.dat");
        ey.open("ey.dat");
        cs.open("cs.dat");
    }
                
    double L = 0;
    for(int i = 1; i < u.n - 1; i++)
        for(int j = 1; j < u.n - 1 ;j++)
        {
            E_x(i, j) = u.n * (u(i + 1, j) - u(i - 1, j)) * 0.5;
            E_y(i, j) = u.n * (u(i, j + 1) - u(i, j - 1)) * 0.5;

            L += E_x(i, j) * E_x(i, j) + E_y(i, j) * E_y(i, j);

            if(print)
            {
                pot << i << "\t" << j << "\t" << u(i, j) << endl;   // splot u
                ex << i << "\t" << j << "\t" << E_x(i, j) << endl; // splot E_x
                ey << i << "\t" << j << "\t" << E_y(i, j) << endl; // splot E_y
                if(i == int(0.5 * u.n)) // plot cross-section
                    cs << j << "\t" << E_x(i, j) << "\t" << E_y(i, j) << endl;
            }
        }
    
    if(print)
    {
        pot.close();
        ex.close();
        ey.close();
        cs.close();
    }

    return L / (u.n * u.n); // division by n^2 for Riemann sums
}

