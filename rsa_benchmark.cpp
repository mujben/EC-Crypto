#include "cryptopp.h/rsa.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./" << argv[0] << " <rsa_public_key.pem> <file_to_encrypt>\n";
        return 1;
    }
    /*generation of 4096 bit key for both versions of rsa encryption
    ...
    */
    //importing ssl file as rsa public key to encrypt data
    if (FILE *rsa_public = fopen(argv[1], "rb"); !rsa_public) {
        std::cerr << "Failed to open file " << argv[1] << "\n";
        return -1;
    }

    return 0;
}