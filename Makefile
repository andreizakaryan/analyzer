CC = g++
CFLAGS = -g -Wall -Wno-write-strings
SRCS = main.cpp Parser.cpp Scanner.cpp Tabl_ident.cpp Interpretator.cpp Executer.cpp 
OBJS = $(SRCS:.cpp=.o)

analyzer: $(OBJS)
	$(CC) $(CFLAGS) -o analyzer $(OBJS)
    
.cpp.o:  
	$(CC) -c $(CFLAGS) $< 
    
-include deps.mk

dep: $(SRCS)
	$(CC) -MM $^ > deps.mk

clean:
	rm -f *.o analyzer
