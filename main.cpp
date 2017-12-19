#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>

void dogs(int i,int j,int k);
void fox(int i,int j,int k);

int main()
{
 int a=DETECT,b,c;
 int x,y,i,j,k=0,poly[8],l,m=0;

 initgraph(&a,&b,"\\tc\\bgi");
 x=getmaxx()/8;
 y=getmaxy()/8;

 for(i=1,k+=y;m<8;i+=y,m++)
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
  if(m==7 && l==0)
   {
       setcolor(15);
       dogs(i,j,k);
   }

   if(m==7 && l==2)
   {
       setcolor(15);
       dogs(i,j,k);
   }

   if(m==7 && l==4)
   {
       setcolor(15);
       dogs(i,j,k);
   }
   if(m==7 && l==6)
   {
       setcolor(15);
       dogs(i,j,k);
   }

   if(m==0 && l==3)
   {
       setcolor(0);
       fox(i,j,k);
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
