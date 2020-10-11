//implementation for mode.cpp
#include "life.h"
#include <fstream>

mode::mode(char **dArray, int x, int y, int t){ //constructor
  generation = 1;

  type = t;
  row = x+2;
  col = y+2;
  matrix = new char*[row];
  prev = new char*[row];
  next = new char*[row];
  for (int i = 0; i < row; ++i) {
    matrix[i] = new char[col];
    prev[i] = new char[col];
    next[i] = new char[col];
    for (int j = 0; j < col; ++j) {
      matrix[i][j] = '-';
      prev[i][j] = '_';
      next[i][j] = '_';
    }
  }
  for (int i = 1; i < row-1; ++i) {
    for (int j = 1; j < col-1; ++j) {
      matrix[i][j] = dArray[i-1][j-1];
    }
  }

  if (type == 1){
    setClassic();
  } else if (type == 2){
    setMirror();
  } else {
    setDonut();
  }

}

mode::~mode(){ //destructor
  for (int i = 0; i < row; ++i) {
    delete prev[i];
    delete matrix[i];
    delete next[i];
  }
  delete prev;
  delete matrix;
  delete next;
}

void mode::calc(){//next matrix and sets previous matrix to old the prior gen.

  for (int i = 1; i < row-1; i++){
    for (int j = 1; j < col-1; j++){
      int v = value(i,j);
      if(v==2){
        next[i][j]=matrix[i][j];
      } else if(v==3){
        next[i][j]='X';
      } else {
        next[i][j]='-';
      }
    }
  }

  for (int i = 1; i < row-1; i++){
    for (int j = 1; j < col-1; j++){
      prev[i][j]=matrix[i][j];
      matrix[i][j]=next[i][j];
    }
  }
  generation++;
  if (type == 1){
    setClassic();
  } else if (type == 2){
    setMirror();
  } else {
    setDonut();
  }

}

void mode::setClassic(){//creates ring around matrix for calculations:classic mode
  for(int i = 0; i < row; ++i){
    if (i == 0 || i == (row - 1)){
      for (int j = 0; j < col; ++j){
        matrix[i][j] = '-';
      }
    } else {
      matrix[i][0] = '-';
      matrix[i][row-1] = '-';
    }
  }
}

void mode::setMirror(){//creates ring around matrix for calculations:mirror mode
  matrix[0][0] = matrix[1][1];
  matrix[row-1][0]=matrix[row-2][1];
  matrix[0][col-1] = matrix[1][col-2];
  matrix[row-1][col-1]=matrix[row-2][col-2];
  for (int i = 1; i < row-1;++i){
    matrix[i][0]=matrix[i][1];
  }
  for (int i = 1; i < col-1;++i){
    matrix[i][col-1]=matrix[i][col-2];
  }
  for (int j = 1; j < col-1;++j){
    matrix[0][j]=matrix[1][j];
  }
  for (int j = 1; j < col-1;++j){
    matrix[row-1][j]=matrix[row-2][j];
  }
}

void mode::setDonut(){//creates ring around matrix for calculations:donut mode
  matrix[0][0] = matrix[row-2][row-2];
  matrix[row-1][0]=matrix[1][col-2];
  matrix[0][col-1] = matrix[row-2][1];
  matrix[row-1][col-1]=matrix[1][1];
  for (int i = 1; i < row-1;++i){
    matrix[i][0]=matrix[i][col-2];
  }
  for (int i = 1; i < col-1;++i){
    matrix[i][col-1]=matrix[i][1];
  }

  for (int j = 1; j < col-1;++j){
    matrix[0][j]=matrix[row-2][j];
  }
  for (int j = 1; j < col-1;++j){
    matrix[row-1][j]=matrix[1][j];
  }
}


int mode::value(int x, int y){//calculates neighbor value at a specific spot
  int n = 0;
  for (int i = x-1; i < x+2; ++i) {
    for (int j = y-1; j < y+2; ++j) {

      if (x != i || y != j){
        if (matrix[i][j] == 'X') {
          n++;
        }
      }
    }
  }
  return n;
}

void mode::printGen(){//prints generation number to console
  cout << "generation " << generation << endl;
}

void mode::print(){//prints matrix to console
  for (int i = 1; i < row-1; ++i) {
    for (int j = 1; j < col-1; ++j) {
      cout << matrix[i][j];
    }
    cout << endl;
  }
}

void mode::printToFileGen(string s){//prints generation number to a file
  ofstream file;
  file.open (s, ios::app);
  if (file.is_open()) {
      file << "generation " << generation << "\n";
  }
  file.close();
}

void mode::printToFile(string s){//prints matrix to a file
  ofstream file;
  file.open (s, ios::app);
  for(int i = 1; i < row-1;++i){
    for(int j = 1; j < col-1;++j){
      file << matrix[i][j];
    }
    file << "\n";
  }
  file.close();
}

bool mode::dupOrZero(){//checks for duplicate matrix or empty matrix
  bool dup = true;
  bool zero = true;
  for (int i = 1; i < row-1; ++i) {
    for (int j = 1; j < col-1; ++j) {
      if (matrix[i][j] != prev[i][j]) {
        dup = false;
      }
      if (matrix[i][j] == 'X') {
        zero = false;
      }
    }
  }
  return (dup || zero);
}
