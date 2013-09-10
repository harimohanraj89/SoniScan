SoniScan:main.o ControlBlock.o SonificationEngine.o
	g++ -Wall main.o ControlBlock.o SonificationEngine.o -o SoniScan

main.o:main.cpp ControlBlock.o SonificationEngine.o
	g++ -Wall -c main.cpp

ControlBlock.o:ControlBlock.cpp ControlBlock.h Constants.h
	g++ -Wall -c ControlBlock.cpp

SonificationEngine.o:SonificationEngine.cpp SonificationEngine.h Constants.h
	g++ -Wall -c SonificationEngine.cpp