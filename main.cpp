#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>SSA
using namespace std;
int x1=0;
int win = 0, turn = 1, x, y, aux1, aux2, mode = 0, numberOfStepsInStrategy = 1;
int mode1 = 0;
int currentLine, whatStrategyAreWeIn;
//turn=1 => fox's turn
//turn=2 => dogs' turn
struct position {
    int i, j;
} moveFrom, moveTo,menuCoordinates;

void dogs(int i,int j,int k);
void fox(int i,int j,int k);
void generateMatrix(int board[8][8]);
void resetGame(int board[8][8]);
void printMatrix(int board[8][8]);
void movePiece(int board[8][8],position moveFrom, position moveTo);
void drawBoard(int board[8][8],int m, int l, int x, int y);
void getMoveFromOnClick(int x1, int y1);
void getMoveToOnClick(int x1, int y1);
void updateMatrix(int board[8][8],position moveFrom, position moveTo);
void foxWins();
void mainMenu();
void getCoordonates(int x1,int y1);
void moveDogs(int board[8][8]);
bool didTheFoxWin(int board[8][8],position moveTo);
bool moveIsValid (int board[8][8],position moveFrom, position moveTo, int turn );
void checkStrategy(int board[8][8]);
void defaultStrategy(int board[8][8]);
void firstStrategy(int board[8][8],int line);
void secondStrategy(int board[8][8],int line);
void thirdStrategy(int board[8][8],int line);
void thirdStrategyOne(int board[8][8],int line);
void thirdStrategyTwo(int board[8][8],int line);
void moveADogInStrategy(int board[8][8], int i1,int i2,int j1,int j2);
void startPlay(int board[8][8]);
void initialiseWindow(int board[8][8]);
bool didTheFoxWin(int board[8][8],position moveTo);
bool didTheDogsWin(int board[8][8]);
void dogsWin();

int main(){

    mainMenu();
    if(mode!=3){
    int board[8][8];
    generateMatrix(board);
    printMatrix(board);

    initialiseWindow(board);
    startPlay(board);
    }
    //getch();
    closegraph();
    return 0;
}
void initialiseWindow(int board[8][8]){
    initwindow(720, 720);
    x=getmaxx()/8;
    y=getmaxy()/8;
    registermousehandler(WM_LBUTTONDOWN, getMoveFromOnClick);
    registermousehandler(WM_LBUTTONUP, getMoveToOnClick);
}
void startPlay(int board[8][8]){

    if(win==1){
        foxWins();
        if(mode1==1){
                mode1=0;
                win = 0;
                generateMatrix(board);
                printMatrix(board);
                initialiseWindow(board);
                startPlay(board);

        }
        if(mode1==2){
            mode1=0;
            _getch();
            closegraph();
        }
    }

    if(win == 2){
        dogsWin();

        if(mode1==1){
            mode1=0;
            win = 0;
            generateMatrix(board);
            printMatrix(board);
            initialiseWindow(board);
            startPlay(board);
        }
        if(mode1==2){
            mode1=0;
            closegraph();
            _getch();
        }
    }

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
        if(turn==1)
            turn=2;
        else
            if(mode == 2 && turn==2)
                turn=1;
        drawBoard(board,0,0,x,y);
    }
    if(turn == 2 && mode == 1){
        if(whatStrategyAreWeIn == 0)
            checkStrategy(board);
        else if(whatStrategyAreWeIn == 1) {firstStrategy(board,currentLine);}
        else if(whatStrategyAreWeIn == 2) secondStrategy(board,currentLine);
        else if(whatStrategyAreWeIn == 3) thirdStrategy(board,currentLine);
        else if(whatStrategyAreWeIn == 4) thirdStrategyOne(board,currentLine);
        else if(whatStrategyAreWeIn == 5) thirdStrategyTwo(board,currentLine);
        drawBoard(board,0,0,x,y);
        turn = 1;
    }
    printMatrix(board);
    startPlay(board);

}
void checkStrategy(int board[8][8]){
    for(int i=0;i<8;i++){

        if(board[i][5]==5 && board[i][1]!=0 && board[i][3]!=0 && board[i+1][4]!=0 && board[i+1][6]!=0){
            numberOfStepsInStrategy = 1;
            cout<<"start 3";
            currentLine=i;
            whatStrategyAreWeIn=3;
            thirdStrategy(board,i);

        }
        else if(board[i][3]==5 && board[i][1]!=0 && board[i+1][2]!=0 && board[i+1][4]!=0 && board[i+1][6]!=0){
            numberOfStepsInStrategy = 1;
            cout<<"start 2";
            currentLine=i;
            whatStrategyAreWeIn=2;
            secondStrategy(board,i);

        }
        else if(board[i][1]==5 && board[i+1][0]!=0 && board[i+1][2]!=0 && board[i+1][4]!=0 && board[i+1][6]!=0){
            numberOfStepsInStrategy = 1;
            cout<<"start 1";
            currentLine=i;
            whatStrategyAreWeIn=1;
            firstStrategy(board,i);

        }
        else if(board[i][2]==5 && board[i+1][1]!=0 && board[i+1][3]!=0 &&board[i][4]!=0 && board[i][6]!=0){
            numberOfStepsInStrategy = 1;
            currentLine=i;
            whatStrategyAreWeIn=3;
            thirdStrategy(board,i);
        }
        else if(board[i][4]==5 && board[i][1]!=0 && board[i+1][2]!=0 &&board[i+1][4]!=0 && board[i+1][6]!=0){
            numberOfStepsInStrategy = 1;
            currentLine=i;
            whatStrategyAreWeIn=2;
            secondStrategy(board,i);
        }
        else if(board[i][6]==5 && board[i+1][1]!=0 && board[i+1][3]!=0 &&board[i+1][5]!=0 && board[i+1][7]!=0){

            numberOfStepsInStrategy = 1;
            currentLine=i;
            whatStrategyAreWeIn=1;
            firstStrategy(board,i);
        }
    }

    defaultStrategy(board);
}
int k=1;
void moveADogInStrategy(int board[8][8], int i1,int i2,int j1,int j2){

    position moveFromLocal, moveToLocal;
    moveFromLocal.i = i1;
    moveFromLocal.j = j1;
    moveToLocal.i = i2;
    moveToLocal.j = j2;
    updateMatrix(board,moveFromLocal,moveToLocal);
    if(turn == 2){
        turn = 1;
    }
}

void firstStrategy(int board[8][8], int line){


        if(numberOfStepsInStrategy==1){
            if(line%2==0)
                moveADogInStrategy(board,line+1,line,4,3);
            else
                moveADogInStrategy(board,line+1,line,3,4);
            numberOfStepsInStrategy=2;
        }
        else if(k==2){
            if(line%2==0)
                moveADogInStrategy(board,line+1,line,0,1);
            else
                moveADogInStrategy(board,line+1,line,7,6);

        }
        else if(k==3){
            //closegraph();
            if(line%2==0)
                moveADogInStrategy(board,line,line-1,3,4);
            else
                moveADogInStrategy(board,line,line-1,4,3);

        }
        else if(k==4){
            if(line%2==0)
                moveADogInStrategy(board,line+1,line,2,3);
            else
                moveADogInStrategy(board,line+1,line,5,4);

        }
        else if(k==5){
          //  closegraph();
            if(line%2==0)
                moveADogInStrategy(board,line,line-1,3,2);
            else
                moveADogInStrategy(board,line,line-1,4,5);

        }
        else if(k==6){
            if(line%2==0)
                moveADogInStrategy(board,line+1,line,6,5);
            else
                moveADogInStrategy(board,line+1,line,1,2);

        }
        else if(k==7){
            if(line%2==0)
                moveADogInStrategy(board,line,line-1,5,6);
            else
                moveADogInStrategy(board,line,line-1,2,1);

        }
        else if(k==8){
            if(line%2==0)
                moveADogInStrategy(board,line,line-1,1,0);
            else
                moveADogInStrategy(board,line,line-1,6,7);
            k=1;
            whatStrategyAreWeIn=0;

        }
    }

void secondStrategy(int board[8][8], int line){

    if(turn == 2){
        if(numberOfStepsInStrategy>=6){
            whatStrategyAreWeIn=0;
            checkStrategy(board);
        }
        else {
            if(k==1){
                if(line%2==0)
                    moveADogInStrategy(board,line+1,line,6,5);
                else
                    moveADogInStrategy(board,line+1,line,1,2);

            }
            else if(k==2){
                if(line%2==0)
                    moveADogInStrategy(board,line+1,line,2,3);
                else
                    moveADogInStrategy(board,line+1,line,5,4);

            }
            else if(k==3){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,5,6);
                else
                    moveADogInStrategy(board,line,line-1,2,1);

            }
            else if(k==4){
                if(line%2==0)
                    moveADogInStrategy(board,line+1,line,4,5);
                else
                    moveADogInStrategy(board,line+1,line,3,2);

            }
            else if(k==5){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,5,4);
                else
                    moveADogInStrategy(board,line,line-1,2,3);
                k=1;
                whatStrategyAreWeIn=0;

            }
        }
    }
}
void thirdStrategyOne(int board[8][8], int line){
    if(turn == 2){
        if(k>=9){
            whatStrategyAreWeIn=0;
            checkStrategy(board);
        }
        else {
            if(k==2){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,1,2);
                else
                    moveADogInStrategy(board,line,line-1,6,5);

            }
            else if(k==3){
                if(line%2==0)
                    moveADogInStrategy(board,line+1,line,6,7);
                else
                    moveADogInStrategy(board,line+1,line,1,0);

            }
            else if(k==4){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,7,6);
                else
                    moveADogInStrategy(board,line,line-1,0,1);

            }
            else if(k==5){
                if(line%2==0)
                    moveADogInStrategy(board,line+1,line,4,3);
                else
                    moveADogInStrategy(board,line+1,line,3,4);

            }
            else if(k==6){
                if(line%2==0)
                    moveADogInStrategy(board,line-1,line-2,2,1);
                else
                    moveADogInStrategy(board,line-1,line-2,5,6);

            }
            else if(k==7){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,3,2);
                else
                    moveADogInStrategy(board,line,line-1,4,5);

            }
            else if(k==8){
                if(line%2==0)
                    moveADogInStrategy(board,line-1,line-2,2,3);
                else
                    moveADogInStrategy(board,line-1,line-2,5,4);
                k=1;
                whatStrategyAreWeIn=0;

            }
        }
    }
}
void thirdStrategyTwo(int board[8][8], int line){
    if(turn == 2){
        if(k>=9){
            whatStrategyAreWeIn=0;
            checkStrategy(board);
        }
        else {
            if(k==2){
                if(line%2==0)
                    moveADogInStrategy(board,line+1,line,4,5);
                else{
                 //   closegraph();
                    moveADogInStrategy(board,line+1,line,3,2);
                }

            }
            else if(k==3){
                if(line%2==0)
                    moveADogInStrategy(board,line+1,line,6,7);
                else
                    moveADogInStrategy(board,line+1,line,1,0);

            }
            else if(k==4){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,7,6);
                else
                    moveADogInStrategy(board,line,line-1,0,1);

            }
            else if(k==5){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,5,4);
                else
                    moveADogInStrategy(board,line,line-1,2,3);

            }
            else if(k==6){
                if(line%2==0)
                    moveADogInStrategy(board,line-1,line-2,2,1);
                else
                    moveADogInStrategy(board,line-1,line-2,5,6);

            }
            else if(k==7){
                if(line%2==0){
                    moveADogInStrategy(board,line,line-1,2,3);
                }
                else
                    moveADogInStrategy(board,line,line-1,4,5);

            }
            else if(k==8){
                if(line%2==0)
                    moveADogInStrategy(board,line-1,line-2,2,3);
                else
                    moveADogInStrategy(board,line-1,line-2,5,4);
                k=1;
                whatStrategyAreWeIn=0;

            }
        }
    }
}
void thirdStrategy(int board[8][8], int line){
    if(turn == 2){
        if(k>=9){
            whatStrategyAreWeIn=0;
            checkStrategy(board);
        }
        else {
            if(k==1){
                if(line%2==0)
                    moveADogInStrategy(board,line,line-1,1,2);
                else
                    moveADogInStrategy(board,line,line-1,6,5);

                if(board[5][4]==5 || board[2][3]==5)
                    whatStrategyAreWeIn=4;
                else
                    whatStrategyAreWeIn=5;


            }
        }

    }
}

void defaultStrategy(int board[8][8]){
    numberOfStepsInStrategy=0;
    if(turn == 2){
      for (int line=7;line>=0;line--) {
        for(int i=0;i<8;i++) {

          if (board[line][i] != 0 && board[line-1][i-1] !=  5  && board[line-1][i+1] !=  5 && line != 0) {
            if (line % 2 == 0){
                    moveADogInStrategy(board,line,line-1, 7-x1, 6-x1);
                    x1+=2;
            }
            else {
                    moveADogInStrategy(board,line,line-1, i, i+1);

            }
            return;
          }
        }
      }
    }
}
void getMoveFromOnClick(int x1, int y1){
    moveFrom.j=x1/90;
    moveFrom.i=y1/90;
}
void getMoveToOnClick(int x1, int y1){
    moveTo.j=x1/90;
    moveTo.i=y1/90;
}
void getCoordonates(int x1,int y1){
    menuCoordinates.i=x1;
    menuCoordinates.j=y1;
}
void mainMenu(){
    int style, midx, midy;
    int size = 1;
    initwindow(720, 720);
    setbkcolor(BLUE);
    moveto(50,50);

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    settextjustify(1,1);
    outtextxy(midx, 100, "FOX AND HOUNDS");
    int left, top, right, bottom;
    left = 200;
    top = 260;
    registermousehandler(WM_LBUTTONDOWN, getCoordonates);
    /* draw a rectangle */
    while(mode==0){
       cout<<menuCoordinates.i<<"   "<<menuCoordinates.j;

       outtextxy(midx, midy-100, "PLAYER VS. COMPUTER");
       outtextxy(midx, midy, "PLAYER VS. PLAYER");
       outtextxy(midx, midy+100, "EXIT");
       system("cls");

       if(menuCoordinates.i>=156 && menuCoordinates.i<=562 &&menuCoordinates.j<=274 && menuCoordinates.j>=222)
            mode = 1;
       if(menuCoordinates.i>=187 && menuCoordinates.i<=530 &&menuCoordinates.j<=373 && menuCoordinates.j>=321)
            mode = 2;
       if(menuCoordinates.i>=297 && menuCoordinates.i<=420 &&menuCoordinates.j<=472 && menuCoordinates.j>=422)
            mode = 3;
    }
    cout<<mode;
    //_getch();
    closegraph();

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
    board[moveFrom.i][moveFrom.j] = 0;
    if(turn == 1 && whatStrategyAreWeIn!=0)
        k++;
    if(didTheFoxWin(board,moveTo) && turn==1){
           win = 1;
          // foxWins();
       }

    if(didTheDogsWin(board) && turn == 2)
    {
        win = 2 ;
       // dogsWin();
    }

}
bool didTheFoxWin(int board[8][8],position moveTo){
    for(int i=moveTo.i+1;i<8;i++)
        for(int j=0;j<8;j++)
            if(board[i][j]!=0)
                return false;
    return true;
}
bool didTheDogsWin(int board[8][8])
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(
               (board[i-1][j-1]!=0 || i-1<0 || j-1<0)&&
               (board[i-1][j+1]!=0 || i-1<0 || j+1>7)&&
               (board[i+1][j-1]!=0 || i+1>7 || j-1<0)&&
               (board[i+1][j+1]!=0 || i+1>7 || j+1>7)&&
                board[i][j]==5)
            {
                 //closegraph();
                return true;
            }
    return false;
}
void dogsWin()
{

    int style, midx, midy;
    int size = 1;
    initwindow(720, 720);
    setbkcolor(BLUE);
    moveto(50,50);

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    settextjustify(1,1);
    outtextxy(midx, 100, "THE DOGS WON!!!");

    registermousehandler(WM_LBUTTONDOWN, getCoordonates);
    menuCoordinates.i=0;
    menuCoordinates.j=0;
    mode1=0;
    while(mode1==0){
       cout<<menuCoordinates.i<<"   "<<menuCoordinates.j;

       outtextxy(midx, midy-100, "PLAY AGAIN");
       outtextxy(midx, midy, "EXIT");
       system("cls");
        if(menuCoordinates.i>=206 && menuCoordinates.i<=516 &&menuCoordinates.j<=273 && menuCoordinates.j>=220)
            mode1 = 1;
       if(menuCoordinates.i>=297 && menuCoordinates.i<=422 &&menuCoordinates.j<=375 && menuCoordinates.j>=325)
            mode1 = 2;
       // _getch();
    }

    closegraph();
}
void foxWins(){

    int style, midx, midy;
    int size = 1;
    initwindow(720, 720);
    setbkcolor(BLUE);
    moveto(50,50);

    midx = getmaxx() / 2;
    midy = getmaxy() / 2;

    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    settextjustify(1,1);
    outtextxy(midx, 100, "THE FOX WON!!!");

    registermousehandler(WM_LBUTTONDOWN, getCoordonates);
    menuCoordinates.i=0;
    menuCoordinates.j=0;
    mode1=0;
    while(mode1==0){
       cout<<menuCoordinates.i<<"   "<<menuCoordinates.j;

       outtextxy(midx, midy-100, "PLAY AGAIN");
       outtextxy(midx, midy, "EXIT");
       system("cls");
        if(menuCoordinates.i>=206 && menuCoordinates.i<=516 &&menuCoordinates.j<=273 && menuCoordinates.j>=220)
            mode1 = 1;
       if(menuCoordinates.i>=297 && menuCoordinates.i<=422 &&menuCoordinates.j<=375 && menuCoordinates.j>=325)
            mode1 = 2;
       // _getch();
    }

    closegraph();
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
    cout<<endl<<endl<<"k="<<k;
    cout<<endl<<endl<<"strategia="<<whatStrategyAreWeIn;
    cout<<endl<<endl<<"linia="<<currentLine;
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
//draws the fox onto the board
void fox(int i,int j,int k) {
    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,17,17);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),17,17);
    setcolor(120);
    setfillstyle(1,200);
    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,10,10);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),10,10);
}
//draws the dogs onto the board
void dogs(int i,int j,int k) {
    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,17,17);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),17,17);
    setcolor(120);
    setfillstyle(1,10);
    ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,10,10);
    fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),10,10);
}
