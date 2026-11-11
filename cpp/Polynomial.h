#pragma once
#include <vector>
#include "Monom.h"

class Polynomial {
private:
    std::vector<Monom> terms;
public:
    Polynomial() = default; // пустой вектор по умолчанию
    Polynomial(std::vector<Monom> t);

    void addMonomial(const Monom& m);
    void simplify();
    void sort();
    void print();
    bool isFree() const;
    const std::vector<Monom>& getTerms() const;

    int getMaxDegreeX() const;
    double getCoeffAtMaxX() const;
    int getMinDegreeX() const;
    int getMinDegreeY() const;

    Polynomial divideByX(int n) const;
    Polynomial divideByY(int n) const;

    void subtractMultipleOf(const Polynomial& other, int mult_power, double some_coeff);
};