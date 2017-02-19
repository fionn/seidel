#include <iostream>
#include <cmath>
#include "potential.h"
#include "initialise_boundary.h"
#include "update_gauss_seidel.h"
#include "relax.h"

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
        for(double w = 1; w < 2; w += 0.01)    
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
                std::cout << "ω = " << w - 0.01 << std::endl;
                return w - 0.01; // optimal over-relaxation parameter
            }
            else
                prev_iteration = iteration;

            std::cout << w << "\t" << iteration << std::endl;
        }
    }

    return 1; // default value for no over-relaxation
}

