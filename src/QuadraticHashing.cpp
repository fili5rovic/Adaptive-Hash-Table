#include "QuadraticHashing.h"

int QuadraticHashing::getAddress(unsigned int key, unsigned int address, unsigned int attempt) const{
    return address + attempt * c1 + attempt * attempt * c2;
}
