#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct _Head  {
    struct _Point *pt;
}   Head;

typedef struct _Point
{
   float x;
   float y;

   struct _Point *next;
}   Point;



int main(int argc, char *argv[])
{
   int i,nx,ny,index,cnt=0;
   float x,y,dx,dy,domainX,domainY,pipeX,ptX,ptY,xx,yy,plusY,minusY;
   float minX,maxX,minY,maxY,dd;
   char fileName[100];
   FILE *in,*out;
   Point *pt,*New,*tmp;
   Head *head;

   if(argc < 1)
   {
      printf("voroid [file]\n");
      exit(0);
   }

   //create point
   head = (Head *)malloc(sizeof(Head ));

   sprintf(fileName,"%s",argv[1]);
   in=fopen(fileName,"r");
   while(fscanf(in,"%g %g",&x,&y)!=EOF)	  {
      New = (Point *)malloc(sizeof(Point ));
      New->next = head->pt;
      head->pt = New;

      New->x=x;
      New->y=y;
      cnt++;
   }
   close(in);

   domainX=5e-5;
   domainY=3e-5;
   nx=500;
   ny=300;
   dx=domainX/((float)nx);
   dy=domainY/((float)ny);

   minX=0;
   index=0;
   for(xx=minX; xx<=domainX; xx+=dx)
   {
     pipeX=xx;   

     if(index%10==0)  {
       sprintf(fileName,"track%d",index);
       out=fopen(fileName,"w");
       
       pt=head->pt;
       while(pt)  {
         ptX=pt->x;
         ptY=pt->y;
         if(pipeX>=ptX)  {
           maxX=0.5*(ptX+pipeX);
           for(x=minX; x<=maxX+dx; x+=dx)  {
             dd=(ptX-pipeX)*(2.0*x-ptX-pipeX);
             if(dd<0) dd=0.0;
             minusY=ptY-sqrt(dd);
             plusY=ptY+sqrt(dd);
             if(minusY>=0.0)  
               fprintf(out,"%g %g %g\n",x,minusY,dd);
             if(plusY<=domainY)  
               fprintf(out,"%g %g %g\n",x,plusY,dd);
           }
         }
         pt=pt->next;
       }
      
       fclose(out);
       printf("%s is made.\n",fileName);

       sprintf(fileName,"pipe%d",index);
       out=fopen(fileName,"w");
       for(yy=minY; yy<=domainY; yy+=dy)
         fprintf(out,"%g %g\n",pipeX,yy);
       fclose(out);
       printf("%s is made.\n",fileName);
     }
     index++;
   }
/*  
   pt=head->pt;
   while(pt)  {
      x=pt->x;
      y=pt->y;
      printf("x=%g, y=%g\n",x,y);
      pt=pt->next;
   }
*/

   //clear
   pt=head->pt;
   while(pt)  {
     tmp=pt->next;
     head->pt=tmp;
     pt->next=NULL;
     free(pt);
     pt=head->pt;
   }
   free(head);

   
   
   return 0;
}
