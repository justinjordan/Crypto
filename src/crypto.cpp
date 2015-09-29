#include "crypto.h"

unsigned char Crypto::encryptChar( unsigned char c, unsigned char key ) {
    c = (c + key) % UCHAR_MAX;

    return c;
}

unsigned char Crypto::decryptChar( unsigned char c, unsigned char key ) {
    int output = ((c<key)?UCHAR_MAX:0) + c - key;
    c = output;

    return c;
}
