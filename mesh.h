
typedef struct _Domain
{

   struct _Hull *hull;
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
