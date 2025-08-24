OBJS=\
	InputMgr.o\
	Main.o

INCS=\
	InputMgr.h

CFLGS=-c -mwindows -mthreads -O2 -std=c++20 -I . -I SFML-2.5.1/include

LIBS=\
	-L SFML-2.5.1/lib\
	-l sfml-graphics -l sfml-window -l sfml-network -l sfml-system

bezierDemo.exe : $(OBJS) $(INCS)
	g++ -o bezierDemo.exe -mwindows -mthreads $(OBJS) $(LIBS)

Main.o : Main.cpp $(INCS)
	g++ $(CFLGS) -o Main.o Main.cpp

InputMgr.o : InputMgr.cpp $(INCS)
	g++ $(CFLGS) -o InputMgr.o InputMgr.cpp

clean :
	rm *.o
