#include "potential.hpp"
#include "initialise_boundary.hpp"
#include "update_gauss_seidel.hpp"
#include "electric_field.hpp"
#include "gs.hpp"

double gs(Potential u, int a, int b, int da, int db, double alpha, double w)
// Wraps the Gauss-Seidel algorithm and iterates until
// converged, returns the integral L.
{
    initialise_boundary(u, a, b, da, db);

    bool converged = false;
    do 
        converged = update_gauss_seidel(u, alpha, a, b, da, db, w);
    while(!converged);

    return electric_field(u, false);
}

