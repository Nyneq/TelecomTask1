#include "Message.h"

int main() {
    Message m;
    m.readBaseMsg();        // Read message as binary from file msg.txt
    m.encode();             // Add securing bits to message
    m.writeEncodedMsg();    // Write secured message to file encodedMsg.txt bits represented by chars
    cout << "Wprowadz zmiany w pliku encodedMsg.txt a nastepnie kontynuuj prace programu.'\n";
    system("pause");
    m.readMsgWithErorrs();       // Read message from encodedMsg.txt file has 0 / 1 chars read them as bits
    m.correctErrors();
    m.writeCorrected();

    return 0;
}