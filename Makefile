
ifndef CPP
	CPP  = g++
endif

CPPFLAGS = -g -O3 -std=c++11 -Wall
BIN      = main.exe
OBJ      = main.o
LINKOBJ  = main.o

ifndef RM
	RM   = rm -f
endif

.PHONY: all all-before all-after clean

all: all-before $(BIN) all-after

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CPPFLAGS)


clean:
	$(RM) $(OBJ) $(BIN)