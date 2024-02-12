#ifndef DOMACI6_HASHTABLE_H
#define DOMACI6_HASHTABLE_H

#include "AddressFunction.h"
#include "QuadraticHashing.h"
#include <iostream>

using namespace std;

class HashTable {
public:
    HashTable(unsigned int size);

    string* findKey(int key);

    string* findKeyStats(int key);

    //string* search(int key);

    bool insertKey(int key, const string& s, bool adaptive = true);

    bool deleteKey(unsigned int key);

    double avgAccessSuccess();
    double avgAccessSuccessV();

    double avgAccessUnsuccess();
    double avgAccessUnsuccessV();

    double avgAccessUnsuccessEst();

    void resetStatistics();

    void clear();

    unsigned int keyCount();

    unsigned int tableSize();

    friend ostream& operator<<(ostream& os, const HashTable& ht);

    double fillRatio();

    ~HashTable() {
        delete addressFunction;
        clear();
        delete hashTable;
    }

    struct KeyValue {
        int key;
        string value;
        bool deleted;
        KeyValue(int key,const string& value) : key(key), value(value), deleted(false) {}
    };
private:
    AddressFunction* addressFunction;
    KeyValue** hashTable;
    unsigned int size;
    unsigned int keyCounter;
    unsigned int accessCount;

    unsigned int accessSuccessful = 0;
    unsigned int numOfSuccessful = 0;
    unsigned int accessUnsuccessful = 0;
    unsigned int numOfUnsuccessful = 0;

    int hashing(int addr) {return addr % size;}
};


#endif //DOMACI6_HASHTABLE_H
