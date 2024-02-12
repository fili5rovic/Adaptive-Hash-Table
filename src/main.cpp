#include "HashTable.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


//<editor-fold desc="Ispisi">
const char topLeftCorner = '\xDA';
const char bottomLeftCorner = '\xC0';
const char topRightCorner = '\xBF';
const char bottomRightCorner = '\xD9';
const char middleLeftCorner = '\xC3';
const char middleRightCorner = '\xB4';
const char horizontalLine = '\xC4';
const char verticalLine = '\xB3';
const char intersection = '\xC5';
const char middleDown = '\xC2';
const char middleUp = '\xC1';
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string RESET = "\033[0m";
const string BOLD = "\033[1m";

string printline(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += '\xC4';
    }
    return s;
}

string printspace(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += ' ';
    }
    return s;
}

void upperTableHeading(int n, bool closing = true, bool end = true) {
    cout << topLeftCorner << printline(n);
    if (closing) cout << topRightCorner;
    if (end) cout << endl;
}

void lowerTableHeading(int n, bool closing = true, bool end = true) {
    cout << bottomLeftCorner << printline(n);
    if (closing) cout << bottomRightCorner;
    if (end) cout << endl;
}

void newMenu(int line_len, int strlen, string options[], int pomeraj = 7) {
    cout << endl;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - options[0].length()) / 2) << options[0]
         << printspace((line_len - options[0].length()) / 2) << verticalLine << endl;
    cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    for (int i = 1; i < strlen; ++i) {
        cout << verticalLine << printspace(pomeraj) << options[i]
             << printspace((line_len - options[i].length()) - pomeraj) << verticalLine << endl;
        if (i < strlen - 1)
            cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    lowerTableHeading(line_len);
}

void newMessage(string poruka = "", int line_len = 40) {
    if (poruka.length() % 2) poruka += " ";
    cout << endl;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - poruka.length()) / 2) << poruka
         << printspace((line_len - poruka.length()) / 2) << verticalLine << endl;
    lowerTableHeading(line_len);
}

void newMessageGreen(string poruka = "", int line_len = 40) {
    if (poruka.length() % 2) poruka += " ";
    cout << endl << GREEN;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - poruka.length()) / 2) << poruka
         << printspace((line_len - poruka.length()) / 2) << verticalLine << endl;
    lowerTableHeading(line_len);
    cout << RESET;
}

void newMessageRed(string poruka = "", int line_len = 40) {
    if (poruka.length() % 2) poruka += " ";
    cout << endl << RED;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - poruka.length()) / 2) << poruka
         << printspace((line_len - poruka.length()) / 2) << verticalLine << endl;
    lowerTableHeading(line_len);
    cout << RESET;
}

//</editor-fold>

string doubleToStringWithoutTrailingZeros(double value) {
    std::ostringstream out;
    out << value;

    std::string str = out.str();

    // Uklanjanje nepotrebnih nula i decimalnog zareza
    size_t dotPos = str.find('.');
    if (dotPos != std::string::npos) {
        size_t nonZeroPos = str.find_last_not_of('0');
        if (nonZeroPos != std::string::npos && nonZeroPos > dotPos) {
            str.erase(nonZeroPos + 1);
        } else {
            str.erase(dotPos);
        }
    }

    return str;
}

int getNumOfLines(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }
    int num = 0;
    string linija;
    while (getline(file, linija)) {
        num++;
    }

    return num;
}

void insertToHashFromFile(HashTable &hashTable, const string &filename, bool adaptive) {
    ifstream file(filename);
    if (!file) {
        string msg = "Unable to open " + filename;
        newMessageRed(msg);
        return;
    }
    string line;
    int key;
    string stringPart;
    while (getline(file, line)) {
        istringstream iss(line);
        string keyString, valueString;

        std::getline(iss, stringPart, '\t');
        std::getline(iss, keyString);

        try {
            key = std::stoi(keyString); // Konvertuje string u int
            valueString = stringPart;
        } catch (const std::invalid_argument &ia) {
            cerr << "CONVERSION ERROR : " << keyString << endl;
            exit(1);
        }
        hashTable.insertKey(key, valueString, adaptive);
    }
    file.close();
    cout << endl;
}

void myTest() {
    HashTable hash1 = HashTable(9);

    hash1.insertKey(4319725, "zelje");
    hash1.insertKey(7543796, "fles");
    hash1.insertKey(2758090, "beograd");
    hash1.insertKey(2887584, "samo");
    hash1.insertKey(2554838, "14");
    hash1.insertKey(492320, "odsto");
    hash1.insertKey(2036857, "zitelja");
    hash1.insertKey(7850636, "srbije");
    hash1.insertKey(911048, "iskreno");

    cout << hash1.tableSize() << endl;
    cout << hash1;
}

void findKeyOption(HashTable &hashTable) {
    newMessage("Enter key:", 30);
    cout << "[key]=";

    int key;
    cin >> key;
    string *keyFound = hashTable.findKey(key), msg;

    if (keyFound) {
        msg = "Key '" + *keyFound + "' exists.";
        if (msg.length() % 2) msg += " ";
        newMessageGreen(msg, 50);
    } else {
        msg = "Key doesn't exist.";
        newMessageRed(msg, 50);

    }
}

void insertKeyOption(HashTable &hashTable, bool adaptive) {
    newMessage("Enter new data:", 30);
    cout << "[key value] =";

    int key;
    string value;
    cin >> key >> value;

    bool ok = hashTable.insertKey(key, value, adaptive);
    if (ok)
        newMessageGreen("Data successfully added to HashTable. ", 50);
    else
        newMessageRed("Key already exists inside HashTable. ", 50);
}

void deleteKeyOption(HashTable &hashTable) {
    newMessage("Enter key you wish to delete: ");
    cout << "[key] =";

    int key;
    cin >> key;
    bool ok = hashTable.deleteKey(key);

    if (ok)
        newMessageGreen("Data successfully deleted.", 50);
    else
        newMessageRed("Data couldn't be deleted.", 50);
}

void avgNum(HashTable &hashTable) {
    string numSucc = doubleToStringWithoutTrailingZeros(hashTable.avgAccessSuccessV());
    string numUnsuccEst = doubleToStringWithoutTrailingZeros(hashTable.avgAccessUnsuccessV());
    string numUnsucc = doubleToStringWithoutTrailingZeros(hashTable.avgAccessUnsuccessEst());

    if (numSucc.length() % 2)
        numSucc += " ";
    if (numUnsucc.length() % 2)
        numUnsucc += " ";
    if (numUnsuccEst.length() % 2)
        numUnsucc += " ";

    string msg = "Average successful access count: " + numSucc;
    if(msg.length() % 2) msg += " ";
    newMessage(msg, 50);

    msg = "Average unsuccessful access count: " + numUnsuccEst;
    if(msg.length() % 2) msg += " ";
    newMessage(msg, 50);
}

void statistics(HashTable &hashTable) {
    hashTable.resetStatistics();
    srand(27);

    int numOfRandom = 100000;
    int minVal = 1000000, maxVal = 10000000;
    int maxMinusMin = maxVal - minVal;
    for (int i = 0; i < numOfRandom; i++) {
        int randomNumber = maxMinusMin * (rand() * 1.0 / RAND_MAX) + minVal;
        hashTable.findKeyStats(randomNumber);
    }

    cout << endl << "----------------------------------------------------" << endl;

    string msg = "Average successful access count: " + to_string(hashTable.avgAccessSuccess());
    if (msg.length() % 2) msg += " ";
    newMessage(msg, 50);

    msg = "Average unsuccessful access count: " + to_string(hashTable.avgAccessUnsuccess());
    if (msg.length() % 2) msg += " ";
    newMessage(msg, 50);

    msg = "Key Count: " + to_string(hashTable.keyCount());
    if (msg.length() % 2) msg += " ";
    newMessage(msg, 50);

    msg = "Fill Ratio: " + doubleToStringWithoutTrailingZeros(hashTable.fillRatio() * 100) + "%";
    if (msg.length() % 2) msg += " ";
    newMessage(msg, 50);

    msg = "Size: " + to_string(hashTable.tableSize());
    if (msg.length() % 2) msg += " ";
    newMessage(msg, 50);

    cout << endl << "----------------------------------------------------" << endl;

//    cout << "KeyCount: " << hashTable.keyCount() << endl;
//    cout << "FillRatio: " << hashTable.fillRatio() << endl;
//    cout << "Table size: " << hashTable.tableSize() << endl;
//    cout << "USPESNO: " << hashTable.avgAccessSuccess() << endl;
//    cout << "NEUSPESNO: " << hashTable.avgAccessUnsuccess() << endl;
}

void menu() {
    int mainChoice;
    newMenu(46, 4,
            new string[]{"- MAIN MENU - ", "[1] Create HashTable From File", "[2] Create Adaptive HashTable From File",
                         "[0] Exit"}, 4);
    while (true) {
        cout << "->";
        cin >> mainChoice;
        if (!mainChoice) break;
        else if (mainChoice != 1 && mainChoice != 2) continue;

        bool adaptive = mainChoice - 1;
        const string filename = "DZ3_Recnik_10K.txt";
//        int size = getNumOfLines(filename);
        int size = 10000;
        HashTable hashTable = HashTable(size);
        insertToHashFromFile(hashTable, filename, adaptive);
        newMessageGreen("Successfully Created HashTable", 40);

        string *meni = new string[]{"- MAIN MENU - ", "[1] Find Key", "[2] Insert Key", "[3] Delete Key",
                                    "[4] Average Access Count", "[5] Statistics", "[6] Print HashTable",
                                    "[0] Exit"};
        int choice = 0;
        while (true) {
            cout << BOLD;
            newMenu(40, 8, meni);
            cout << "->" << RESET;
            cin >> choice;
            switch (choice) {
                case 1:
                    findKeyOption(hashTable);
                    break;
                case 2:
                    insertKeyOption(hashTable, adaptive);
                    break;
                case 3:
                    deleteKeyOption(hashTable);
                    break;
                case 4:
                    avgNum(hashTable);
                    break;
                case 5:
                    statistics(hashTable);
                    break;
                case 6:
                    cout << hashTable << endl;
                    break;
                case 0:
                    newMessageGreen("Program exited successfully!", 50);
                    return;
                default:
                    continue;
            }
        }
    }
    newMessageGreen("Program exited successfully!", 50);
}


int main() {
    menu();
    return 0;
}
