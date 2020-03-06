#ifndef TK1_MESSAGE_H
#define TK1_MESSAGE_H

#include "iostream"
#include "bitset"
#include "vector"
#include "string"
#include "conio.h"

using namespace std;

struct msg_t{
    bitset<8> bit;
    bitset<8> parityBit;
};

class Message
{
private:
    vector< msg_t > msg;
    vector< msg_t > errorMsg;
    bool matrix2[8][16] = {
            {1, 1, 1, 1, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 0, 0, 1, 1, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0,  0, 0, 1, 0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 1, 0,  0, 0, 0, 1, 0, 0, 0, 0},
            {1, 1, 1, 0, 1, 0, 0, 1,  0, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 1, 0, 1, 0, 1,  0, 0, 0, 0, 0, 1, 0, 0},
            {0, 1, 1, 1, 1, 0, 1, 1,  0, 0, 0, 0, 0, 0, 1, 0},
            {1, 1, 1, 0, 0, 1, 1, 1,  0, 0, 0, 0, 0, 0, 0, 1}};

public:
    Message();

    virtual ~Message();

    void readBitsFromKeyboard();

    void readErrorBitsFromKeyboard();

    bool checkString(string str);

    void printBits();

    void printErrorBits();

    void encode();

};


#endif
