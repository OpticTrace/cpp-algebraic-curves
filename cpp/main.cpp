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

    bool isFree() const { // если есть свободный член (ненулевой) то true
        for (const Monom& m: terms) {
            if (m.x_power == 0 && m.y_power == 0 && std::abs(m.coeff) > EPSILON) return true;
        }
        return false;
    }

    const std::vector<Monom>& getTerms() const { return terms; }

    int getMaxDegreeX() const {
        int max = 0;
        for (const Monom& m: terms) {
            if (m.y_power == 0 && m.x_power > max) {
                max = m.x_power;
            }
        }
        return max;
    }

    double getCoeffAtMaxX() const {
        int max_x_power = getMaxDegreeX();
        for (const Monom& m: terms) {
            if (m.y_power == 0 && m.x_power == max_x_power) {
                return m.coeff;
            }
        }
        return 0.0;
    }

    int getMinDegreeX() const {
        int min_power = -1;
        for (const Monom& m: terms) {
            if (min_power == -1 || m.x_power < min_power) {
                min_power = m.x_power;
            }
        }
        return min_power == -1 ? 0 : min_power;
    }

    int getMinDegreeY() const {
        int min_power = -1;
        for (const Monom& m: terms) {
            if (min_power == -1 || m.y_power < min_power) {
                min_power = m.y_power;
            }
        }
        return min_power == -1 ? 0 : min_power;
    }

    Polynomial divideByX(int n) const {
        if (getMinDegreeX() >= n) {
            std::vector<Monom> new_terms;
            for (const Monom& m: terms) {
                new_terms.push_back(Monom(m.coeff, m.x_power - n, m.y_power));
            }
            return Polynomial(new_terms);
        }
        else {
            return Polynomial(terms);
        }
    }


    Polynomial divideByY(int n) const {
        if (getMinDegreeY() >= n) {
            std::vector<Monom> new_terms;
            for (const Monom& m: terms) {
                new_terms.push_back(Monom(m.coeff, m.x_power, m.y_power - n));
            }
            return Polynomial(new_terms);
        }
        else {
            return Polynomial(terms);
        }
    }


    void subtractMultipleOf(const Polynomial& other, int mult_power, double some_coeff) { // вычесть из this многочлен coeff·other·x^mult_power (чтоб убрать лишние x)
        for (const Monom& m: other.getTerms()) {
            terms.push_back(Monom(m.coeff * -some_coeff, m.x_power + mult_power, m.y_power));
        }
        simplify();
    }

};


int main() {
    Polynomial p1 = Polynomial();
    p1.addMonomial(Monom(-1, 2, 3));
    p1.addMonomial(Monom(-15, 10, 3));
    Polynomial p2 = Polynomial();
    p2.addMonomial(Monom(-10, 12, 3));
    p1.subtractMultipleOf(p2, 3, 2.2);
    p1.print();
}
