#include <iostream>
#include <math/Multiplicity.h>

using namespace math;

int main() {
    std::cout << "program for calculating multiplicity of algebraic curves\n";

    // создаем первый многочлен f
    Polynomial f;
    std::cout << "enter monomials for f (coefficient degree_x degree_y) type 0 0 0 to stop\n";
    int coeff, deg_x, deg_y;
    while (std::cin >> coeff >> deg_x >> deg_y) {
        if (coeff == 0 && deg_x == 0 && deg_y == 0) break;
        f.addMonomial(Monom(coeff, deg_x, deg_y));
    }

    // создаем второй многочлен g
    Polynomial g;
    std::cout << "enter monomials for g (coefficient degree_x degree_y) type 0 0 0 to stop\n";
    while (std::cin >> coeff >> deg_x >> deg_y) {
        if (coeff == 0 && deg_x == 0 && deg_y == 0) break;
        g.addMonomial(Monom(coeff, deg_x, deg_y));
    }

    int result = calculateMultiplicity(f, g);
    std::cout << "multiplicity is " << result << "\n";

    return 0;
}