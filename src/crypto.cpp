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

void Crypto::encryptFile( std::string filename, std::string cipher ) {

    // Initialize Variables
    int fileSize;
    char data, key;

    // Open file streams
    std::ifstream ifs(filename, std::ios::in|std::ios::binary);
    std::ofstream ofs(filename + extension, std::ios::out|std::ios::binary);

    // TODO:  Generate password hash and prepend it to new file.

    // Get file size
    ifs.seekg( 0, std::ios::end ); // goto end of file
    fileSize = ifs.tellg(); // get file pointer position, or last byte position (size)
    ifs.seekg( 0, std::ios::beg ); // go back to beginning

    // Parse and Encrypt
    data = ifs.get();
    for ( int i = 0; ifs.good(); i++ ) {

        // Get byte key
        key = cipher[ i % cipher.length() ];

        // Encode and write to new file
        ofs << encode( data, key );

        // Get next byte
        data = ifs.get();
    }

    // Close file streams
    ifs.close();
    ofs.close();

    // TODO:  Copy file permissions from original to the new one.

    std::remove(filename.c_str()); // remove original file
}
