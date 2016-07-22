EXEC = show
CC = gcc
OBJS = main.o slowHull.o clean.o util.o fastHull.o

INCL = mesh.h
LIBS = -lm
$(EXEC):$(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(EXEC)
	$(CC) $(OBJS) $(LIBS) -o $(EXEC)
$(OBJS):$(INCL)
clean:
	@rm -f *.o *~ $(EXEC)
