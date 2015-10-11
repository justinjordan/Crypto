#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <csignal>
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

        if ( argc < 4 )
            throw 0;

        inputFile = argv[2];
        password = argv[3];

        // ==== ENCRYPT ====
        if ( strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0 ) {

            std::cout << "  Encrypting " << inputFile << "...\n\n";

            if ( Crypto::is_crypto_file(inputFile) )
                throw 3;

            if ( !Crypto::encryptFile(inputFile, password) )
                throw 2;

        // ==== DECRYPT ====
        } else if ( strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0 ) {

            std::cout << "  Decrypting " << inputFile << "...\n\n";

            if ( !Crypto::is_crypto_file(inputFile) )
                throw 4;

            if ( !Crypto::decryptFile(inputFile, password) )
                throw 2;

        } else {
            throw 0;
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
