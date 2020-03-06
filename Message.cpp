#include "Message.h"

Message::Message(){}

Message::~Message(){}

void Message::readBitsFromKeyboard(){
    string str;
    int number = 8;
    while (1)
    {
        str = "";
        cout << "\nPodaj " << number << " bitow wiadomosci:\n";
        cin >> str;
        if (!checkString(str) || str.size() != number)
        {
            cout << "Podano nieprawidlowa wiadomosc!";
        } else
        {
            bitset<8> tmpBitset(str);
            msg_t tmpMsg;
            tmpMsg.bit = tmpBitset;
            msg.push_back(tmpMsg);
            return;
        }
    }
}

void Message::readErrorBitsFromKeyboard(){
    string str;
    int number = 8;
    while(1){
        str = "";
        cout << "\nPodaj wiadomosc z jednym bledem:\n";
        cin >> str;
        if( !checkString(str) || str.size() != number*2 ) {
            cout << "Podano nieprawidlowa wiadomosc!";
        }
        else {
            msg_t tmpMsg;
            string tmpStr = str.substr(8,8);
            bitset<8> tmpBitset(tmpStr);
            tmpMsg.parityBit = tmpBitset;
            tmpStr = str.substr(0,8);
            bitset<8> tmpBitset2(tmpStr);
            tmpMsg.bit = tmpBitset2;
            errorMsg.push_back(tmpMsg);
            return;
        }
    }
}

bool Message::checkString(string str) {
    for( auto & x : str ){
        if( x != '0' && x != '1' ) {
            return false;
        }
    }
    return true;
}

void Message::printBits() {
    for(auto & i : msg) {
        cout << i.bit.to_string() << " " << i.parityBit.to_string() << endl;
    }
}

void Message::printErrorBits() {
    for(auto & i : errorMsg) {
        cout << i.bit.to_string() << " " << i.parityBit.to_string() << endl;
    }
}

void Message::encode() {
    int counter;
    string tmpString = "";
    for( int i = 0; i < 8; i++){
        counter = 0;
        for( int j = 0; j < 8; j++){
            if( msg[0].bit[7-j] & matrix2[i][j] ) {
                counter++;
            }
        }
        if( (counter%2) == 1 ){
            tmpString += "1";
        }
        else{
            tmpString += "0";
        }
    }
    bitset<8> tmpBitset(tmpString);
    msg[0].parityBit = tmpBitset;
}

