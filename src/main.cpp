#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <csignal>
#include <vector>
#include "crypto.h"

void close_handler(int signum) {

    // Print leave message
    printf ("\n\n  Good bye!\n\n");

    // Show cursor
    printf("\e[?25h");

    // exit application
    exit(signum);

}

int main(int argc, char* argv[]) {

    std::string inputFile, password;
    signal(SIGINT, close_handler);

    std::cout << std::endl;

    try {

        // Parse arguments
        std::vector<std::string> files;
        std::string password;

        for ( int i = 1; i < argc; i++ ) {

            if ( i == argc-1 ) {
                password = argv[i];
            } else {
                files.push_back(argv[i]);
            }

        }

        if ( files.empty() || password.empty() ) {
            throw 0; // show info dialog
        }

        for ( int i = 0; i < files.size(); i++ ) {

            try {
                if ( Crypto::is_crypto_file(files[i]) ) {

                    /* ==== DECRYPT ==== */

                    printf( "  Decrypting %s...\n\n", files[i].c_str() );

                    if ( !Crypto::decryptFile(files[i], password) )
                        throw "Problem decrypting file!";

                } else {

                    /* ==== ENCRYPT ==== */

                    printf( "  Encrypting %s...\n\n", files[i].c_str() );

                    if ( !Crypto::encryptFile(files[i], password) )
                        throw "Problem encrypting file!";

                }
            } catch ( const char* e ) {
                printf("%s\n\n", e);
            }

        }

    } catch ( int e ) {

        switch (e) {
            case 0:
                std::cout <<
                "  *****************************************" << std::endl <<
                "  *    ______                             *" << std::endl <<
                "  *   / ____/___ __ __ ___ _______ ___    *" << std::endl <<
                "  *  | |    | , \\  V /| , \\|_   _|/ _ \\   *" << std::endl <<
                "  *  | |    |   / \\ / | __/  | | | | | |  *" << std::endl <<
                "  *  | |____| |\\\\ | | | |    | | | |_| |  *" << std::endl <<
                "  *   \\_____|_| \\\\|_| |_|    |_|  \\___/   *" << std::endl <<
                "  *                                       *" << std::endl <<
                "  * Beta Version - (c) 2015 Justin Jordan *" << std::endl <<
                "  *****************************************" << std::endl <<
                std::endl <<
                "    Usage:  crypto <mode> <file> <cipher>" << std::endl <<
                std::endl <<
                "    Modes:" << std::endl <<
                std::endl <<
                "        --encrypt or -e\t: Encrypt file." << std::endl <<
                "        --decrypt or -d\t: Decrypt file." << std::endl <<
                std::endl <<
                "    Example:" << std::endl <<
                std::endl <<
                "        crypto -e file.txt password123" << std::endl;


                break;
            case 1:
                printf("\033[1;31m  Canceled!\033[0m\n");
                break;
            case 2:
                printf("\033[1;31m  Error!\033[0m\n");
                break;
            case 3:
                printf("\033[1;31m  %s is already encrypted!\033[0m\n", inputFile.c_str());
                break;
            case 4:
                printf("\033[1;31m  %s is not encrypted!\033[0m\n", inputFile.c_str());
                break;

        }

    }

    std::cout << std::endl;

    return 0;
}
