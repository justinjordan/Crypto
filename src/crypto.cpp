#include "crypto.h"

char Crypto::encode( char data, char key ) {
    return data ^ key;
}
