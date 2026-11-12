#include <gtest/gtest.h>
#include <math/Multiplicity.h>

using namespace math;

// вспомогательная функция для создания многочлена из списка одночленов
Polynomial makePolynomial(std::initializer_list<Monom> monomials) {
    Polynomial p;
    for (const auto& m : monomials) {
        p.addMonomial(m);
    }
    return p;
}

// случай 1 две перпендикулярные прямые пересекаются в начале координат f = x, g = y
// геометрически они пересекаются ровно один раз
TEST(MultiplicityTest, SimpleIntersection_ReturnsOne) {
    Polynomial f = makePolynomial({ Monom(1, 1, 0) }); // x
    Polynomial g = makePolynomial({ Monom(1, 0, 1) }); // y

    EXPECT_EQ(calculateMultiplicity(f, g), 1);
}

// случай 2 прямая касается параболы в начале координат f = y, g = y - x^2
// точка пересечения имеет кратность 2
TEST(MultiplicityTest, TangentParabola_ReturnsTwo) {
    Polynomial f = makePolynomial({ Monom(1, 0, 1) }); // y
    Polynomial g = makePolynomial({ 
        Monom(1, 0, 1),   // y
        Monom(-1, 2, 0)   // -x^2
    });

    EXPECT_EQ(calculateMultiplicity(f, g), 2);
}

// случай 3 парабола и касп f = x^2 - y, g = x^3 - y^2
// эти кривые соприкасаются в начале координат с более высоким порядком
TEST(MultiplicityTest, ParabolaAndCusp_ReturnsThree) {
    Polynomial f = makePolynomial({
        Monom(1, 2, 0),   // x^2
        Monom(-1, 0, 1)   // -y
    });
    
    Polynomial g = makePolynomial({
        Monom(1, 3, 0),   // x^3
        Monom(-1, 0, 2)   // -y^2
    });

    EXPECT_EQ(calculateMultiplicity(f, g), 3);
}

// случай 4 два симметричных каспа f = x^3 - y^2, g = x^2 - y^3
// проверяем алгоритм на более сложных алгебраических кривых
TEST(MultiplicityTest, SymmetricCusps_ReturnsFour) {
    Polynomial f = makePolynomial({
        Monom(1, 3, 0),   // x^3
        Monom(-1, 0, 2)   // -y^2
    });
    
    Polynomial g = makePolynomial({
        Monom(1, 2, 0),   // x^2
        Monom(-1, 0, 3)   // -y^3
    });

    EXPECT_EQ(calculateMultiplicity(f, g), 4);
}

// проверка свойства кратность пересечения должна быть симметричной
// математически mult(f g) == mult(g f)
TEST(MultiplicityTest, Commutativity_OrderDoesNotMatter) {
    Polynomial f = makePolynomial({
        Monom(1, 3, 0), Monom(-1, 0, 2)
    });
    
    Polynomial g = makePolynomial({
        Monom(1, 2, 0), Monom(-1, 0, 3)
    });

    EXPECT_EQ(calculateMultiplicity(f, g), calculateMultiplicity(g, f));
}

// граничный случай 1 первый многочлен пустой f = 0
// алгоритм не должен падать например при делении на ноль и должен вернуть 0
TEST(MultiplicityTest, ZeroPolynomialFirst_ReturnsZero) {
    Polynomial zero;
    Polynomial g = makePolynomial({ Monom(1, 2, 0) }); // x^2

    EXPECT_EQ(calculateMultiplicity(zero, g), 0); 
}

// граничный случай 2 второй многочлен пустой g = 0
// то же самое но проверяем другой порядок аргументов
TEST(MultiplicityTest, ZeroPolynomialSecond_ReturnsZero) {
    Polynomial f = makePolynomial({ Monom(1, 2, 0) }); // x^2
    Polynomial zero;

    EXPECT_EQ(calculateMultiplicity(f, zero), 0); 
}