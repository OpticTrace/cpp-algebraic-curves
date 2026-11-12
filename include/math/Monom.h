#pragma once

#include <iosfwd> // облегченный для std::ostream

namespace math {

struct Monom {
    double coeff;
    int x_power;
    int y_power;
    
    Monom() = default; // конструктор по умолчанию (чтобы вектор мог создавать пустые элементы)
    Monom(double c, int x, int y);

    friend std::ostream& operator<<(std::ostream& out, const Monom& M);
};

}