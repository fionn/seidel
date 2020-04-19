#include <iostream>
#include <cmath>
#include "potential.hpp"
#include "initialise_boundary.hpp"
#include "update_gauss_seidel.hpp"
#include "relax.hpp"

double relax(Potential u, int a, int b, int da, int db, double alpha, 
                                                    bool run, double argsw)
// Runs through all values of the successive over-relaxation 
// parameter and returns the optimal value.
{
    if(!run)
        return argsw; // known optimum value
    else
    {
        double prev_iteration = INFINITY;
        double w = 1, dw = 0.01;

        while(w < 2)
        {
            initialise_boundary(u, a, b, da, db);

            int iteration = 0;
            bool converged = false;
            do 
            {
                converged = update_gauss_seidel(u, alpha, a, b, da, db, w);
                iteration++;
            }
            while(!converged);

            if(iteration > prev_iteration)
            {
                std::cout << "ω = " << w - dw << std::endl;
                return w - dw; // optimal over-relaxation parameter
            }
            else
                prev_iteration = iteration;

            std::cout << w << "\t" << iteration << std::endl;

            w += dw;
        }
    }

    return 1; // default value for no over-relaxation
}

