#include <iostream>
#include "potential.h"
#include "electric_field.h"
#include "translate_y.h"
#include "gs.h"
#include "relax.h"
#include "arguments.h"
#include "parse.h"

int main(int argc, char *argv[])
{ 
    struct arguments args = parser(argc, argv);
    if(args.clean || args.w < 1 || args.w >= 2)
        return 0;

    const int n = args.n;                   // size of mesh
    int a = args.a, b = args.b;             // location of inner boundary
    const int da = 0.3 * n, db = 0.2 * n;   // size of inner region
    const double alpha = args.alpha;        // instead of 0.1;

    Potential u(n);
    const double w = relax(u, a, b, da, db, alpha, 
                           args.overrelax, args.w);

    std::cout << "n = " << n << ", a = " << a << ", b = " << b 
              << ", da = " << da << ", db = " << db << ", ω = " << w 
              << ", α = " << alpha << std::endl;

    if(!args.print)
    {
        if(!args.translate)
        {
            double L = gs(u, a, b, da, db, alpha, w);
            std::cout << "L = " << L << std::endl;
        }
        else
            translate_y(u, a, da, db, alpha, w);
    }
    else
    {
        gs(u, a, b, da, db, alpha, w);
        electric_field(u, args.print);
    }

    return 0;
}

