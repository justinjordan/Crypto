#ifndef CRYPTO_H
#define CRYPTO_H

#include <climits>
#include "types.h"

class Crypto {
public:
    static char encode( char data, char key );
};

#endif
