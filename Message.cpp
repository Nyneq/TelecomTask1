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
    string fileName = R"(E:\Studia\Semestr4\Telekomunikacja\Task1\msg.txt)";
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
    string fileName = R"(E:\Studia\Semestr4\Telekomunikacja\Task1\encodedMsg.txt)";
    char tmpChar;
    fstream File;
    File.open(fileName, ios::out | ios::binary);
    if( !File.is_open() ){
        cout << "\nNie udalo sie zapisac zakodowanej wiadomosci do pliku.\n";
    }
    else {
        for (auto &z : msg) {
            tmpChar = z.bit.to_ulong();
            File.put(tmpChar);
            tmpChar = z.parityBit.to_ulong();
            File.put(tmpChar);
        }
    }
    File.close();
}

void Message::readMsgWithErorrs() {
    msg.clear();
    string fileName = R"(E:\Studia\Semestr4\Telekomunikacja\Task1\encodedMsg.txt)";
    char x = 0;
    fstream File;
    File.open(fileName, ios::in | ios::binary);
    if( !File.is_open() ) {
        cout << "\nNie mozna bylo odczytac pliku.\n";
    }
    else {
        msg_t tmpMsg;
        string tmpString = "";
        int y;
        bool flag = true;
        while( File.get(x) ) {
            if(flag){
                y = x;
                bitset<8> tmpBitset(y);
                tmpMsg.bit = tmpBitset;
                flag = false;
            } else {
                y = x;
                bitset<8> tmpBitset(y);
                tmpMsg.parityBit = tmpBitset;
                msg.push_back(tmpMsg);
                flag = true;
            }

            /*
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
            */
        }
    }
    File.close();
}

void Message::correctErrors()
{
    bool tmpBool;
    bitset<8> tmpBitset;
    for (auto &x : msg)
    {
        tmpBitset.reset();
        for (int i = 0; i < 8; i++)
        {
            tmpBool = false;
            for (int j = 0; j < 16; j++)
            {
                if (j < 8) {
                    tmpBool ^= (x.bit[7 - j] & matrix[i][j]);
                } else {
                    tmpBool ^= (x.parityBit[15 - j] & matrix[i][j]);
                }
            }
            tmpBitset[7 - i] = tmpBool;
        }
        // Checking if any bits changed
        if (tmpBitset.any())
        {
            for (int k = 0; k < 16; k++) {
                for (int l = 0; l < 8; l++) {
                    if (matrix[l][k] != tmpBitset[7 - l]) break;
                    if (l == 7) {
                        if (k < 8) {
                            x.bit.flip(7 - k);
                        } else x.parityBit.flip(7 - (k % 8));
                    }
                }
            }
                // Checking for two bits changed
                vector<bool> tmpBoolVec;
                bool changedBitsMatch;
                for (int i = 0; i < 15; ++i)
                {
                    for( int n = i+1; n < 16; n++)
                    {
                        tmpBoolVec.clear();
                        int sameBitsCount = 0;
                        changedBitsMatch = false;
                        for (int j = 0; j < 8; j++)
                        {
                            tmpBoolVec.push_back(matrix[j][i] ^ matrix[j][n]);
                        }
                        for (int m = 0; m < 8; m++)
                        {
                            if (tmpBitset[7 - m] != tmpBoolVec[m]) break;
                            sameBitsCount +=1 ;
                            if( sameBitsCount == 8 ) changedBitsMatch = true;
                        }
                        if (changedBitsMatch)
                        {
                            if (i < 8)
                            {
                                x.bit.flip(7 - i);
                            } else
                            {
                                x.parityBit.flip(7-(i % 8));
                            }
                            if( n < 8 )
                            {
                                x.bit.flip(7 - n);
                            } else
                            {
                                x.parityBit.flip(7-(n % 8));
                            }
                        }
                    }
                }
            }
        }
    }

void Message::writeCorrected() {
    string fileName = R"(E:\Studia\Semestr4\Telekomunikacja\Task1\correctedMsg.txt)";
    char c;
    fstream File;
    File.open(fileName, ios::out | ios::binary);
    if( !File.is_open() ){
        cout << "\nNie udalo sie zapisac zakodowanej wiadomosci do pliku.\n";
    }
    else {
        for (auto &z : msg) {
            c = z.bit.to_ulong();
            File.put(c);
        }
    }
    File.clear();
}