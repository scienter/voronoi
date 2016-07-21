#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"


void slowHull(float **mesh,int cnt,Point *sites)
{
   int maxX,maxY,x,y,startId,n,tmpStartId,targetId;
   int findTargetId(Point *sites,int tmpStartId,int cnt);

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

   if(tmpStartId==0) targetId=1;
   else              targetId=0;
   while(startId!=targetId)  {
     targetId=findTargetId(sites,tmpStartId,cnt);
     printf("targetId=%d, startId=%d\n",targetId,startId);
     tmpStartId=targetId;
   }
/*
       //save line
       startI=sites[tmpStartId].x;
       startJ=sites[tmpStartId].y;
       endI=sites[targetId].x;
       endJ=sites[targetId].y;
       for(i=startI; i<=endI; i++)
         for(j=startJ; j<=endJ; j++)
           mesh[i][j]=1;
   }	//end of while
*/      
//   printf("maxX=%g, maxY=%g, id=%d\n",maxX,maxY,startId);

}

int findTargetId(Point *sites,int tmpStartId,int cnt)
{
   int left,scanId,n,targetId;
   int startX,startY,targetX,targetY,testX,testY;
   float alpha,testA;

   left=1;
   scanId=0;
   while(left==1)  {
     if(scanId!=tmpStartId)  {
       startX=sites[tmpStartId].x;
       startY=sites[tmpStartId].y;
       targetX=sites[scanId].x;
       targetY=sites[scanId].y;
       alpha=(targetY-startY)/(targetX-startX);

       for(n=0; n<cnt; n++)  {
         if(n!=scanId && n!=tmpStartId)  {
           testX=sites[n].x;
           testY=sites[n].y;
           testA=(testY-startY)/(testX-startX);
           if(testA>alpha)   left=1;        
           else  {
             left=0;
             targetId=n;
           }
         }
       }
     }      
   }

   return targetId;
}
