#include <iostream>

struct Monom {
    double coeff;
    int x_power;
    int y_power;
    
    Monom(double c, int x, int y) : coeff(c), x_power(x), y_power(y) {}

    friend std::ostream& operator<< (std::ostream& out, const Monom& M) { // чтоб не передавать this
        out << M.coeff << " · x^" << M.x_power << " · y^" << M.y_power << "\n";
        return out;
    }
};


int main() {
    // std::cout << Monom(1, 2, 3);
}
