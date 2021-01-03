#include "TRclasses.h"

using namespace Teathello;

  // Rspot 

  Rspot::Rspot(){
    color = NONE;
    spotscore = 0;
    capscore = 0;
    legalW = false;
    legalB = false;
  }
  
  Rspot::Rspot(spotcolor acolor,int x, int y){
    color = acolor;
    initScore(x,y);
    capscore = 0;
    legalW = false;
    legalB = false;
  }

  //corners worth 3
  //good lane worth 1
  //bad lane worth -1
  //middle is 0
  void Rspot::initScore(int x,int y){
    int relx = x;
    int rely = y;
    if(x > 3) relx = 7 - x;
    if(y > 3) rely = 7 - y;
    spotscore = -1;
    if(relx == 0 and rely == 0) spotscore = 3;
    if(relx == 2 and rely < 3) spotscore = 1;
    if(relx < 3 and rely == 2) spotscore = 1;
    if(relx == 3 or rely == 3) spotscore = 0;
  }

  void Rspot::setScore(int ascore) {
    capscore = ascore;
  }

  void Rspot::setColor(spotcolor acolor) {
    color = acolor;
    legalB = false;
    legalW = false;
  }

  spotcolor Rspot::getColor() {
    return color;
  }

  int Rspot::getValue() {
    return spotscore + capscore;
  }

  // Rbot
  Rbot::Rbot() {
    for(int i = 0;i < 8;i++){
      for(int j = 0;j < 8;j++){
        Board[i][j] = new Rspot(NONE,i,j);
      }
    }
    Board[3][3]->setColor(BLACK);
    Board[4][4]->setColor(BLACK);
    Board[3][4]->setColor(WHITE);
    Board[4][3]->setColor(WHITE);
  }

  void Rbot::setSpace(spotcolor acolor,int x,int y){
    Board[x][y]->setColor(acolor);
  }

  void Rbot::playMove(int &x,int &y,spotcolor &color){
    int topx = 0;
    int topy = 0;
    int topscore = 0;
    calcScores();
    color = mycolor;
    for(int i = 0;i < 8;i++){
      for(int j = 0;j < 8;j++){
        if(Board[i][j]->getValue() > topscore) {
          if((mycolor == BLACK) and (Board[i][j]->legalB == true)) {
            topscore = Board[i][j]->getValue();
            topx = i;
            topy = j;
          }
          else if((mycolor == WHITE) and (Board[i][j]->legalW == true)){
            topscore = Board[i][j]->getValue();
            topx = i;
            topy = j;
          }
        }
      }
    }
    x = topx;
    y = topy;
    Board[topx][topy]->setColor(mycolor);
    flipPoints(topx,topy);
  }

  void Rbot::calcScores() {
    for(int i = 0;i < 8;i++){
      for(int j = 0;j < 8;j++){
        if(Board[i][j]->getColor() != NONE) {
          Board[i][j]->setScore(0);
          Board[i][j]->legalB = false;
          Board[i][j]->legalW = false;
        }
        else calcPoint(i,j);
      }
    }
  }

  void Rbot::calcPoint(int x,int y){
    int score = 0;
    int temp = 0;
    int a = 0;
    int b = 0;
    spotcolor theirs;
    if(mycolor == BLACK) theirs = WHITE;
    else theirs = BLACK;
    //x+
    for(int i = 1;i < 8;i++){
      a = x+i;
      if(a > 7) break;
      if(Board[a][y]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[a][y]->getColor() == NONE) break;
      if(Board[a][y]->getColor() == theirs) temp += 1;
    }
    temp = 0;
    //x-
    for(int i = 1;i < 8;i++){
      a = x-i;
      if(a < 0) break;
      if(Board[a][y]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[a][y]->getColor() == NONE) break;
      if(Board[a][y]->getColor() == theirs) temp += 1;
    }
    temp = 0;
    //y+
    for(int i = 1;i < 8;i++){
      b = y+i;
      if(b > 7) break;
      if(Board[x][b]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[x][b]->getColor() == NONE) break;
      if(Board[x][b]->getColor() == theirs) temp += 1;
    }
    temp = 0;
    //y-
    for(int i = 1;i < 8;i++){
      b = y-i;
      if(b < 0) break;
      if(Board[x][b]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[x][b]->getColor() == NONE) break;
      if(Board[x][b]->getColor() == theirs) temp += 1;
    }
    temp = 0;
    //x+y+
    for(int i = 1;i < 8;i++){
      a = x+i;
      b = y+i;
      if(a > 7) break;
      if(b > 7) break;
      if(Board[a][b]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs) temp += 1;
    }
    temp = 0;
    //x-y-
    for(int i = 1;i < 8;i++){
      a = x-i;
      b = y-i;
      if(a < 0) break;
      if(b < 0) break;
      if(Board[a][b]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs) temp += 1;
    }
    temp = 0;
    //y+x-
    for(int i = 1;i < 8;i++){
      a = x-i;
      b = y+i;
      if(a < 0) break;
      if(b > 7) break;
      if(Board[a][b]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs) temp += 1;
    }
    temp = 0;
    //y-x+
    for(int i = 1;i < 8;i++){
      a = x+i;
      b = y-i;
      if(a > 7) break;
      if(b < 0) break;
      if(Board[a][b]->getColor() == mycolor) {
        if(temp > 0) {
          if(mycolor == BLACK) Board[x][y]->legalB = true;
          if(mycolor == WHITE) Board[x][y]->legalW = true;
        }
        score += temp;
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs) temp += 1;
    }

    Board[x][y]->setScore(score);
  }


  void Rbot::flipPoints(int x,int y){
    mini spots[8];
    int idx = 0;
    int a = 0;
    int b = 0;
    spotcolor theirs;
    if(mycolor == BLACK) theirs = WHITE;
    else theirs = BLACK;
    //x+
    for(int i = 1;i < 8;i++){
      a = x+i;
      if(a > 7) break;
      if(Board[a][y]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[a][y]->getColor() == NONE) break;
      if(Board[a][y]->getColor() == theirs){
        spots[idx].x = a;
        spots[idx].y = y;
        idx++;
      }
    }
    idx = 0;
    //x-
    for(int i = 1;i < 8;i++){
      a = x-i;
      if(a < 0) break;
      if(Board[a][y]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[a][y]->getColor() == NONE) break;
      if(Board[a][y]->getColor() == theirs){
        spots[idx].x = a;
        spots[idx].y = y;
        idx++;
      }
    }
    idx = 0;
    //y+
    for(int i = 1;i < 8;i++){
      b = y+i;
      if(b > 7) break;
      if(Board[x][b]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[x][b]->getColor() == NONE) break;
      if(Board[x][b]->getColor() == theirs){
        spots[idx].x = x;
        spots[idx].y = b;
        idx++;
      }
    }
    idx = 0;
    //y-
    for(int i = 1;i < 8;i++){
      b = y-i;
      if(b < 0) break;
      if(Board[x][b]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[x][b]->getColor() == NONE) break;
      if(Board[x][b]->getColor() == theirs){
        spots[idx].x = x;
        spots[idx].y = b;
        idx++;
      }
    }
    idx = 0;
    //x+y+
    for(int i = 1;i < 8;i++){
      a = x+i;
      b = y+i;
      if(a > 7) break;
      if(b > 7) break;
      if(Board[a][b]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs){
        spots[idx].x = a;
        spots[idx].y = b;
        idx++;
      }
    }
    idx = 0;
    //x-y-
    for(int i = 1;i < 8;i++){
      a = x-i;
      b = y-i;
      if(a < 0) break;
      if(b < 0) break;
      if(Board[a][b]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs){
        spots[idx].x = a;
        spots[idx].y = b;
        idx++;
      }
    }
    idx = 0;
    //y+x-
    for(int i = 1;i < 8;i++){
      a = x-i;
      b = y+i;
      if(a < 0) break;
      if(b > 7) break;
      if(Board[a][b]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs){
        spots[idx].x = a;
        spots[idx].y = b;
        idx++;
      }
    }
    idx = 0;
    //y-x+
    for(int i = 1;i < 8;i++){
      a = x+i;
      b = y-i;
      if(a > 7) break;
      if(b < 0) break;
      if(Board[a][b]->getColor() == mycolor) {
        for(int j=0;j<idx;j++) {
          Board[spots[j].x][spots[j].y]->setColor(mycolor);
        }
        break;
      }
      if(Board[a][b]->getColor() == NONE) break;
      if(Board[a][b]->getColor() == theirs){
        spots[idx].x = a;
        spots[idx].y = b;
        idx++;
      }
    }
  }
