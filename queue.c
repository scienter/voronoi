#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"


void enqueue(lnkList *queue,int front,int *rear,lnkList *item,int totalCnt)
{
  int tmp;

  tmp=(*rear+1)%totalCnt;
  if(front==tmp)  {
    printf("Queue is full\n");
    return;
  }  else
    queue[++*rear]=*item;
}

/*
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
  Segment *segment;
  lnkList *lnk,*queue;
  void segment_sort(lnkList *lnk,int cnt);
  void enqueue(lnkList *queue,int front,int *rear,lnkList *item,int totalCnt);




  //initiate queList
  totalCnt=cnt/2;
  front=0;
  rear=0;

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

  //sorting segment
  lnk = (lnkList *)malloc(totalCnt*sizeof(lnkList ));  
  queue = (lnkList *)malloc((totalCnt+1)*sizeof(lnkList ));  
  for(i=0; i<totalCnt; i++)  {
    x1=segment[i].x1;
    y1=segment[i].y1;
    x2=segment[i].x2;
    y2=segment[i].y2;
    if(y2>y1) {
      lnk[i].y=y2;
      lnk[i].x=x2;
    }  else  {
      lnk[i].y=y1;
      lnk[i].x=x1;
    }
    lnk[i].seg=i;  
  }
  segment_sort(lnk,totalCnt);

  //making queue  
  for(i=0; i<totalCnt; i++)
    enqueue(queue,front,&rear,&lnk[i],totalCnt+1);

  for(i=1; i<=totalCnt; i++)
    printf("i=%d, x=%d, y=%d, front=%d, rear=%d\n",i,queue[i].x,queue[i].y,front,rear);
  

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

