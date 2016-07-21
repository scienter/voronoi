#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"


int main(int argc, char *argv[])
{
   int i,j,n,nx,ny,cnt=0;
   int istart,iend,jstart,jend,x,y;
   float minX,maxX,minY,maxY,alpha;
   float **mesh;
   char fileName[100];
   FILE *in,*out;
   Point *sites;
   Domain *D;
   Edge *eg;
   void slowHull(Domain *D,float **mesh,int cnt,Point *sites);
   void clean(Domain *D);


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
   
   slowHull(D,mesh,cnt,sites);

   eg=D->hull->eg;
   while(eg)  {
     istart=sites[eg->start].x;
     jstart=sites[eg->start].y;
     iend=sites[eg->end].x;
     jend=sites[eg->end].y;
     printf("start=%d : (%d,%d), end=%d : (%d,%d) \n",eg->start,istart,jstart,eg->end,iend,jend);
     for(i=istart; i<=iend; i++) {
       alpha=(float)(jend-jstart)/(float)(iend-istart);
       for(i=istart; i<=iend; i++)  {
	 j=alpha*(i-istart)-jstart;
	 mesh[i][j]=1;
       }
     }
     eg=eg->next;
   }


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
   clean(D);
   
   
   return 0;
}
