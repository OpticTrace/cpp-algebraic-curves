#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <iterator>


#define EPSILON 1e-9

struct Monom {
    double coeff;
    int x_power;
    int y_power;
    
    Monom(double c, int x, int y) : coeff(c), x_power(x), y_power(y) {}

    friend std::ostream& operator<< (std::ostream& out, const Monom& M) { // чтоб не передавать this
        out << M.coeff << "·x^" << M.x_power << "·y^" << M.y_power;
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

    void simplify() { // привести пободные
        std::map<std::pair<int, int>, double> map; // ключ: <степень_x, степень_y>, значение: коэффицент перед этим мономом
        for (const Monom& m: terms) {
            map[{m.x_power, m.y_power}] += m.coeff;
        }
        terms.clear();
        for (const auto& [key, value] : map) {
            if (std::abs(value) > EPSILON) 
                terms.push_back(Monom(value, key.first, key.second));
        }
    }

    void sort() {
        std::sort(
        terms.begin(),
        terms.end(),
        [] (const Monom& m1, const Monom& m2) {
            return std::tie(m1.x_power, m1.y_power, m1.coeff) > std::tie(m2.x_power, m2.y_power, m2.coeff);
        });
    }

    void print() {
        this->sort();
        if (terms.begin() != terms.end()) {
            for (auto it = terms.begin(); it != terms.end(); ++it) {
                if (std::next(it) == terms.end()) {
                    std::cout << *it << "\n";
                }
                else {
                    std::cout << *it << " + ";
                }
            }
        }
        else {
            std::cout << "0\n";
        }
    }

};


int main() {
    Polynomial p = Polynomial();
    p.addMonomial(Monom(-1, 2, 3));
    p.addMonomial(Monom(-15, 10, 3));
    p.print();
}
