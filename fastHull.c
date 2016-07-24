#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"

void fastHull(Domain *D,int cnt,Point *sites)
{
  int n,x,y,last,leftFlag,rightMost;
  int *list;
  void bubble_sort(Point *sites,int cnt);
  void findLeftTurn(Point *sites,int *list,int last,int *leftFlag);

  bubble_sort(sites,cnt);

  list = (int *)malloc(cnt*sizeof(int ));
  for(n=0; n<cnt; n++)
    list[n]=0;

  //right scan
  list[0]=0;
  list[1]=1;
  list[2]=2;
  last=2;
  for(n=2; n<cnt; n++)  {
    list[last]=n;
    leftFlag=1;
    while(leftFlag==1 && last>=2)  {
      findLeftTurn(sites,list,last,&leftFlag);
      if(leftFlag==1) {
	list[last-1]=list[last];
	list[last]=0;
	last--;
      }
    }
    last++;
  } 
  rightMost=last-1;

  list[rightMost+1]=cnt-2;
  list[rightMost+2]=cnt-3;
  last=rightMost+2;
  //left scan
  for(n=cnt-3; n>=0; n--)  {
    list[last]=n;
    leftFlag=1;
    while(leftFlag==1 && last>=rightMost+2)  {
      findLeftTurn(sites,list,last,&leftFlag);
      if(leftFlag==1) {
	list[last-1]=list[last];
	list[last]=0;
	last--;
      }
    }
    last++;
  } 

  for(n=0; n<cnt; n++)
    printf("list[%d]=%d\n",n,list[n]);
  printf("last=%d\n",last);
  for(n=0; n<cnt; n++)
    printf("n=%d, x=%d, y=%d\n",n,sites[n].x,sites[n].y);


}

void findLeftTurn(Point *sites,int *list,int last,int *leftFlag)
{
  int x1,y1,x2,y2,x3,y3;
  float alpha1,alpha2;

  x1=sites[list[last-2]].x;
  y1=sites[list[last-2]].y;
  x2=sites[list[last-1]].x;
  y2=sites[list[last-1]].y;
  x3=sites[list[last]].x;
  y3=sites[list[last]].y;

  if(x1==x3)  *leftFlag=0;
  else {
    if(x1==x2) *leftFlag=0;
    else if(x2==x3) *leftFlag=1;
    else {
      alpha1=(float)(y2-y1)/(float)(x2-x1);
      alpha2=(float)(y3-y2)/(float)(x3-x2);
      if(alpha1>=alpha2) *leftFlag=0;
      else  *leftFlag=1;
    }
  }
}
