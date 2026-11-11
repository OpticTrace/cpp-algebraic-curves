#pragma once // to avoid redefinition
#include <iostream>

struct Monom {
    double coeff;
    int x_power;
    int y_power;
    
    Monom(double c, int x, int y);

    friend std::ostream& operator<< (std::ostream& out, const Monom& M);
};