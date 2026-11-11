#include "Polynomial.h"
#include <map>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <iterator>

#define EPSILON 1e-9

Polynomial::Polynomial(std::vector<Monom> t) : terms(t) {}

void Polynomial::addMonomial(const Monom& m) {
    terms.push_back(m);
}

void Polynomial::simplify() { // привести пободные
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

void Polynomial::sort() {
    std::sort(
    terms.begin(),
    terms.end(),
    [] (const Monom& m1, const Monom& m2) {
        return std::tie(m1.x_power, m1.y_power, m1.coeff) > std::tie(m2.x_power, m2.y_power, m2.coeff);
    });
}

void Polynomial::print() {
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

bool Polynomial::isFree() const { // если есть свободный член (ненулевой) то true
    for (const Monom& m: terms) {
        if (m.x_power == 0 && m.y_power == 0 && std::abs(m.coeff) > EPSILON) return true;
    }
    return false;
}

const std::vector<Monom>& Polynomial::getTerms() const { return terms; }

int Polynomial::getMaxDegreeX() const {
    int max = 0;
    for (const Monom& m: terms) {
        if (m.y_power == 0 && m.x_power > max) {
            max = m.x_power;
        }
    }
    return max;
}

double Polynomial::getCoeffAtMaxX() const {
    int max_x_power = getMaxDegreeX();
    for (const Monom& m: terms) {
        if (m.y_power == 0 && m.x_power == max_x_power) {
            return m.coeff;
        }
    }
    return 0.0;
}

int Polynomial::getMinDegreeX() const {
    int min_power = -1;
    for (const Monom& m: terms) {
        if (min_power == -1 || m.x_power < min_power) {
            min_power = m.x_power;
        }
    }
    return min_power == -1 ? 0 : min_power;
}

int Polynomial::getMinDegreeY() const {
    int min_power = -1;
    for (const Monom& m: terms) {
        if (min_power == -1 || m.y_power < min_power) {
            min_power = m.y_power;
        }
    }
    return min_power == -1 ? 0 : min_power;
}

Polynomial Polynomial::divideByX(int n) const {
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

Polynomial Polynomial::divideByY(int n) const {
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

void Polynomial::subtractMultipleOf(const Polynomial& other, int mult_power, double some_coeff) { // вычесть из this многочлен coeff·other·x^mult_power (чтоб убрать лишние x)
    for (const Monom& m: other.getTerms()) {
        terms.push_back(Monom(m.coeff * -some_coeff, m.x_power + mult_power, m.y_power));
    }
    simplify();
}