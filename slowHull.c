#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"


void slowHull(Domain *D,float **mesh,int cnt,Point *sites)
{
   int maxX,maxY,x,y,startId,n,tmpStartId,targetId;
   int findTarget(Point *sites,int start,int cnt);
   Edge *New;

   //find start point
   maxX=-1;
   maxY=-1;
   startId=0;
   for(n=0; n<cnt; n++)  {
     x=sites[n].x;
     y=sites[n].y;
     if(x>=maxX || y>=maxY)  {
       maxX=x;
       maxY=y;
       startId=n;
     }
   }
   tmpStartId=startId;

   D->hull = (Hull *)malloc(sizeof(Hull ));

   while(startId!=targetId)   {
     targetId=findTarget(sites,tmpStartId,cnt);
     New = (Edge *)malloc(sizeof(Edge ));
     New->next = D->hull->eg;
     D->hull->eg = New;
 
     New->start=tmpStartId;
     New->end=targetId;
     tmpStartId=targetId;
   }

}

int findTarget(Point *sites,int start,int cnt)
{
  int findFlag,target,left,n;
  void findLeft(Point *sites,int tmpStartId,int targetId,int n,int *left);

  findFlag=0;
  target=0;
  while(findFlag==0 && target<cnt)  {
    left=0;
    if(start!=target) { 
      for(n=0; n<cnt; n++)  
	if(n!=start && n!=target)  
	  findLeft(sites,start,target,n,&left);
      if(left==0) findFlag=1;
    }
    target++;
  }

  return target-1;
}


void findLeft(Point *sites,int tmpStartId,int targetId,int n,int *left)
{
   int startX,startY,targetX,targetY,x0,y0,x,y;
   float alpha;

   startX=sites[tmpStartId].x;
   startY=sites[tmpStartId].y;
   targetX=sites[targetId].x;
   targetY=sites[targetId].y;

   x0=sites[n].x;
   y0=sites[n].y;
   if(startX<targetX)  {
     alpha=(float)(targetY-startY)/(float)(targetX-startX);
     y=alpha*(x0-startX)+startY;
     if(y0>y) *left=1;
   }
   else if(startX>targetX)  {
     alpha=(float)(targetY-startY)/(float)(targetX-startX);
     y=alpha*(x0-startX)+startY;
     if(y0<y) *left=1;
   }
   else  {
     if(x0<startX)   *left=1;
   }

//   printf("start=%d,targetId=%d,n=%d,left=%d\n",tmpStartId,targetId,n,*left);
}
