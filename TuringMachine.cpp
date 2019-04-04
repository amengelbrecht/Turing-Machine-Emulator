#include "TuringMachine.h"

TuringMachine::TuringMachine (void){
  headPosition = 0;
  currentState = "q0";
  madeTransition = true;
}

TuringMachine::~TuringMachine (void){

}

bool TuringMachine::readTape (string filename){
  ifstream inFile;
  char nextSymbol;

  tape.clear();

  inFile.open(filename);

  if(!inFile){
    return false;
  }

  else {
    while(inFile>>nextSymbol){
      tape.push_back(string(1, nextSymbol));
    }
    tape.push_back("b");
  }
}

void TuringMachine::printTape (void){
  for(int i = 0; i < tape.size(); i++){
    cout << tape[i] << " ";
  }
}

bool TuringMachine::readDeltas (string filename){
  ifstream inFile;
  string deltaLine, state, inputSymbol, nextState, nextSymbol, direction;
  int deltaFind, deltaFindBack;

  deltaTable.clear();

  inFile.open(filename);

  if(!inFile){
    return false;
  }

  while(getline(inFile, deltaLine)){
    deltaFind = deltaLine.find(",");
    state = deltaLine.substr(1,deltaFind-1);
    inputSymbol = deltaLine.substr(deltaFind+1,1);
    deltaFindBack = deltaLine.find_last_of(",");
    nextState = deltaLine.substr(deltaFind+5, deltaFindBack-deltaFind-7);
    nextSymbol = deltaLine.substr(deltaFindBack-1,1);
    direction = deltaLine.substr(deltaFindBack+1,1);
    addDeltraTransition(state, inputSymbol, nextState, nextSymbol, direction);
  }

  return true;
}

void TuringMachine::addDeltraTransition(string state, string inputSymbol, string nextState, string nextSymbol, string direction){
  int stateIndex;
  if(findState(state, stateIndex)) {
    deltaTable[stateIndex].push_back(vector<string>());
    deltaTable[stateIndex][deltaTable[stateIndex].size()-1].push_back(state);
    deltaTable[stateIndex][deltaTable[stateIndex].size()-1].push_back(inputSymbol);
    deltaTable[stateIndex][deltaTable[stateIndex].size()-1].push_back(nextState);
    deltaTable[stateIndex][deltaTable[stateIndex].size()-1].push_back(nextSymbol);
    deltaTable[stateIndex][deltaTable[stateIndex].size()-1].push_back(direction);
  }
  else{
    deltaTable.push_back(vector<vector<string>>());
    deltaTable[deltaTable.size()-1].push_back(vector<string>());
    deltaTable[deltaTable.size()-1][0].push_back(state);
    deltaTable[deltaTable.size()-1][0].push_back(inputSymbol);
    deltaTable[deltaTable.size()-1][0].push_back(nextState);
    deltaTable[deltaTable.size()-1][0].push_back(nextSymbol);
    deltaTable[deltaTable.size()-1][0].push_back(direction);
  }
}

bool TuringMachine::findState(string state, int& stateIndex){
  for(int i = 0; i < deltaTable.size(); i++){
    if(deltaTable[i][0][0] == state){
      stateIndex = i;
      return true;
    }
  }
  return false;
}

void TuringMachine::printDeltaTable (void){
  for(int state = 0; state < deltaTable.size(); state++){
    cout << deltaTable[state][0][0] << ":" << endl;
    for(int inputSymbol = 0; inputSymbol < deltaTable[state].size(); inputSymbol++){
      cout << "\t(" << deltaTable[state][inputSymbol][0] << ", " << deltaTable[state][inputSymbol][1]
      << ") = (" << deltaTable[state][inputSymbol][2] << ", " << deltaTable[state][inputSymbol][3]
      << ", " << deltaTable[state][inputSymbol][4] << ")" << endl;
    }
  }
}

void TuringMachine::moveRight(void){
  headPosition++;
  if(headPosition >= tape.size()){
    tape.push_back("b");
  }
}

void TuringMachine::moveLeft(void){
  headPosition--;
  if(headPosition < 0){
    headPosition = 0;
  }
}

void TuringMachine::addFinalState(string state){
  finalStates.push_back(state);
}

void TuringMachine::printFinalStates(void){
  for(int i = 0; i < finalStates.size(); i++){
    cout << finalStates[i] << endl;
  }
}

void TuringMachine::printCurrentConfiguration(void){
  for(int i = 0; i < tape.size(); i++){
    if(i == headPosition){
      cout << currentState << " ";
    }
    cout << tape[i] << " ";
  }
  cout << endl;
}

bool TuringMachine::run (void) {

  while(madeTransition){
  printCurrentConfiguration();
    madeTransition = false;

    for(int i = 0; i < deltaTable.size(); i++){
      if(deltaTable[i][0][0] == currentState){
        for(int k = 0; k < deltaTable[i].size(); k++){
          if(deltaTable[i][k][1] == tape[headPosition]){
            currentState = deltaTable[i][k][2];
            tape[headPosition] = deltaTable[i][k][3];
            if(deltaTable[i][k][4] == "R"){
              moveRight();
            }
            if(deltaTable[i][k][4] == "L"){
              moveLeft();
            }
            madeTransition = true;
            break;
          }
        }
        break;
      }
    }
  }

  for (int i = 0; i < finalStates.size(); i++) {
    if(currentState == finalStates[i]){
      return true;
    }
  }

  return false;
}

void TuringMachine::resetHead(void){
  headPosition = 0;
}
