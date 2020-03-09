#include "Message.h"

Message::Message(){}

Message::~Message(){}

void Message::printBits() {
    for(auto & i : msg) {
        cout << i.bit.to_string() << " " << i.parityBit.to_string() << endl;
    }
}

void Message::encode() {
    int counter;
    string tmpString;
    for (auto & k : msg)
    {
        tmpString = "";
        for (int i = 0; i < 8; i++)
        {
            counter = 0;
            for (int j = 0; j < 8; j++)
            {
                if (k.bit[7 - j] & matrix[i][j])
                {
                    counter++;
                }
            }
            if ((counter % 2) == 1)
            {
                tmpString += "1";
            } else
            {
                tmpString += "0";
            }
        }
        bitset<8> tmpBitset(tmpString);
        k.parityBit = tmpBitset;
    }
}

void Message::readBaseMsg() {
    string fileName = R"(E:\STUDIA\Semestr4\Telekom\TelecomTask1\msg.txt)";
    char x = 0;
    int y;
    msg.clear();
    fstream File;
    File.open(fileName, ios::in | ios::binary);
    if( !File.is_open() ) {
        cout << "\nNie mozna bylo odczytac pliku.\n";
    }
    else {
        while( File.get(x) ) {
            y = x;
            msg_t tmpMsg;
            bitset<8> tmpBitset(y);
            tmpMsg.bit = tmpBitset;
            msg.push_back(tmpMsg);
        }
    }
    File.close();
}

void Message::writeEncodedMsg() {
    string tmpString, fileName = R"(E:\STUDIA\Semestr4\Telekom\TelecomTask1\encodedMsg.txt)";
    fstream File;
    File.open(fileName, ios::out | ios::binary);
    if( !File.is_open() ){
        cout << "\nNie udalo sie zapisac zakodowanej wiadomosci do pliku.\n";
    }
    else {
        for (auto &z : msg) {
            tmpString = z.bit.to_string();
            for(char v : tmpString){
                File.put(v);
            }
            tmpString = z.parityBit.to_string();
            for(char v : tmpString){
                File.put(v);
            }
        }
    }
    File.close();
}

void Message::readMsgWithErorrs() {
    msg.clear();
    string fileName = R"(E:\STUDIA\Semestr4\Telekom\TelecomTask1\encodedMsg.txt)";
    char x = 0;
    fstream File;
    File.open(fileName, ios::in | ios::binary);
    if( !File.is_open() ) {
        cout << "\nNie mozna bylo odczytac pliku.\n";
    }
    else {
        msg_t tmpMsg;
        string tmpString = "";
        int bitCount = 0;
        while( File.get(x) ) {
            tmpString += x;
            if( bitCount == 7 ){
                bitset<8> tmpBitset(tmpString);
                tmpMsg.bit = tmpBitset;
                tmpString = "";
            }
            else if( bitCount == 15 ){
                bitset<8> tmpBitset(tmpString);
                tmpMsg.parityBit = tmpBitset;
                tmpString = "";
                bitCount = -1;
                msg.push_back(tmpMsg);
            }
            bitCount++;
        }
    }
    File.close();
}

void Message::correctErrors() {
    bool tmpBool;
    bitset<8> tmpBitset;
    for( auto &x : msg ) {
        tmpBitset.reset();
        for( int i = 0; i < 8; i++ ) {
            tmpBool = false;
            for( int j = 0; j < 16; j++) {
                if( j < 8 ) {
                    tmpBool ^= x.bit[7-j] & matrix[i][j];
                }
                else {
                    tmpBool ^= x.parityBit[15-j] & matrix[i][j];
                }
            }
            tmpBitset[7-i] = tmpBool;
        }
        // Checking if any bits changed
        if( tmpBitset.any() ){
            for(int k = 0; k < 16; k++) {
                for( int l = 0; l < 8; l++) {
                    if( matrix[l][k] != tmpBitset[7-l] ) break;
                }
                // correcting the bits
            }
        }
    }
}

