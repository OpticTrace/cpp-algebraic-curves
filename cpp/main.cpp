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



int calculateMultiplicity(Polynomial f, Polynomial g) { 
    int result = 0;

    // по теореме Ван дер Вардена алгоритм гарантированно завершится
    while (true) { 

        // свойство (а) из лекции: если есть свободный член (число без x и y), 
        // значит, кривая не проходит через точку (0,0), и пересечения там нет
        if (f.isFree() || g.isFree()) { 
            return result; 
        }

        
        // если многочлен полностью сократился до нуля (все мономы уничтожились)
        // значит мы все посчитали выходим из цикла
        if (f.getTerms().empty() || g.getTerms().empty()) { 
            break; 
        }

        // если f(x, y) делится на y, это значит, что f можно записать как f = y * h
        // (то есть абсолютно все члены в f содержат моном y)
        if (f.getMinDegreeY() >= 1) {
            
            // по свойству (в) из лекции: m(f, g) = m(y*h, g) = m(y, g) + m(h, g)
            // сейчас наша задача - найти вот эту часть: m(y, g). 
            // это кратность пересечения горизонтальной оси X (ее уравнение y=0) с кривой g.
            
            // как мы выяснили: чтобы найти кратность с осью y=0, 
            // нужно подставить y=0 в многочлен g (выкинуть все члены с y) 
            // ищем минимальную степень x. 
            // почему именно минимальную? потому что это максимальная степень x, 
            // которую мы можем вынести за скобку (например, из x^2 + x^3 выносится x^2).
            // то, что остается в скобках, в нуле не равно нулю.
            // значит, степень вынесенного икса в точности показывает, 
            // насколько сильно кривая касается оси (то есть кратность корня x=0)!
            int min_x = 999999;
            for (const Monom& m : g.getTerms()) {
                // ищем только те члены, где нет y (то есть мы подставили y=0)
                if (m.y_power == 0 && m.x_power < min_x) {
                    min_x = m.x_power; // находим самую маленькую степень x (минимальную)
                }
            }
            // если членов без y вообще не нашлось, значит пересечения с осью нет
            if (min_x == 999999) min_x = 0;
            
            // прибавляем найденную кратность m(y, g) к общему ответу
            result += min_x; 
            
            // теперь мы учли кусок y. осталось разобраться с h.
            // делим f на y, чтобы получить этот самый h, и идем на следующий круг.
            f = f.divideByY(1); 
            continue;
        }
        
        // абсолютно симметричная ситуация: если g(x, y) делится на y, то g = y * h.
        // по свойству (в): m(f, g) = m(f, y*h) = m(f, y) + m(f, h)
        else if (g.getMinDegreeY() >= 1) {
            
            // нам нужно найти m(f, y) - кратность пересечения оси y=0 с кривой f.
            // для этого смотрим на многочлен f, выкидываем члены с y 
            // и ищем минимальную степень x.
            int min_x = 999999;
            for (const Monom& m : f.getTerms()) {
                if (m.y_power == 0 && m.x_power < min_x) {
                    min_x = m.x_power;
                }
            }
            if (min_x == 999999) min_x = 0;

            // прибавляем m(f, y) к общему ответу
            result += min_x; 
            
            // делим g на y, чтобы получить h, и продолжаем алгоритм
            g = g.divideByY(1); 
            continue; 
        }
        else {
            // самое сердце алгоритма (шаг 2 из лекции 10). 
            // мы попали сюда, потому что ни f, ни g не делятся на y.
            // это значит, что у обоих есть чистые иксы (мономы, которые останутся даже при y=0).
            // именно их мы сейчас будем уничтожать вычитанием.
            
            // находим максимальную степень x для f(x,0) и для g(x,0)
            int deg_f = f.getMaxDegreeX();
            int deg_g = g.getMaxDegreeX();

            // по свойству (б): m(f, g) = m(f, g - (beta/alpha) * x^(l-k) * f)
            // мы вычитаем из одного многочлена другой, чтобы старшая степень x сократилась.
            if (deg_g >= deg_f) {
                // если степень g больше, уничтожаем старший член в g.
                // для этого вычисляем отношение старших коэффициентов (beta / alpha),
                // чтобы при вычитании они дали ноль (например, 3x^4 - 3x^4 = 0).
                double ratio = g.getCoeffAtMaxX() / f.getCoeffAtMaxX();
                
                // вычитаем из g многочлен f, умноженный на нужный коэффициент и x^(deg_g - deg_f).
                // это гарантированно уменьшит максимальную степень x в g.
                g.subtractMultipleOf(f, deg_g - deg_f, ratio);
            } 
            else {
                // симметрично: если степень f больше, уничтожаем старший член в f,
                // вычитая из него кратное g.
                double ratio = f.getCoeffAtMaxX() / g.getCoeffAtMaxX();
                f.subtractMultipleOf(g, deg_f - deg_g, ratio);
            }
            // после вычитания цикл автоматически пойдет на следующую итерацию. 
            // многочлены станут проще, и мы продолжим, пока не дойдем до выноса y.
        }
    }

    // возвращаем накопленную сумму кратностей (все те очки, что мы собрали на шагах с y)
    return result;
}



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