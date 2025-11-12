# Project documentation
## MathHelper
Useful mathematical tools.
- $\textbf{is_prime(number, iterations)}$

Perform Miller-Rabin primality test executed in `iterations` iterations (by default set to 10).

- $\textbf{factor(}$ $|E(F_p)|$ $\textbf{)}$

Factorize and order of a elliptic curve and output an array `{h, n}` with small h determined\
by `MAX_COFACTOR`. If `h` is too large return `{0, 0}`

- $\textbf{is_residue(value)}$

Calculates the Legrende symbol of `value` using Euler's criterion $value^{(p-1)/2}(mod$ $p)$.
Output determines if `value` has a square root:
1. Returns `1` if `value` is a quadratic residue - it has two roots
2. Returns `0` if `value` is 0 - it has one root equal 0.
3. Returns `-1` if `value` is quadratic nonresidue.

## Point
Arithmetics on points of a elliptic curve.
- $\textbf{addition (operator+)}$

Adding two points of a elliptic curve according to standard formulas.

- $\textbf{multiplication (operator*)}$

We used double and add algorithm for faster computations.

## Int

- $\textbf{pow(exp)}$

Binary exponentiation for faster computations.

## ECHelper

- $\textbf{find_order(EC)}$

Brute force every possible `x` coordinate of a elliptic curve and then check if given `x` is a square residue.
If it is (meaning the output of `is_residue(x)` is 1) it adds 2 points to the counter, otherwise if `is_residue(x)` outputs 0
it adds 1 point to the counter and in other case, the point is not a part of a curve.

- $\textbf{find_root_mod(value)}$

Implementation of [Tonelli-Shanks](https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm) algorithm.
The function outputs $R$ as result of $R^2 = value$. The second result is $-R$ (which is equal to $p - R (mod$ $p)$)

- $\textbf{pick_random_point(EC)}$

Return random point on a curve by picking random $x$ and searching for its corresponding $y$ value.