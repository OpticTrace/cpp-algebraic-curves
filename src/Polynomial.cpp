#include <math/Polynomial.h>
#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <iterator>

namespace math {

constexpr double EPSILON = 1e-9;

Polynomial::Polynomial(std::vector<Monom> t) : terms(std::move(t)) {} // move для оптимизации

void Polynomial::addMonomial(const Monom& m) {
    terms.push_back(m);
}

void Polynomial::simplify() { // привести пободные
    std::map<std::pair<int, int>, double> coeff_map;
    for (const Monom& m: terms) {
        coeff_map[{m.x_power, m.y_power}] += m.coeff;
    }
    terms.clear();
    for (const auto& [key, value] : coeff_map) {
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

void Polynomial::print() const {
    std::vector<Monom> sorted_terms = terms; // сортируем копию а не оригинал
    std::sort(
        sorted_terms.begin(),
        sorted_terms.end(),
        [] (const Monom& m1, const Monom& m2) {
            return std::tie(m1.x_power, m1.y_power, m1.coeff) > std::tie(m2.x_power, m2.y_power, m2.coeff);
        }
    );

    if (sorted_terms.empty()) {
        std::cout << "0\n";
        return;
    }

    for (auto it = sorted_terms.begin(); it != sorted_terms.end(); ++it) {
        // костыль для красивого вывода знаков
        if (it != sorted_terms.begin()) {
            if (it->coeff > 0) std::cout << " + ";
            else std::cout << " - ";
        }
        
        // выводим модуль коэффициента чтобы не было двойных минусов
        Monom temp = *it;
        if (it != sorted_terms.begin() && temp.coeff < 0) {
            temp.coeff = -temp.coeff; 
        }
        std::cout << temp;
    }
    std::cout << "\n";
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

void Polynomial::subtractMultipleOf(const Polynomial& other, int mult_power, double multiplier) { // вычесть из this многочлен coeff·other·x^mult_power (чтоб убрать лишние x)
    for (const Monom& m: other.getTerms()) {
        terms.push_back(Monom(m.coeff * -multiplier, m.x_power + mult_power, m.y_power));
    }
    simplify();
}

}