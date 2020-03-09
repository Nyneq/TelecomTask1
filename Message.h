#ifndef TK1_MESSAGE_H
#define TK1_MESSAGE_H

#include "iostream"
#include "bitset"
#include "vector"
#include "string"
#include "conio.h"
#include "fstream"

using namespace std;

struct msg_t{
    bitset<8> bit;
    bitset<8> parityBit;
};

class Message
{
private:
    vector< msg_t > msg;
    bool matrix[8][16] = {
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

    void readBaseMsg();

    void printBits();

    void encode();

    void writeEncodedMsg();

    void readMsgWithErorrs();

    void correctErrors();

    int cmpVectorNmatrix(bitset<8> bits, msg_t msg);
};


#endif
