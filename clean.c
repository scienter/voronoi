#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"

void clean(Domain *D)
{
  Edge *eg,*tmpEdge;

  //remove edge
  eg=D->hull->eg;
  while(eg)  {
    tmpEdge=eg->next;
    D->hull->eg=tmpEdge;
    eg->next=NULL;
    free(eg);
    eg=D->hull->eg;
  }
  free(D->hull);
}
