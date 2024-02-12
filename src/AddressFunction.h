#ifndef DOMACI6_ADDRESSFUNCTION_H
#define DOMACI6_ADDRESSFUNCTION_H


class AddressFunction {
public:
    virtual int getAddress(unsigned int key,unsigned int address,unsigned int attempt) const = 0;

};


#endif //DOMACI6_ADDRESSFUNCTION_H
