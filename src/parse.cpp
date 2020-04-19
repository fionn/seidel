#include <argp.h>
#include <iostream>
#include "arguments.hpp"
#include "parse.hpp"

void clean()
{
    std::cout << "Removing {u, ex, ey, cs}.dat" << std::endl;
    remove("u.dat");
    remove("ex.dat");
    remove("ey.dat");
    remove("cs.dat");
}

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = (struct arguments *) state -> input;
    switch(key)
    {
        case 't':
            arguments -> translate = true;
            break;
        case 'p':
            arguments -> print = true;
            break;
        case 'r':
            arguments -> overrelax = true;
            break;
        case 'q':
            arguments -> w = 1;
            break;
        case 'c':
            arguments -> clean = true;
            clean();
            //std::exit(0);
            break;
        case 'n':
            arguments -> n = atoi(arg);
            break;
        case 'a':
            arguments -> a = atoi(arg);
            break;
        case 'b':
            arguments -> b = atoi(arg);
            break;
        case 'w':
            arguments -> w = atof(arg);
            if(atof(arg) < 1 || atof(arg) >= 2)
            {
                std::cerr << "ω = " << arg << " is not in [1, 2)" << std::endl;
                return -1;
            }
            break;
        case 0:
            std::cout << state[0].name  << std::endl;
            std::cout << state[2].flags << std::endl;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

arguments parser(int argc, char *argv[])
{
    static struct argp_option options[] = 
    {
        {"print", 'p', 0, 0, "Produce {u, ex, ey, cs}.dat files: the potential, the x- and y-components of the vector field E and a cross-section"},
        {"translate", 't', 0, 0, "Output L as the inner region is translated"},
        {"relax", 'r', 0, 0, "Calculate the optimum successive over-relaxation parameter; defaults to ω = 1.92"},
        {"norelax", 'q', 0, 0, "Don't use successive over-relaxation (ω = 1)"},
        {"clean", 'c', 0, 0, "Remove files produced by --print and exit"},
        {"size", 'n', "n", 0, "Set the size of the (square) lattice"},
        {"omega", 'w', "w", 0, "Set the value of the over-relaxation parameter ω"}, 
        {"xboundary", 'a', "a", 0, "Set the x-coordinate of the inner boundary"},
        {"yboundary", 'b', "b", 0, "Set the y-coordinate of the inner boundary"},
      //{"alpha", 0, "a", 0, "Set the value of alpha; defaults to 0"},
      //{"da", 0, "da", 0, "Set the x-size of the inner region"},
      //{"db", 0, "db", 0, "Set the y-size of the inner region"},
        {0}
    };

    static char doc[] = "\e[1;38;5;166mSEIDEL\e[0m\n\e[1F\e[6C solves the Laplace equation for electrostatic potentials in bounded concentric regions using the Gauss-Seidel algorithm with successive over-relaxation.";

    static struct argp argp = {options, parse_opt, 0, doc};

    struct arguments arguments;
    arguments.translate = false;
    arguments.print     = false;
    arguments.overrelax = false;
    arguments.clean     = false;
    arguments.n         = 100;
    arguments.a         = 50;
    arguments.b         = 50;
    arguments.w         = 1.92;
    arguments.alpha     = 0;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    return arguments;
}

