#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define clear() printf(“\033[H\033[J”)
void dogs(int i,int j,int k);
void fox(int i,int j,int k);
bool win = false;
int var=0;
int turn = 1;
int aux1,aux2;
int ok = 0;
void click_handler(int x1, int y1)
{
    aux1=x1/90;
    aux2=y1/90;
    var++;
}

void tabla(int v[8][8],int l,int m,int x,int y)
{
    int i,j,k=0,poly[8];
    for(i=1,k+=y;m<8;i+=y,m++){

             for(j=1,l=0;l<8;j+=x,l++)
             {
              if((l%2==1 && m%2==0) || (l%2==0 && m%2==1))
              {
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

             // cout<<v[m][l]<<"  ";
              if(v[m][l]==2)
               {
                  // cout<<"m="<<m<<endl<<"l="<<l<<endl;
                   setcolor(15);
                   dogs(i,j,k);
               }
               if(v[m][l]==1)
               {
                //   cout<<"m="<<m<<endl<<"l="<<l<<endl;
                   setcolor(0);
                   fox(i,j,k);

               }
             }
           // cout<<endl;

    }
}


int main(void)
{
int prevx,prevy;
int v[8][8]={{0}};

v[0][3]=1;
aux2=0;
aux1=3;
prevx=0;
prevy=3;
v[7][0]=v[7][2]=v[7][4]=v[7][6]=2;

int x, y;
 //initgraph(&a,&b,"\\tc\\bgi");
 initwindow(720, 720);
 x=getmaxx()/8;
 y=getmaxy()/8;

registermousehandler(WM_LBUTTONDOWN, click_handler);

while (!win)
{

        if(turn == 1){

            tabla(v,0,0,x,y);
            system("cls");
            cout<<aux2<<"  "<<aux1<<endl;
            if(v[aux2][aux1]==0)
                if((aux2==prevx-1 || aux2==prevx+1) && (aux1==prevy-1 || aux1==prevy+1))
                {
                    v[prevx][prevy]=0;
                    v[aux2][aux1]=1;
                    prevx=aux2;
                    prevy=aux1;
                    turn = 2;
                    tabla(v,0,0,x,y);
                }

            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++)
                    cout<<v[i][j]<<"  ";
                cout<<endl;
            }

            delay(100);
          //  turn=2;
          if(ok == 1)
            turn = 2;
        }

        if(turn == 2)
        {
            v[6][6]=2;
            win = true;
        }

    }

  getch();
  closegraph();
}
void dogs(int i,int j,int k)
{
 ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,17,17);
 fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),17,17);
 setcolor(120);
 setfillstyle(1,120);

 ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,10,10);
 fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),10,10);
}

void fox(int i,int j,int k)
{
 ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,17,17);
 fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),17,17);
 setcolor(120);
 setfillstyle(1,120);

 ellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),0,360,10,10);
 fillellipse((j+getmaxx()/16),(k+i)-(getmaxy()/16),10,10);
}
