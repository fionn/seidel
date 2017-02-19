#include "potential.h"
#include "initialise_boundary.h"

void initialise_boundary(Potential u, int a, int b, int da, int db)
// Sets the boundary conditions and the value of the 
// potential in the interior.
{
    for(int i = 0; i < u.n; i++)
        for(int j = 0; j < u.n; j++)
            if((i >= a && i <= a + da && j == b) || 
               (i == a && j >= b && j <= b + db) || 
               (i >= a && i <= a + da && j == b + db) ||
               (i == a + da && j >= b && j <= b + db))
                u(i, j) = 0.0;
            else if(i == 0 || i == u.n - 1 || j == 0 || j == u.n - 1)
                u(i, j) = 1.0;
            else
                u(i, j) = 0.5; // this is faster for all w != 1.92
}

