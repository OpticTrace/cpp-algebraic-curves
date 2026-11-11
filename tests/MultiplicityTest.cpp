#include <gtest/gtest.h>
#include "Multiplicity.h"

// test 1: f = x^2 - y, g = x^3 - y^2
TEST(MultiplicityTest, BasicCase) {
    Polynomial f1;
    f1.addMonomial(Monom(1, 2, 0));
    f1.addMonomial(Monom(-1, 0, 1));

    Polynomial g1;
    g1.addMonomial(Monom(1, 3, 0));
    g1.addMonomial(Monom(-1, 0, 2));

    EXPECT_EQ(calculateMultiplicity(f1, g1), 3);
}

// test 2: f = x^3 - y^2, g = x^2 - y^3
TEST(MultiplicityTest, AnotherCase) {
    Polynomial f2;
    f2.addMonomial(Monom(1, 3, 0));
    f2.addMonomial(Monom(-1, 0, 2));

    Polynomial g2;
    g2.addMonomial(Monom(1, 2, 0));
    g2.addMonomial(Monom(-1, 0, 3));

    EXPECT_EQ(calculateMultiplicity(f2, g2), 4);
}