#ifndef CRYPTO_H
#define CRYPTO_H

#include <climits>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <openssl/sha.h>

class Crypto {
public:
    static const std::string extension;
    static char encode( char data, char key );
    static bool is_crypto_file( std::string filename );
    static bool file_exists ( std::string filename );
    static bool encryptFile( std::string filename, std::string password);
    static bool decryptFile( std::string filename, std::string password);
    static std::string getHash( const char* string );
};

#endif
