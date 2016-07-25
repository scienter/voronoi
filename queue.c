#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"
/*
void enqueue(QueElement *queList,int *rear,QueElement *item,int totalCnt)
{
  if(*rear==totalCnt-1)  {
    printf("Queue is full\n");
    return;
  }
  queList[++*rear]=item;
}

int isEmpty(int *front, int rear)  
{
  if(*front==rear) return 1;
  else return 0;
}

QueElement dequeue(int *front, int rear)
{
  if(*front==rear) {
    printf("Queue is empty.\n");
    exit(1);
  }
  else return queList[++*front];
}

void deleteQueItem(int *front,int rear)
{
  if(*front==rear) {
    printf("Queue is empty.\n");
    exit(1);
  }
  else ++*front;
}

QueElement quePeek(int *front, int rear)
{
  if(*front==rear) {
    printf("Queue is empty.\n");
    exit(1);
  }
  else return queList[front+1];
}
*/
void createQue(Domain *D,Point *sites,int cnt)
{
  int sudoCnt,totalCnt,front,rear,n,i;
  int x,y,x1,y1,x2,y2,i1,i2;
  float alpha;
  FILE *out;
  char fileName[100];
  void swapInt(int *x1,int *x2);
  Segment *segment;



  //initiate queList
  totalCnt=cnt/2;
  front=-1;
  rear=-1;

  //create segment
  segment = (Segment *)malloc(totalCnt*sizeof(Segment ));  
  sudoCnt=totalCnt*2;
  for(n=0; n<sudoCnt; n+=2)  {
    x1=sites[n].x;
    x2=sites[n+1].x;
    y1=sites[n].y;
    y2=sites[n+1].y;
    if(x1<x2) {
      segment[n/2].x1=x1;
      segment[n/2].x2=x2;
      segment[n/2].y1=y1;
      segment[n/2].y2=y2;
    } else {
      segment[n/2].x1=x2;
      segment[n/2].x2=x1;
      segment[n/2].y1=y2;
      segment[n/2].y2=y1;
    }
  }

  sprintf(fileName,"segment");
  out=fopen(fileName,"w");
  for(i=0; i<totalCnt; i++)  {
    x1=segment[i].x1;
    y1=segment[i].y1;
    x2=segment[i].x2;
    y2=segment[i].y2;
    if(x2==x1)  {
      x=x1;
      if(y2>=y1) 
        for(y=y1; y<=y2; y++)  
          fprintf(out,"%d %d\n",x,y);
      else
        for(y=y1; y>=y2; y--)  
          fprintf(out,"%d %d\n",x,y);
    } else {
      alpha=(float)(y2-y1)/(float)(x2-x1);
      for(x=x1; x<=x2; x++)  {
        y=alpha*(x-x1)+y1;
        fprintf(out,"%d %d\n",x,y);
      }
    }

  }
  fclose(out);


  
}

