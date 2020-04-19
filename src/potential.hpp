#ifndef POTENTIAL_H
#define POTENTIAL_H

class Potential
{
    public:
        double *data;
        int n;
        Potential(int m);
        double &operator() (int i, int j);
};

#endif

