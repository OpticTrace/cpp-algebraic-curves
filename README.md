# Calculating the Intersection Multiplicity of Algebraic Curves

## About the Project
This project is a **C++ refactoring** of an existing Python script. The application implements an algorithm to calculate the local intersection multiplicity of two algebraic curves:
> **f(x, y) = 0** and **g(x, y) = 0** at the origin **(0, 0)**

The mathematical logic is based on [**Lecture 10**](lectures/lect10.pdf): we repeatedly subtract a multiple of one polynomial from the other to eliminate the highest degree terms of **x**, until one of the polynomials is divisible by **y**.

**Project Goal:** Practice C++ Object-Oriented Programming (Classes and Object Lifecycle) by turning a messy script into a clean, readable, and well-structured program.


## Progress Checklist

### 1. Class `Monom` (Single Term)
Represents a single term in the form of **c·xᵃ·yᵇ**.
- [x] Struct definition and constructor `Monom(coeff, power_x, power_y)`
- [x] Overload the `<<` operator for easy printing (e.g., `2·x^2·y^1`)

### 2. Class `Polynomial`
Stores a collection of monomials using `std::vector<Monom>`.
- [x] Class definition and `std::vector<Monom>` attribute
- [x] `addMonomial(Monom m)` — Adds a monomial to the polynomial
- [x] `simplify()` — Combines like terms and removes zero coefficients
- [x] `sort()` — Sort terms in lexicographical order (highest degrees first)
- [x] `print()` — Helper method for debugging output
- [x] `isFree()` — Checks if there is a constant term
- [x] `getMaxDegreeX()` — Finds the highest power of **x** (assuming **y = 0**)
- [x] `getCoeffAtMaxX()` — Finds the coefficient of the highest power of **x** (assuming **y = 0**)
- [x] `getMinDegreeX()` — Finds the lowest power of **x**
- [x] `divideByX(int n)` — Divides the whole polynomial by **xⁿ**
- [x] `divideByY(int n)` — Divides the whole polynomial by **yⁿ**
- [x] `subtractMultipleOf(...)` — **CORE METHOD:** Subtracts **other · coeff · xᵐ** from the current polynomial (eliminates highest degree of **x**)

### 3. Core Algorithm: `calculateMultiplicity(f, g)`
- [ ] Check for free terms (return `0` if found)
- [ ] Implement the main `while` loop until one polynomial is divisible by **y**
- [ ] Implement the logic to subtract the polynomial with the highest degree of **x**
- [ ] Implement factoring out **y** and adding `m(f, y)` to the result

### 4. Function `main`
- [ ] Take input from the user to build the two polynomials
- [ ] Call `calculateMultiplicity`
- [ ] Print the final result

## Technical Notes (Implementation Details)
*   **Data Types:** Used `double` instead of `int` for coefficients to prevent precision loss during division in the `subtractMultipleOf` step.
*   **Floating-point comparisons:** Used an epsilon (`1e-9`) to safely compare `double` coefficients to zero.
*   **Immutability:** `Monom` is implemented as a `struct` with public fields (Value Semantics), while `Polynomial` encapsulates its data in `private` to maintain invariants.
