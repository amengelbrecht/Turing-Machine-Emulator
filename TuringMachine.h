#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class TuringMachine{

public:
  TuringMachine (void);
  ~TuringMachine (void);

  bool readTape(string filename);
  void printTape(void);
  bool readDeltas(string filename);
  void addDeltraTransition(string state, string inputSymbol, string nextState, string nextSymbol, string direction);
  void printDeltaTable(void);
  void addFinalState(string state);
  void printFinalStates(void);
  bool run(void);
  void resetHead(void);

private:
  vector<string> tape;
  vector<vector<vector<string>>> deltaTable;
  int headPosition;
  vector<string> finalStates;
  string currentState;
  bool madeTransition;

  bool findState(string state, int& stateIndex);
  bool findInputSymbol(int stateIndex, string inputSymbol, int& inputSymbolIndex);
  void moveRight(void);
  void moveLeft(void);
  void printCurrentConfiguration(void);
};

#endif
