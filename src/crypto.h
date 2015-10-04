#ifndef CRYPTO_H
#define CRYPTO_H

#include <climits>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

class Crypto {
public:
    static const std::string extension;
    static char encode( char data, char key );
    static bool is_crypto_file( std::string filename );
    static void encryptFile( std::string filename, std::string cipher );
};

#endif
