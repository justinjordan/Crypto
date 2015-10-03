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

void Crypto::generatePrimeSequence( char (&target)[16] ) {

    srand(time(NULL)); // seed rand

    char primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
    int randomIndex;

    for ( int i = 0; i < sizeof(target); i++ ) {
        randomIndex = rand() % 16;
        target[i] = primes[randomIndex];
    }

}

bool Crypto::is_prime( char byte ) {

    if ( byte == 2 ) { // 2 is prime... duh
        return true;
    } else if ( byte > 2 && byte%2 != 0 ) { // can be prime

        for ( int i = 3; i*i <= byte; i++ ) { // only check divisors less than square root

            if ( byte%i == 0 )
                return false;
        }

        return true; // can't be anything but prime
    }

    return false;

}
