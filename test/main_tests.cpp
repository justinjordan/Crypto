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

SCENARIO( "encrypt password with SHA256 algorithm", "[gethash]" ) {

    GIVEN( "string representing password" ) {

        WHEN( "password is converted to SHA256 hash" ) {

            std::string hash = Crypto::getHash("123456seven");

            REQUIRE( hash == "f30cc8de61ec96e84fc3d279636c225906f12a60ecc8fe8c8a1bae2e2fc024bc" );

        }

    }

}
