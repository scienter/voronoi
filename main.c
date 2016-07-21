#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"


int main(int argc, char *argv[])
{
   int i,j,n,nx,ny,index,cnt=0,x,y;
   float dx,dy,domainX,domainY,pipeX,ptX,ptY,xx,yy,plusY,minusY;
   float minX,maxX,minY,maxY,dd;
   float **mesh;
   char fileName[100];
   FILE *in,*out;
   Point *sites;
   void slowHull(float **mesh,int cnt,Point *sites);



   if(argc < 1)
   {
      printf("voroid [file]\n");
      exit(0);
   }

   sprintf(fileName,"%s",argv[1]);
   in=fopen(fileName,"r");
   while(fscanf(in,"%d %d",&x,&y)!=EOF)	  
      cnt++;
   close(in);

   sites = (Point *)malloc(cnt*sizeof(Point ));

   in=fopen(fileName,"r");
   n=0;
   while(fscanf(in,"%d %d",&x,&y)!=EOF)	  {
      sites[n].x=x;
      sites[n].y=y;
      n++;
   }
   close(in);

   nx=11;
   ny=11;
   mesh = (float **)malloc(nx*sizeof(float *));
   for(i=0; i<nx; i++)
     mesh[i] = (float *)malloc(ny*sizeof(float ));
   for(i=0; i<nx; i++)
     for(j=0; j<ny; j++)
       mesh[i][j]=0.0;
   


   slowHull(mesh,cnt,sites);


   //print
   sprintf(fileName,"lala");
   out=fopen(fileName,"w");
   for(i=0; i<nx; i++) 
     for(j=0; j<ny; j++)
       if(mesh[i][j]>0)
         fprintf(out,"%d %d %g\n",i,j,mesh[i][j]);
   fclose(out);


   //clear
   free(sites);

   
   
   return 0;
}
