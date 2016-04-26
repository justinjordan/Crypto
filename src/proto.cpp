#include <cstdio>
#include <string>
#include "jcrypt.h"

int main(int argc, char* argv[]) {

    if ( argc > 1 ) {
        std::string salt = jcrypt::createSalt(4);
        std::string hash = jcrypt::createHash(argv[1], salt);

        printf("%s\n", hash.c_str());
    }

    return 0;
}
