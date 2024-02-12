#ifndef DOMACI6_QUADRATICHASHING_H
#define DOMACI6_QUADRATICHASHING_H


#include "AddressFunction.h"

class QuadraticHashing : public AddressFunction {
public:
    QuadraticHashing(int c1, int c2) : c1(c1), c2(c2) {}
    virtual int getAddress(unsigned int key,unsigned int address,unsigned int attempt) const override;
private:
    int c1,c2;
};


#endif //DOMACI6_QUADRATICHASHING_H
