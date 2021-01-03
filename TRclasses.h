#include <stdlib.h>

namespace Teathello {

enum spotcolor {
  NONE,
  BLACK,
  WHITE
};

typedef struct mini {
	int x;
	int y;
};

class Rspot {
  public:
  
  Rspot();
  Rspot(spotcolor acolor,int x, int y);
  ~Rspot();

  void setColor(spotcolor acolor);

  spotcolor getColor();

  void setScore(int ascore);

  //currently capscore + spotscore
  int getValue();

  bool legalW;
  bool legalB;

  private:

  //assumes board size of 64 right now
  void initScore(int x,int y);

  spotcolor color;
  //position score
  int spotscore;
  //capture score
  int capscore;
};

class Rbot {
  public:
  
  Rbot();
  ~Rbot();

  //Bot's color
  spotcolor mycolor;

  //Tell bot your move
  void setSpace(spotcolor acolor,int x,int y);

  //Get Move from bot
  void playMove(int &x,int &y,spotcolor &color);

  private:

  //updates Capture Score for each space
  void calcScores();

  //becuase im on a train and don't feel like thinking with recursion
  void calcPoint(int x,int y);
  void flipPoints(int x,int y);

  //assumes board size of 64 right now
  Rspot* Board[8][8];

};

};