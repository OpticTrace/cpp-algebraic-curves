#include <iostream>
#include <vector>
#include <map>


struct Monom {
    double coeff;
    int x_power;
    int y_power;
    
    Monom(double c, int x, int y) : coeff(c), x_power(x), y_power(y) {}

    friend std::ostream& operator<< (std::ostream& out, const Monom& M) { // чтоб не передавать this
        out << M.coeff << " · x^" << M.x_power << " · y^" << M.y_power;
        return out;
    }
};


class Polynomial {
private:
    std::vector<Monom> terms;
public:
    Polynomial() = default; // пустой вектор по умолчанию
    Polynomial(std::vector<Monom> t) : terms(t) {}

    void addMonomial(const Monom& m) {
        terms.push_back(m);
    }

    void simplify() {
        
    }


};


int main() {
    // std::cout << Monom(1, 2, 3);
}
