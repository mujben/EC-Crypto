#include <sstream>
#include <iomanip>
#include "sodium.h"
#include "Point.h"

const int key_length = 32;

void key_from_point(Point shared_secret, unsigned char* key) {
    string point_str = string(shared_secret);
    crypto_generichash(
        key, key_length,
        (unsigned char*)point_str.c_str(), point_str.length(),
        NULL, 0);
}

string encrypt(const string& message, Point shared_secret) {
    unsigned char key[key_length];
    key_from_point(shared_secret, key);

    string ciphertext;

    for (size_t i = 0; i < message.size(); i++) {
        ciphertext += message[i] ^ key[i % sizeof(key)];
    }

    ostringstream hexstream;
    for (unsigned char c : ciphertext) {
        hexstream << setw(2) << setfill('0') << std::hex << (int)c;
    }
    string hexstr = hexstream.str();

    return hexstr;
}

string decrypt(const string& message, Point shared_secret) {
    unsigned char key[key_length];
    key_from_point(shared_secret, key);

    string ciphertext;
    for (size_t i = 0; i < message.length(); i += 2) {
        unsigned int byte;
        stringstream ss;
        ss << hex << message.substr(i, 2);
        ss >> byte;
        ciphertext += (unsigned char)(byte);
    }

    string result;
    for (size_t i = 0; i < ciphertext.size(); i++) {
        result += ciphertext[i] ^ key[i % sizeof(key)];
    }

    return result;
}