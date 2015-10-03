#include "../src/crypto.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

SCENARIO( "file with special extension is recognized while other is rejected", "[extension]" ) {

    GIVEN( "filename with special extension" ) {

        std::string filename = "somefile.txt" + Crypto::extension;

        WHEN( "filename is checked for extension" ) {
            REQUIRE( Crypto::is_crypto_file(filename) == true );

            THEN( "special extension is removed" ) {
                filename = "somefile.txt";
                REQUIRE( Crypto::is_crypto_file(filename) == false );
            }
        }
    }

}

SCENARIO( "byte is encrypted, then decrypted", "[encrypt]" ) {

    GIVEN( "byte of data and key" ) {
        char data = 5;
        char key = 10;

        WHEN( "data is encrypted" ) {
            data = Crypto::encode(data, key);
            REQUIRE( data == 15 );

            THEN( "encrypted data is decrypted" ) {
                data = Crypto::encode(data, key);
                REQUIRE( data == 5 );
            }
        }
    }
}

SCENARIO( "is_prime function works", "[is_prime]") {

    REQUIRE( Crypto::is_prime(2) == true );
    REQUIRE( Crypto::is_prime(3) == true );
    REQUIRE( Crypto::is_prime(5) == true );
    REQUIRE( Crypto::is_prime(7) == true );
    REQUIRE( Crypto::is_prime(11) == true );

    REQUIRE( Crypto::is_prime(4) == false );
    REQUIRE( Crypto::is_prime(39) == false );
    REQUIRE( Crypto::is_prime(27) == false );
    REQUIRE( Crypto::is_prime(36) == false );
    REQUIRE( Crypto::is_prime(20) == false );

}

SCENARIO( "a series of 16 random prime bytes are generated", "[primesequence]" ) {

        GIVEN( "an empty char array" ) {
            char num[16];

            WHEN( "prime hash is generated" ) {
                Crypto::generatePrimeSequence(num);

                for ( int i = 0; i < sizeof(num); i++ ) {
                    CHECK( Crypto::is_prime(num[i]) );
                }
            }
        }
}
