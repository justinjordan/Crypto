#include "crypto.h"

const std::string Crypto::extension = ".crp";

char Crypto::encode( char data, char key ) {
    return data ^ key;
}

bool Crypto::is_crypto_file( std::string filename ) {

    if ( filename.find(extension) != std::string::npos )
        return true;

    return false;
}

bool Crypto::file_exists ( std::string filename ) {
    std::ifstream f(filename.c_str());
    bool output = f.good();
    f.close();

    return output;
}

bool Crypto::encryptFile( std::string filename, std::string password ) {

    // Initialize Variables
    int fileSize, progressBarWidth, w;
    char data, key;
    double ratio;
    std::string cipher;

    // Open file streams
    std::ifstream ifs(filename, std::ios::in|std::ios::binary);
    std::ofstream ofs(filename + extension, std::ios::out|std::ios::binary);

    // encrypt password
    cipher = getHash(password.c_str());

    // Get file size
    ifs.seekg( 0, std::ios::end ); // goto end of file
    fileSize = ifs.tellg(); // get file pointer position, or last byte position (size)
    ifs.seekg( 0, std::ios::beg ); // go back to beginning

    // Setup progress display
    progressBarWidth = 30;

    // Hide cursor
    printf("\e[?25l");

    // Parse and Encrypt
    data = ifs.get();
    for ( int i = 0; ifs.good(); i++ ) {

        // Display progress every kilobyte
        if ( i % 1024 == 0 ) {
            ratio = i / (float)fileSize;

            printf("  [");

            w = progressBarWidth * ratio + 1;
            for ( int x = 0; x < w; x++ ) {
                printf("=");
            }
            for ( int x = w; x < progressBarWidth; x++ ) {
                printf(" ");
            }

            printf("]  %3d%%  ", (int)( ratio * 100 + 1 ));

            printf("\r");
        }

        // Get byte key
        key = cipher[ i % cipher.length() ];

        // Encode and write to new file
        ofs << encode( data, key );

        // Get next byte
        data = ifs.get();
    }

    printf("  [");
    for ( int x = 0; x < progressBarWidth; x++ ) {
        printf("=");
    }
    printf("]  100%%  ");
    printf("\n\n  Done!\n");

    // Show cursor
    printf("\e[?25h");

    // Close file streams
    ifs.close();
    ofs.close();

    // TODO:  Copy file permissions from original to the new one.

    std::remove(filename.c_str()); // remove original file

    return true;
}

bool Crypto::decryptFile( std::string filename, std::string password ) {

    int extPos = filename.find(extension);
    if ( extPos == std::string::npos )
        return false; // throw error

    std::string originalFileName = filename.substr(0, extPos);
    std::string newFileName = originalFileName;
    std::string decryptFileName = filename + extension;
    int dotPos;

    for ( int i = 2; file_exists(newFileName); i++ ) {
        newFileName = originalFileName;
        dotPos = newFileName.find(".");
        if ( dotPos == std::string::npos ) dotPos = newFileName.length();

        newFileName.insert(dotPos, std::to_string(i));
    }

    bool success = encryptFile(filename, password);

    rename(decryptFileName.c_str(), newFileName.c_str());


    return success;

}

std::string Crypto::getHash( const char* string ) {

    unsigned char digest[SHA256_DIGEST_LENGTH];

    SHA256((const unsigned char*)string, strlen((const char*)string), (unsigned char*)&digest);

    char mdString[SHA256_DIGEST_LENGTH*2+1];

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    std::string output = mdString;

    return output;
}
