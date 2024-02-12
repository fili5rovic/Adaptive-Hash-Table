#include "HashTable.h"

HashTable::HashTable(unsigned int size) : size(size), addressFunction(new QuadraticHashing(1, 3)) {
    hashTable = new KeyValue *[size];
    for (int i = 0; i < size; ++i) {
        hashTable[i] = nullptr;
    }
    keyCounter = 0;
    accessCount = 0;
};


string *HashTable::findKey(int key) {
    for (int i = 0;; ++i) {
        int address = hashing(key);
        int addressCollision = addressFunction->getAddress(key, address, i);
        // ponovno hesiranje, jer addressFunction vraca nehesiranu vrednost
        addressCollision = hashing(addressCollision);
        if (hashTable[addressCollision] == nullptr) {
            return nullptr;
        } else if (hashTable[addressCollision]->key == key) {
            if (hashTable[addressCollision]->deleted)
                return nullptr;
            return &hashTable[addressCollision]->value;
        }
    }
}


string *HashTable::findKeyStats(int key) {
    int access = 0;
    for (int i = 0;; ++i) {
        access++;
        int address = hashing(key);
        int addressCollision = addressFunction->getAddress(key, address, i);
        // ponovno hesiranje, jer addressFunction vraca nehesiranu vrednost
        addressCollision = hashing(addressCollision);
        if (hashTable[addressCollision] == nullptr) {
            accessUnsuccessful += access;
            numOfUnsuccessful++;
            return nullptr;
        } else if (hashTable[addressCollision]->key == key) {
            if (hashTable[addressCollision]->deleted) {
                accessUnsuccessful += access;
                numOfUnsuccessful++;
                return nullptr;
            }
            accessSuccessful += access;
            numOfSuccessful++;
            return &hashTable[addressCollision]->value;
        }
    }
}


bool HashTable::insertKey(int key, const string &s, bool adaptive) {
    if (fillRatio() == 1.0) {
        cout << "Full HashTable!" << endl;
        return false;
    }
    KeyValue *k = new KeyValue(key, s);
    for (int i = 0;; i++) {
        accessCount++;
        int address = hashing(key);
        int addressCollision = addressFunction->getAddress(key, address, i);

        // ponovno hesiranje, jer addressFunction vraca nehesiranu vrednost
        addressCollision = hashing(addressCollision);

        if (hashTable[addressCollision] == nullptr) {
            hashTable[addressCollision] = k;
            keyCounter++;
            if (adaptive && (fillRatio() >= 0.75f || avgAccessSuccess() > 5)) {
                KeyValue **newHashTable = new KeyValue *[2 * size];
                int j;
                for (j = 0; j < size; ++j) {
                    newHashTable[j] = hashTable[j];
                }
                for (; j < 2 * size; ++j) {
                    newHashTable[j] = nullptr;
                }
                size *= 2;
                delete hashTable;
                hashTable = newHashTable;
            }
            return true;
        } else if (hashTable[addressCollision]->key == key) {
            if(hashTable[addressCollision]->deleted) { // check
                hashTable[addressCollision] = k;
                keyCounter++;
                return true;
            }
            return false;
        }

    }
}

unsigned int HashTable::tableSize() { return this->size; }

double HashTable::fillRatio() { return keyCounter * 1.0 / size; }

unsigned int HashTable::keyCount() { return keyCounter; }

ostream &operator<<(ostream &os, const HashTable &ht) {
    cout << "-----------------" << endl;
    for (int i = 0; i < ht.size; ++i)
        if (ht.hashTable[i] == nullptr)
            cout << "EMPTY" << endl;
        else if (!ht.hashTable[i]->deleted)
            os << ht.hashTable[i]->value << endl;
        else
            os << "DELETED" << endl;
    cout << "-----------------" << endl;
    return os;
}

double HashTable::avgAccessSuccess() {
    if(!numOfSuccessful) return 0;
    return accessSuccessful * 1.0 / numOfSuccessful;
}

double HashTable::avgAccessSuccessV() {
    if(!keyCounter) return 0;
    return accessCount * 1.0 / keyCounter;
}


double HashTable::avgAccessUnsuccessV() {
    int size = this->tableSize();
    int numberOfElements = this->keyCount(), numEmpty = size - numberOfElements;
    double average_accesses = 0.0;
    average_accesses += numEmpty * 1.0 / size;
    for (int n = 2; n < size; ++n) {
        double prob_chain = numEmpty * 1.0 / size;
        for (int k = 1; k < n - 1; ++k) {
            prob_chain *= (numEmpty - k) * 1.0 / (size - k);
        }
        prob_chain *= numEmpty * 1.0 / (size - n + 1);
        average_accesses += n * prob_chain;
    }

    return average_accesses;
}


double HashTable::avgAccessUnsuccess() {
    if(!numOfUnsuccessful) return 0;
    return accessUnsuccessful * 1.0 / numOfUnsuccessful;
}


void HashTable::clear() {
    for (int i = 0; i < size; ++i) {
        delete hashTable[i];
        hashTable[i] = nullptr;
    }
}


void HashTable::resetStatistics() {
    accessSuccessful = accessUnsuccessful = 0;
    numOfSuccessful = numOfUnsuccessful = 0;
}


bool HashTable::deleteKey(unsigned int key) {
    for (int i = 0; i < size * 10; i++) {
        int address = hashing(key);
        int addressCollision = addressFunction->getAddress(key, address, i);
        // ponovno hesiranje, jer addressFunction vraca nehesiranu vrednost
        addressCollision = hashing(addressCollision);
        if (hashTable[addressCollision] == nullptr)
            return false;
        if (hashTable[addressCollision]->key == key) {
            hashTable[addressCollision]->deleted = true;
            keyCounter--;
            return true;
        }
    }
    return false;
}


double HashTable::avgAccessUnsuccessEst() {
    return 1 / (1.0 - fillRatio());
}

