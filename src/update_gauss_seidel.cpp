#include "potential.hpp"
#include "update_gauss_seidel.hpp"

bool update_gauss_seidel(Potential u, double alpha, int a, int b, int a_len, int b_len, double w)
// Solves the Laplace equation via the Gauss-Seidel
// algorithm and successive over-relaxation.
// Returns boolean on thermalisation.
{
    double d = 0.0;

    for(int i = 1; i < u.n - 1; i++)
        for(int j = 1; j < u.n - 1; j++)
            if(!((i >= a && i <= a + a_len && j == b) || 
                 (i == a && j >= b && j <= b + b_len) || 
                 (i >= a && i <= a + a_len && j == b + b_len) || 
                 (i == a + a_len && j >= b && j <= b + b_len)))
            {
                double u_old = u(i, j);
                u(i, j) = w * (u(i + 1, j) + u(i - 1, j) 
                               + u(i, j + 1) + u(i, j - 1)) / (4.0 + alpha)
                          + (1 - w) * u(i, j);

                u_old -= u(i, j);
                d += u_old * u_old;
            }

    return d < 1.0e-11; // what is largest reasonable number?
}

