#ifndef CRYPTO_H
#define CRYPTO_H

#include <climits>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

class Crypto {
public:
    static const std::string extension;
    static char encode( char data, char key );
    static bool is_crypto_file( std::string filename );
};

#endif
