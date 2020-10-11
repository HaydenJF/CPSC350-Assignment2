//implementation for calling.cpp
#include "life.h"
#include <cmath>
#include <time.h>
#include <fstream>
#include <unistd.h>
#include <bits/stdc++.h>

#define _USE_MATH_DEFINES

calling::calling(){//constructor
  intro();
}

calling::~calling(){//deconstructor
  for (int i = 0; i < rows; ++i) {
    delete dArray[i];
  }
  delete dArray;
}

void calling::intro(){//Introduction to game.
  cout << "Hello and welcome to the game of life!." << endl;
  step1();
}

void calling::step1(){//Asks if user want a random game or already has a file.
  cout << "Would you like a random game or do you already have a file set up? (1,2)" << endl;
  string ans;
  cin >> ans;
  cin.ignore();
  if (ans == "1") {
    randoms();
  } else if (ans == "2") {
    config();
  } else {
    cout << "That was not a 1 or a 2..." << endl;
    step1();
  }
}

int calling::numRow(){//gets rows for randoms()
  try {
    cout << "How many rows?" << endl;
    string s1;
    cin >> s1;
    cin.ignore();
    int r = stoi(s1);
    if (r < 1){
      throw invalid_argument("bad");
    }
    return r;
  } catch(const invalid_argument i){
    cout << "Give an integer." << endl;
    return numRow();
  }
}

int calling::numCol(){//gets cols for randoms()
  try {
    cout << "How many columns?" << endl;
    string s1;
    cin >> s1;
    cin.ignore();
    int r = stoi(s1);
    if (r < 1){
      throw invalid_argument("bad");
    }
    return r;
  } catch(const invalid_argument i){
    cout << "Give an integer." << endl;
    return numCol();
  }
}

double calling::percent(){//gets decimal value for randoms()
  try {
    cout << "Give a decimal greater than 0 and less than or equal to 1." << endl;
    string s1;
    cin >> s1;
    cin.ignore();
    double r = stod(s1);
    if (r > 1 || r <= 0){
      throw invalid_argument("bad");
    }
    return r;
  } catch(const invalid_argument i){
    cout << "Give a double that is greater than 0 and less than or equal to 1." << endl;
    return percent();
  }
}



void calling::randoms(){//creates a rand matrix as specified by user

    rows = numRow();
    cols = numCol();
    double n = percent();

    int Xs = (int)(n*rows*cols);
    char array[rows*cols] = {};
    int spot = 0;
    while (spot < rows*cols){
      if (Xs > 0) {
        Xs--;
        array[spot] = 'X';
      } else {
        array[spot] = '-';
      }
      spot++;
    }
    srand(time(NULL));
    unsigned s = rand();
    int l = sizeof(array) / sizeof(array[0]);
    shuffle(array, array+l, default_random_engine(s));
    int k = 0;
    dArray = new char*[rows];
    for (int i = 0; i < rows; ++i) {
      dArray[i] = new char[cols];
      for (int j = 0; j < cols; ++j) {
        dArray[i][j] = array[k];
        k++;
      }

    }
    step2();
}

void calling::config(){//takes a file from user
  bool goodFile = false;
  cout << "What is your file name?" << endl;
  string f;
  cin >> f;
  cin.ignore();

  ifstream file(f);
  if (file.is_open()) {

    string tempLine;
    int lines = 0;
    bool firstLines = true;
    bool done = false;
    while (getline(file, tempLine) && !done) {

      if (lines == 0 && firstLines){
        rows = stoi(tempLine);

        dArray = new char*[rows];
      } else if (lines == 1 && firstLines) {
        cols = stoi(tempLine);

        lines = -1;
        firstLines = false;
      } else if (lines < rows){
        dArray[lines] = new char[cols];
        for (int k = 0; k < cols; ++k){
          dArray[lines][k] = tempLine[k];
          cout << tempLine[k];
        }
        cout << endl;
      }


      if (lines == rows) {
        done = true;
      }
      lines++;

  }

    goodFile = true;
} else {
    goodFile = false;
  }
  file.close();
  if (!goodFile) {
    cout << "Your file did not work.  Try again." << endl;
    config();
  } else {
    step2();
  }
}

void calling::step2(){//Chooses classic mirror or donut ring for matrix.
  cout << "Do you want a classic, mirror or donut ring for your game? (1/2/3)" << endl;
  string s;
  cin >> s;
  cin.ignore();
  if (s == "1"){
    type = 1;
    step3();
  } else if (s == "2") {
    type = 2;
    step3();
  } else if (s == "3") {
    type = 3;
    step3();
  } else {
    cout << "You did not give proper input." << endl;
    step2();
  }
}

void calling::step3(){//Determines style of output
  cout << "Do you want a brief pause, or do you want to click enter between generations, or do you want it in a txt file? (1/2/3)" << endl;
  string s;
  cin >> s;
  cin.ignore();
  if (s == "1"){
    briefPause();
  } else if (s == "2") {
    enterPause();
  } else if (s == "3") {
    toFile();
  } else {
    cout << "You did not give proper input." << endl;
    step3();
  }
}

void calling::briefPause(){//outputs with pauses between entries.
  mode *m = new mode(dArray, rows, cols, type);
  cout << "0" << endl;
  m->print();

  while (!m->dupOrZero()){
    usleep(2000000);

    m->printGen();
    m->print();
    m->calc();
  }
  exit();

}
void calling::enterPause(){//outputs with pauses for user to hit enter.
  mode *m = new mode(dArray, rows, cols, type);
  cout << "0" << endl;
  m->print();
  while (!m->dupOrZero()){

    m->printGen();
    m->print();
    m->calc();
    cout << "Click enter when ready." << endl;
    string s;

    getline(cin, s);


  }
  exit();
}

void calling::toFile(){//outputs to file that is specified by user
  cout << "Please give a file." << endl;
  string s;
  cin >> s;
  cin.ignore();
  mode *m = new mode(dArray, rows, cols, type);
  ofstream file;
  file.open (s, ios::app);
  if (file.is_open()) {
      file << "0" << "\n";
  }
  file.close();
  m->printToFile(s);
  while (!m->dupOrZero()){
    m->printToFileGen(s);
    m->printToFile(s);
    m->calc();
  }
  exit();
}


void calling::exit(){//Ends the program
  cout << "The program is over.  Press enter when done.";
  string s;

  getline(cin, s);
}
