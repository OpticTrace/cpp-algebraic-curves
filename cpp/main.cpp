#include <iostream>
#include "Multiplicity.h"

int main() {
    // Тест 1: f = x^2 - y, g = x^3 - y^2 (Ожидаемый ответ: 3)
    Polynomial f1;
    f1.addMonomial(Monom(1, 2, 0)); // x^2
    f1.addMonomial(Monom(-1, 0, 1)); // -y

    Polynomial g1;
    g1.addMonomial(Monom(1, 3, 0)); // x^3
    g1.addMonomial(Monom(-1, 0, 2)); // -y^2

    std::cout << "Test 1 (Expect 3): " << calculateMultiplicity(f1, g1) << "\n";

    // Тест 2: f = x^3 - y^2, g = x^2 - y^3 (Ожидаемый ответ: 4)
    Polynomial f2;
    f2.addMonomial(Monom(1, 3, 0)); // x^3
    f2.addMonomial(Monom(-1, 0, 2)); // -y^2

    Polynomial g2;
    g2.addMonomial(Monom(1, 2, 0)); // x^2
    g2.addMonomial(Monom(-1, 0, 3)); // -y^3

    std::cout << "Test 2 (Expect 4): " << calculateMultiplicity(f2, g2) << "\n";

    return 0;
}