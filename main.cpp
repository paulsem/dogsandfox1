#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>SSA

using namespace std;

//global variables

int win = 0;
int turn = 1;
int x,y;

struct position {
    int i, j;
}moveFrom, moveTo;

//functions

void dogs(int i,int j,int k);
void fox(int i,int j,int k);
void generateMatrix(int board[8][8]);
void resetGame(int board[8][8]);
void printMatrix(int board[8][8]);
void movePiece(int board[8][8],position moveFrom, position moveTo);
void drawBoard(int board[8][8],int m, int l, int x, int y);
void getMoveFromOnClick(int x1, int y1);
void getMoveToOnClick(int x1, int y1);
void initBoard(int board[8][8]);
bool moveIsValid (int board[8][8],position moveFrom, position moveTo, int turn );
void updateMatrix(int board[8][8],position moveFrom, position moveTo);
bool didTheFoxWin(int board[8][8],position moveTo);
void foxWins();

int main(){
    int board[8][8];

    generateMatrix(board);
    printMatrix(board);
    initwindow(720, 720);
    x=getmaxx()/8;
    y=getmaxy()/8;

    registermousehandler(WM_LBUTTONDOWN, getMoveFromOnClick);
    registermousehandler(WM_LBUTTONUP, getMoveToOnClick);
    foxWins();

    while (win == 0){

            drawBoard(board,0,0,x,y);
            system("cls");
            cout<<turn;

            cout<<endl;
            cout<<moveTo.i<<" "<<moveTo.j<<endl;
            cout<<moveFrom.i<<" "<<moveFrom.j<<endl;

            if(moveIsValid(board,moveFrom,moveTo,turn)){
                updateMatrix(board,moveFrom,moveTo);
                printMatrix(board);
                cout<<turn;
                if(turn==1)turn=2;
                else turn=1;
                drawBoard(board,0,0,x,y);
            }
        printMatrix(board);
    }

    if(win == 1){
        cout<<endl<<" a castigat vulpea ";
    }
    getch();
    closegraph();
    return 0;
}

//function definitions

void getMoveFromOnClick(int x1, int y1){

    moveFrom.j=x1/90;
    moveFrom.i=y1/90;
}
void getMoveToOnClick(int x1, int y1){
    moveTo.j=x1/90;
    moveTo.i=y1/90;
}

void generateMatrix(int board[8][8]){
    int i,j;
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            board[i][j] = 0;
    board[7][0] = 1;//leftmost dog
    board[7][2] = 2;//dog
    board[7][4] = 3;//dog
    board[7][6] = 4;//rightmost dog
    board[0][3] = 5;//fox
}
void updateMatrix(int board[8][8],position moveFrom, position moveTo){
    board[moveTo.i][moveTo.j] = board[moveFrom.i][moveFrom.j];
    //cout<<"  a=  "<<board[moveTo.i][moveTo.j]<<endl;
    board[moveFrom.i][moveFrom.j] = 0;
    if(didTheFoxWin(board,moveTo) && turn==1){
           win = 1;
           foxWins();
       }
}
bool didTheFoxWin(int board[8][8],position moveTo){

    for(int i=moveTo.i+1;i<8;i++)
        for(int j=0;j<8;j++)
            if(board[i][j]!=0)
                return false;
    return true;
}
void foxWins(){
    cout<<"the fox wins";
}


    int gdriver = DETECT, gmode, errorcode;

   struct textsettingstype textinfo;

   int midx, midy, ht;

   char fontstr[80], dirstr[80], sizestr[80];

   char hjuststr[80], vjuststr[80];



   /* initialize graphics and local variables */

   initgraph(&gdriver, &gmode, "");



   /* read result of initialization */

   errorcode = graphresult();

   if (errorcode != grOk) {  /* an error occurred */



      printf("Graphics error: %s\n", grapherrormsg(errorcode));

      printf("Press any key to halt:");

      getch();

      exit(1);               /* terminate with an error code */

   }



   midx = getmaxx() / 2;

   midy = getmaxy() / 2;



   /* get information about current text settings */

   gettextsettings(&textinfo);



   /* convert text information into strings */

   sprintf(fontstr, "%s is the text style.", font[textinfo.font]);

  sprintf(dirstr, "%s is the text direction.",dir[textinfo.direction]);



  sprintf(sizestr, "%d is the text size.", textinfo.charsize);

  sprintf(hjuststr, "%s is the horizontal justification.", hjust[textinfo.horiz]);

  sprintf(vjuststr, "%s is the vertical justification.", vjust[textinfo.vert]);



   /* display the information */

   ht = textheight("W");

   settextjustify(CENTER_TEXT, CENTER_TEXT);

   outtextxy(midx, midy, fontstr);

   outtextxy(midx, midy+2*ht, dirstr);

   outtextxy(midx, midy+4*ht, sizestr);

   outtextxy(midx, midy+6*ht, hjuststr);



   outtextxy(midx, midy+8*ht, vjuststr);
}
void drawBoard(int board[8][8],int m, int l, int x, int y){
    //draw the board

    int i,j,k=0,poly[8];

    for(i=1,k+=y;m<8;i+=y,m++)
        for(j=1,l=0;l<8;j+=x,l++) {
            if((l%2==1 && m%2==0) || (l%2==0 && m%2==1)) {
                setcolor(12);
                setfillstyle(1,15);
                poly[0]=j;
                poly[1]=i;
                poly[2]=j+x;
                poly[3]=i;
                poly[4]=j+x;
                poly[5]=k+i;
                poly[6]=j;
                poly[7]=k+i;
                fillpoly(4,poly);
            }
            if(board[m][l]>=1 && board[m][l]<=4){
                setcolor(15);
                dogs(i,j,k);
            }
            if(board[m][l]==5){
                setcolor(0);
                fox(i,j,k);
            }
        }
}

void printMatrix(int board[8][8]) {
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
            cout<<board[i][j]<<' ';
        cout<<endl;
    }
}

bool moveIsValid (int board[8][8], position moveFrom, position moveTo, int turn ) {
    if( board[moveTo.i][moveTo.j]==0 ){ //if the target field is free
        if( turn == 1 && board[moveFrom.i][moveFrom.j]==5 ){ //if it's a fox & it's its turn
            if((moveTo.i == moveFrom.i + 1 && moveTo.j == moveFrom.j + 1) ||
                (moveTo.i == moveFrom.i + 1 && moveTo.j == moveFrom.j - 1) ||
                (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j + 1) ||
                (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j - 1) )
                    return true;
        } else if(turn == 2 && board[moveFrom.i][moveFrom.j] != 0 && board[moveFrom.i][moveFrom.j] != 5) { //if it's a dog & it's its turn
            if( (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j + 1) ||
                (moveTo.i == moveFrom.i - 1 && moveTo.j == moveFrom.j - 1) )
                    return true;
        }
    }
    return false;
}

void resetGame(int board[8][8]){
    generateMatrix(board);
    drawBoard(board,0,0,x,y);
    //update the score somewhere
}

void fox(int i,int j,int k) {
    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,17,17);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),17,17);
    setcolor(120);
    setfillstyle(1,200);
    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,10,10);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),10,10);
}
void dogs(int i,int j,int k) {
    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,17,17);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),17,17);
    setcolor(120);
    setfillstyle(1,10);

    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,10,10);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),10,10);
}
