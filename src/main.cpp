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

        string inputFile = argv[2];
        string cipher = argv[3];
        string cryptExt = ".crypto";

        // ENCRYPT
        if ( strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0 ) {

            ifstream ifs;
            ifs.open(inputFile, ifstream::in | ifstream::binary);

            string outputFile = inputFile;
            outputFile += cryptExt;
            ofstream ofs;
            ofs.open(outputFile, ofstream::out | ifstream::binary);

            // Display Message
            cout << "  Encrypting " << argv[2] << "... ";

            unsigned char c = ifs.get();
            for ( int i = 0; ifs.good(); i++ ) {
                c = Crypto::encryptChar(c, cipher[ i % cipher.length() ]);

                ofs << c;
                c = ifs.get();
            }

            ifs.close();
            ofs.close();

            remove(argv[2]);

        // DECRYPT
        } else if ( strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0 ) {

            char answer;
            cout << "  WARNING:" << endl <<
            "  If the password you provided is incorrect" << endl <<
            "  the file will be reverse encrypted." << endl <<
            endl <<
            "  Would you like to continue? (y or n)  ";
            cin >> answer;
            if ( answer == 'n' || answer == 'N' )
                throw 1;
            cout << "\n\n";

            ifstream ifs;
            ifs.open(inputFile, ifstream::in | ifstream::binary);

            string outputFile = inputFile.substr(0, inputFile.length() - cryptExt.length());
            ofstream ofs;
            ofs.open(outputFile, ofstream::out | ifstream::binary);

            // Display Message
            cout << "  Decrypting " << argv[2] << "... ";

            unsigned char c = ifs.get();
            for ( int i = 0; ifs.good(); i++ ) {
                c = Crypto::decryptChar(c, cipher[ i % cipher.length() ]);

                ofs << c;
                c = ifs.get();
            }

            ifs.close();
            ofs.close();

            remove(argv[2]);
        } else {
            throw 0;
        }


        cout << "Done!" << endl;

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
