# Project documentation
## MathHelper
Useful mathematical tools.
- **is_prime(number, iterations)**

Perform Miller-Rabin primality test executed in `iterations` iterations (by default set to 10).

- **factor($|E(F_p)|$)**

Factorize and order of a elliptic curve and output an array `{h, n}` with small `h` determined\
by `MAX_COFACTOR`. If `h` is too large return `{0, 0}`

- **is_residue(value)**

Calculates the Legrende symbol of `value` using Euler's criterion $value^{(p-1)/2}\pmod p$.
Output determines if `value` has a square root:
1. Returns `1` if `value` is a quadratic residue - it has two roots
2. Returns `0` if `value` is 0 - it has one root equal 0.
3. Returns `-1` if `value` is quadratic nonresidue.

## Point
Arithmetics on points of a elliptic curve.
- **addition (operator+)**

Adding two points of a elliptic curve according to standard formulas.

- **multiplication (operator\*)**

We used double and add algorithm for faster computations.

- **find_generator(curve, {h, n})**

Return generator point `G`. This is achieved by selecting random point `P` and calculating `G = h * P` 
(h is the cofactor of a curve). This operation guarantees that `G` is a generator of the subgroup
of order `n` according to [Lagrange's theorem](https://en.wikipedia.org/wiki/Lagrange%27s_theorem_(group_theory)).

## Int

- **pow(exp)**

Binary exponentiation for faster computations.

## ECHelper

- **find_order(EC)**

Brute force every possible `x` coordinate of a elliptic curve and then check if given `x` is a square residue.
If it is (meaning the output of `is_residue(x)` is 1) it adds 2 points to the counter, otherwise if `is_residue(x)` outputs 0
it adds 1 point to the counter and in other case, the point is not a part of a curve.

- **find_root_mod(value)**

Implementation of [Tonelli-Shanks](https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm) algorithm.
The function outputs $R$ as result of $R^2 = value$. The second result is $-R$ (which is equal to $p - R \pmod p$)

- **pick_random_point(EC)**

Return random point on a curve by picking random $x$ and searching for its corresponding $y$ value.

## ECDH

- **get_public_key()**

Return public key, which is exual to $\text{private_key} \times G$, private_key is a random value in range `[1, n - 1]`.

- **calculate_shared_secret(other_public_key)**

Calculate the shared secret value by multiplying values of private_key and other_public_key.

## ECDSA

- **sign(message)**

Generates a digital signature {r, s} for the given message. It calculates $r = (k \times G).x \pmod n$ and $s = k^{-1}(z + r \times d_A) \pmod n$, where $z$ is a hash of the message, $k$ is a random nonce in range `[1, n - 1]`, and $d_A$ is the private key. Returns a Signature struct.

- **verify(message, sig, public_key, curve, G, n, p)**

Verifies if the signature sig is valid for the message and public_key. It computes $u1 = z \times s^{-1} \pmod n$, and $u_2 = r \times s^{-1} \pmod n$. It then calculates the point $P = u1 \times G + u_2 \times \text{public_key}$ (using mod p arithmetic). The signature is valid if $P.x \pmod n == r$. Returns true or false.
