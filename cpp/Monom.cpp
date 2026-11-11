#include "Monom.h"

Monom::Monom(double c, int x, int y) : coeff(c), x_power(x), y_power(y) {}

std::ostream& operator<< (std::ostream& out, const Monom& M) { // чтоб не передавать this
    out << M.coeff << "·x^" << M.x_power << "·y^" << M.y_power;
    return out;
}