# Implementation of EC Cryptography
This repository focuses on implementing the **Elliptic Curve Cryptography (ECC)** algorithms in C++, along with its common applications such as **ECDH (Elliptic Curve Diffie–Hellman)** and **ECDSA (Elliptic Curve Digital Signature Algorithm)**.

**This project aims to:**
- Implement core elliptic curve operations over finite fields.
- Build cryptographic schemes based on ECC (key exchange and digital signatures).


## Dependencies
- libsodium (installed automatically during compilation)

## Compilation and usage (Linux 🐧)
### Prerequisites
```
sudo apt update
sudo apt install build-essential cmake git
```
### Build and Run
```
mkdir build
cd build
cmake -DBUILD_SRC=ON ..
make
cd src
./krypto
```

## Literature
- [Methods for computing the number of points of an elliptic curve](https://jtnb.centre-mersenne.org/article/JTNB_1995__7_1_219_0.pdf)
- [Tonelli-Shanks algorithm for computing square root of a number](https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm)
- [Lagrange's theorem](https://en.wikipedia.org/wiki/Lagrange%27s_theorem_(group_theory))
- AGH lectures: "Algebra" (dr Lech Adamus), "Selected Topic in Advanced Mathematics", "Cryptography" (prof. Piotr Chołda).
