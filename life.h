//implementation for life.h
#include <iostream>

using namespace std;
//header file for mode.cpp and calling.cpp
class mode{ //for mode.cpp
  public:
    mode(char **dArray, int x, int y, int t); //constructor
    ~mode(); //destructor
    void print(); //prints with cout
    void printGen(); //prints generation
    void printToFile(string s);  //prints to file
    void printToFileGen(string s); //prints to file generation
    void calc(); //calculates next gen
    bool dupOrZero(); //checks if gen is over
  private:
    int value(int x, int y); //checks surounding spots
    void setClassic(); //sets ring to classic mode
    void setMirror(); //sets ring to mirror mode
    void setDonut(); //sets ring to donut mode
    int generation;
    int row;
    int col;
    char **prev;
    char **matrix;
    char **next;
    int type;
};

class calling{ //for calling.cpp
  public:
    calling(); //constructor
    ~calling(); //destructor
    void intro();//Introduces game
    void step1();//chose between random and pre-file
    void randoms();//creates random matrix
    void config();//uses players text file

    void step2(); //sets ring type

    void step3(); //choses how to present
    void briefPause(); //presents with delay
    void enterPause(); //presents with enter click
    void toFile(); //presents into file


    void exit(); //ends program
  private:
    int numRow();//for randoms(); creates rows with error check
    int numCol();//for randoms(); creates cols with error check
    double percent();//for randoms(); creates a decimal with error check
    int rows;
    int cols;
    char **dArray;
    int type;



};


/*class mirror: public mode{
  public:
    mirror(char **dArray, int x, int y);
    ~mirror();
    void setRing();
};
class donut: public mode{
public:
  donut(char **dArray, int x, int y);
  ~donut();
  void setRing();
};*/
