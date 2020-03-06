#include "Message.h"

int main()
{
    int taskNr;
    while(1) {

        cout << "Wybierz podpunkt zadania (1,2,3) lub 7 by opuscic program: ";
        cin >> taskNr;
        if(taskNr == 1){
            Message m;
            m.readBitsFromKeyboard();
            m.encode();
            cout << "Wiadomosc zakodowana:\n";
            m.printBits();
            system("pause");
            m.readErrorBitsFromKeyboard();
            system("pause");
        }
        else if( taskNr == 2){

        }
        else if(taskNr == 3){

        }
        else if(taskNr == 7) break;
        else{
            cout << "Podano niepoprawny numer podpunktu.\n";
        }
    }


    return 0;
}