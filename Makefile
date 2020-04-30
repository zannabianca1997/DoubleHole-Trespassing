# Project: DoubleHole

SRCDIR = ./Source

CPP      = g++ -D__DEBUG__
CC       = gcc.exe -D__DEBUG__
OBJ      = $(SRCDIR)/main.o $(SRCDIR)/Metropolis.o $(SRCDIR)/Ran2.o $(SRCDIR)/LoadSetup.o $(SRCDIR)/Output.o $(SRCDIR)/SimpleIni/ConvertUTF.o $(SRCDIR)/diffs.o

INCS     = 

PROGRESS = -DPROGRESS
VERBOSE = -DVERBOSE

BIN      = DoubleHole
FLAGS   = $(INCS) $(PROGRESS) $(VERBOSE)

RM       = rm -f
CD       = cd

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(FLAGS)

$(SRCDIR)/main.o: $(SRCDIR)/main.cpp
	$(CPP) -c $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o $(FLAGS)

$(SRCDIR)/Metropolis.o: $(SRCDIR)/Metropolis.cpp
	$(CPP) -c $(SRCDIR)/Metropolis.cpp -o $(SRCDIR)/Metropolis.o $(FLAGS)

$(SRCDIR)/Ran2.o: $(SRCDIR)/Ran2.cpp
	$(CPP) -c $(SRCDIR)/Ran2.cpp -o $(SRCDIR)/Ran2.o $(FLAGS)

$(SRCDIR)/LoadSetup.o: $(SRCDIR)/LoadSetup.cpp
	$(CPP) -c $(SRCDIR)/LoadSetup.cpp -o $(SRCDIR)/LoadSetup.o $(FLAGS)

$(SRCDIR)/Output.o: $(SRCDIR)/Output.cpp
	$(CPP) -c $(SRCDIR)/Output.cpp -o $(SRCDIR)/Output.o $(FLAGS)

$(SRCDIR)/SimpleIni/ConvertUTF.o: $(SRCDIR)/SimpleIni/ConvertUTF.c
	$(CPP) -c $(SRCDIR)/SimpleIni/ConvertUTF.c -o $(SRCDIR)/SimpleIni/ConvertUTF.o $(FLAGS)

$(SRCDIR)/diffs.o: $(SRCDIR)/diffs.c
	$(CPP) -c $(SRCDIR)/diffs.c -o $(SRCDIR)/diffs.o $(FLAGS)
