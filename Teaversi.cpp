#include "TRclasses.h"
#include <windows.h>
#include <iostream>
#include <string>

using namespace Teathello;
using namespace std;

Rspot* myBoard[8][8];

//player flipping
void flipPoints(int x,int y,spotcolor pcolor,Rbot* abot,bool popbot){
    mini spots[8];
    int idx = 0;
    int a = 0;
    int b = 0;
    spotcolor theirs;
    if(pcolor == BLACK) theirs = WHITE;
    else theirs = BLACK;
    //x+
    for(int i = 1;i < 8;i++){
        a = x+i;
        if(a > 7) break;
        if(myBoard[a][y]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[a][y]->getColor() == NONE) break;
        if(myBoard[a][y]->getColor() == theirs){
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
        if(myBoard[a][y]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[a][y]->getColor() == NONE) break;
        if(myBoard[a][y]->getColor() == theirs){
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
        if(myBoard[x][b]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[x][b]->getColor() == NONE) break;
        if(myBoard[x][b]->getColor() == theirs){
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
        if(myBoard[x][b]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[x][b]->getColor() == NONE) break;
        if(myBoard[x][b]->getColor() == theirs){
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
        if(myBoard[a][b]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[a][b]->getColor() == NONE) break;
        if(myBoard[a][b]->getColor() == theirs){
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
        if(myBoard[a][b]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[a][b]->getColor() == NONE) break;
        if(myBoard[a][b]->getColor() == theirs){
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
        if(myBoard[a][b]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[a][b]->getColor() == NONE) break;
        if(myBoard[a][b]->getColor() == theirs){
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
        if(myBoard[a][b]->getColor() == pcolor) {
        for(int j=0;j<idx;j++) {
            myBoard[spots[j].x][spots[j].y]->setColor(pcolor);
            if(popbot) abot->setSpace(pcolor,spots[j].x,spots[j].y);
        }
        break;
        }
        if(myBoard[a][b]->getColor() == NONE) break;
        if(myBoard[a][b]->getColor() == theirs){
        spots[idx].x = a;
        spots[idx].y = b;
        idx++;
        }
    }
}

void playerMove(Rbot* opp, spotcolor pcolor) {
    int x, y;
    //ask for some console input
    cout << "\nYour Move. X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;
    opp->setSpace(pcolor, x, y);
    myBoard[x][y]->setColor(pcolor);
    flipPoints(x,y,pcolor,opp,true);
}

void printGame() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 8; i++) {
        cout << "\n";
            for(int j = 0; j < 8; j++) {
                if (myBoard[j][i]->getColor() == WHITE) {
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "W ";
                }
                if (myBoard[j][i]->getColor() == BLACK) {
                    SetConsoleTextAttribute(hConsole, 13);
                    cout << "B ";
                }
                if (myBoard[j][i]->getColor() == NONE) {
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << "N ";
                }
            }
    }
}

int main() {
  int botx,boty;
  spotcolor botcolor;
  Rbot* botopp = new Rbot;
  spotcolor pcolor = BLACK;
  botopp->mycolor = WHITE;

  for(int i = 0;i < 8;i++){
    for(int j = 0;j < 8;j++){
      myBoard[i][j] = new Rspot(NONE,i,j);
    }
  }
  myBoard[3][3]->setColor(BLACK);
  myBoard[4][4]->setColor(BLACK);
  myBoard[3][4]->setColor(WHITE);
  myBoard[4][3]->setColor(WHITE);

  while(1) {
    printGame();
    cout << "\nBot's Turn!\n";
    botopp->playMove(botx,boty,botcolor);
    myBoard[botx][boty]->setColor(botcolor);
    flipPoints(botx,boty,botcolor,botopp,false);
    printGame();
    playerMove(botopp, pcolor);
  }
}
