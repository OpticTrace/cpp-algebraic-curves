# Calculating the Intersection Multiplicity of Algebraic Curves

## About the Project
This project is a **C++** refactoring of an existing **Python** script. The original code implements an algorithm to calculate the local intersection multiplicity of two algebraic curves:

> **f(x, y) = 0** and **g(x, y) = 0** at the origin **(0, 0)**

The mathematical logic is based on **Lecture 10**: we repeatedly subtract a multiple of one polynomial from the other to eliminate the highest degree terms of **x**, until one of the polynomials is divisible by **y**.

## Project Goal
To practice **C++** Object-Oriented Programming (specifically Topics **4.1 Classes** and **4.3 Object Lifecycle**) by turning a messy "spaghetti code" script into a clean, readable, and well-structured program.

---

## Technical Specification

### 1. Class `Monom` (Single Term)
Represents a single term in the form of **c · x<sup>a</sup> · y<sup>b</sup>**.

* **Attributes:**
  * `coeff` — the coefficient (**c**).
  * `power_x` — the power of **x** (**a**).
  * `power_y` — the power of **y** (**b**).
* **Methods:**
  * Constructor.
  * Overload the `<<` operator for easy printing (e.g., **2 · x<sup>2</sup> · y<sup>1</sup>**).

### 2. Class `Polynomial`
Stores a collection of monomials using `std::vector<Monom>`.

* **Methods:**
  * `simplify()` — Combines like terms (if `power_x` and `power_y` match, add the coefficients). Removes terms with zero coefficients.
  * `addMonomial(Monom m)` — Adds a monomial to the polynomial.
  * `isFree()` — Checks if there is a constant term (if yes, the intersection at the origin does not exist).
  * `getMaxDegreeX()` — Finds the highest power of **x** (assuming **y = 0**).
  * `getCoeffAtMaxX()` — Finds the coefficient of the highest power of **x**.
  * `getMinDegreeX()` — Finds the lowest power of **x** (used to check if the polynomial can be factored by **x**).
  * `divideByX(int n)` — Divides the whole polynomial by **x<sup>n</sup>** (subtracts n from all `power_x`).
  * `divideByY(int n)` — Divides the whole polynomial by **y<sup>n</sup>** (subtracts n from all `power_y`).
  * `subtractMultipleOf(Polynomial other, int mult_power, int coeff)` — **CORE METHOD:** Subtracts **other · coeff · x<sup>mult_power</sup>** from the current polynomial. This is the step that eliminates the highest degree of **x**.

### 3. Core Algorithm: `calculateMultiplicity(f, g)`
Returns an `int` (the multiplicity).

**Logic:**

1. If **f.isFree()** or **g.isFree()**, return **0**.
2. Loop until one of the polynomials is divisible by **y** (i.e., until **getMinDegreeX() > 0**).
3. Find the highest degrees: **deg_f = f.getMaxDegreeX()** and **deg_g = g.getMaxDegreeX()**.
4. If **deg_g >= deg_f**: subtract from **g** the polynomial **f** multiplied by **x<sup>(deg_g - deg_f)</sup>** and the ratio of their leading coefficients.
5. If **deg_f > deg_g**: subtract from **f** the polynomial **g** multiplied by **x<sup>(deg_f - deg_g)</sup>** and the ratio of their leading coefficients.
6. When one of them is divisible by **y**, use the property: **m(f, g · y) = m(f, y) + m(f, g)**. Factor out **y** and continue the algorithm.

### 4. Function `main`
* Take input from the user to build the two polynomials.
* Call `calculateMultiplicity`.
* Print the result.

