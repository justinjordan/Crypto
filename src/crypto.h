#ifndef CRYPTO_H
#define CRYPTO_H

#include <climits>

class Crypto {
public:
    static unsigned char encryptChar( unsigned char c, unsigned char key );
    static unsigned char decryptChar( unsigned char c, unsigned char key );
};

#endif
