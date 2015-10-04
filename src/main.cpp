#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "crypto.h"
using namespace std;

int main(int argc, char* argv[]) {

    cout << endl;

    try {

        if ( argc < 4 )
            throw 0;

        std::string inputFile = argv[2];
        std::string password = argv[3];

        // ==== ENCRYPT ====
        if ( strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0 ) {

            cout << "  Encrypting " << inputFile << "...";

            Crypto::encryptFile(inputFile, password);

        // ==== DECRYPT ====
        } else if ( strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0 ) {



        } else {
            throw 0;
        }


        cout << "  Done!" << endl;

    } catch ( int e ) {

        switch (e) {
            case 0:
                cout <<
                "  *****************************************" << endl <<
                "  *    ______                             *" << endl <<
                "  *   / ____/___ __ __ ___ _______ ___    *" << endl <<
                "  *  | |    | , \\  V /| , \\|_   _|/ _ \\   *" << endl <<
                "  *  | |    |   / \\ / | __/  | | | | | |  *" << endl <<
                "  *  | |____| |\\\\ | | | |    | | | |_| |  *" << endl <<
                "  *   \\_____|_| \\\\|_| |_|    |_|  \\___/   *" << endl <<
                "  *                                       *" << endl <<
                "  * Beta Version - (c) 2015 Justin Jordan *" << endl <<
                "  *****************************************" << endl <<
                endl <<
                "    Usage:" << endl <<
                endl <<
                "        crypto <mode> <file> <cipher>" << endl <<
                endl <<
                "    Modes:" << endl <<
                endl <<
                "        --encrypt or -e\t: Encrypt file." << endl <<
                "        --decrypt or -d\t: Decrypt file." << endl <<
                endl <<
                "    Example:" << endl <<
                endl <<
                "        crypto -e file.txt password123" << endl;


                break;
            case 1:
                cout << "Canceled!" << endl;
        }

    }

    cout << endl;

    return 0;
}
