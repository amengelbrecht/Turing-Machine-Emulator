#include "TuringMachine.h"

using namespace std;

int main(void) {
  TuringMachine tm;
  int input = -1;
  string filename, inputS;

  while(input != 0){
    cout << "1. Read Tape" << endl
    << "2. Read Delta Table" << endl
    << "3. Print Tape" << endl
    << "4. Print Delta Tabel" << endl
    << "5. Add Final State" << endl
    << "6. Print Final States:" << endl
    << "7. Reset Read/Write Head" << endl
    << "8. Run" << endl
    << "0. Quit" << endl
    << endl << "Input: ";
    cin >> input;

    switch(input){
      case 1:
        cout << endl << "Tape Input Filename: ";
        cin >> filename;
        cout << endl;
        if(tm.readTape(filename)){
          cout << filename << " successfully read" << endl;
        }
        else {
          cout << endl << "Could not read file " << filename << endl;
        }
        cout << endl;
        break;

      case 2:
        cout << endl << "Delta Table Filename: ";
        cin >> filename;
        cout << endl;
        if(tm.readDeltas(filename)){
          cout << filename << " successfully read" << endl;
        }
        else {
          cout << "Could not read file " << filename << endl;
        }
        cout << endl;
        break;

      case 3:
        cout << endl << "Tape Content: ";
        tm.printTape();
        cout << endl << endl;
        break;

      case 4:
        cout << endl;
        tm.printDeltaTable();
        cout << endl << endl;
        break;

      case 5:
        cout << endl << "Add a final state: ";
        cin >> inputS;
        tm.addFinalState(inputS);
        break;

      case 6:
        cout << endl << "Final States:" << endl;
        tm.printFinalStates();
        cout << endl;
        break;

      case 7:
        tm.resetHead();
        cout << endl << "Head reset..." << endl;
        break;

      case 8:
        cout << endl << endl;
        if(tm.run()){
          cout << endl << "Success! Ended in final state.";
        }
        else {
          cout << endl << "Failure! Machine did not end in final state! :(";
        }
        cout << endl << endl;
        break;

      case 0:
        cout << endl << "Closing..." << endl << endl;
        break;

      default:
      cout << "Invalid Input!";
      break;

    }
  }
}
