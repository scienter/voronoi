#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}

typedef struct _Domain
{

   struct _Hull *hull;
   struct _QueElement *queList;
}   Domain;




typedef struct _Point
{
   int x;
   int y;

//   struct _Point *next;
}   Point;

typedef struct _Hull  {
   struct _Edge *eg;
}   Hull;


typedef struct _Edge
{
   int start;
   int end;
   
   struct _Edge *next;
}   Edge;


typedef struct _QueElement
{
   int start;
   int end;
   int increment;
}   QueElement;


typedef struct _Segment
{
   int x1;
   int y1;
   int x2;
   int y2;
}   Segment;



