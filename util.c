#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"

void segment_sort(lnkList *lnk,int cnt)
{
  int i,j,start,end,tempStart,tempEnd,flag=1;
  void seg_sortX(lnkList *lnk,int start,int end);

//  element next;
  for(i=cnt-1; flag>0; i--) { 
    flag = 0;
    for(j=0; j<i; j++) {
      if(lnk[j].y < lnk[j+1].y) {
        SWAP(lnk[j],lnk[j+1]);
        flag = 1; 
      }
    }
  }

  flag=0;
  tempStart=start=cnt;
  tempEnd=end=0;
  for(i=0; i<cnt-1; i++)  {
    if(lnk[i].y==lnk[i+1].y)  {
      tempStart=i;
      tempEnd=i+1;
      flag=1;
    } 
    if(tempStart<start) start=tempStart;
    if(tempEnd>end)     end=tempEnd;

    if(flag==1)  {
      seg_sortX(lnk,start,end);
      flag=0;
    }
  }

}

void seg_sortX(lnkList *lnk,int start,int end)
{
  int i, j;
  int flag = 1;

//  element next;
  for(i=end; flag>0; i--) { 
    flag = 0;
    for(j=start; j<i; j++) {
      if(lnk[j].x > lnk[j+1].x) {
        SWAP(lnk[j],lnk[j+1]);
        flag = 1; 
      }
    }
  }
}



void bubble_sort(Point *sites,int cnt)
{
  int i,j,start,end,tempStart,tempEnd,flag=1;
  void swap(Point *p1, Point *p2);
  void bubble_sortY(Point *sites,int start,int end);

//  element next;
  for(i=cnt-1; flag>0; i--) { 
    flag = 0;
    for(j=0; j<i; j++) {
      if(sites[j].x > sites[j+1].x) {
        swap(&sites[j],&sites[j+1]);
        flag = 1; 
      }
    }
  }
  
  flag=0;
  tempStart=start=cnt;
  tempEnd=end=0;
  for(i=0; i<cnt-1; i++)  {
    if(sites[i].x==sites[i+1].x)  {
      tempStart=i;
      tempEnd=i+1;
      flag=1;
    } 
    if(tempStart<start) start=tempStart;
    if(tempEnd>end)     end=tempEnd;

    if(flag==1)  {
      bubble_sortY(sites,start,end);
      flag=0;
    }
  }
}

void bubble_sortY(Point *sites,int start,int end)
{
  int i, j;
  int flag = 1;
  void swap(Point *p1, Point *p2);

//  element next;
  for(i=end; flag>0; i--) { 
    flag = 0;
    for(j=start; j<i; j++) {
      if(sites[j].y > sites[j+1].y) {
        swap(&sites[j],&sites[j+1]);
        flag = 1; 
      }
    }
  }
}

void swap(Point *p1, Point *p2)
{
  int tempX,tempY;
  
  tempX=p1->x;
  tempY=p1->y;
  p1->x=p2->x;
  p1->y=p2->y;
  p2->x=tempX;
  p2->y=tempY;
}

void swapInt(int *x1,int *x2)
{
  int temp;
  
  temp=*x1;
  *x1=*x2;
  *x2=temp;
}
