#include "crypto.h"

const std::string Crypto::extension = ".crypto";

char Crypto::encode( char data, char key ) {
    return data ^ key;
}

bool Crypto::is_crypto_file( std::string filename ) {

    if ( filename.find(extension) != std::string::npos )
        return true;

    return false;
}
