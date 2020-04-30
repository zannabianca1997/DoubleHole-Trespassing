# Project: DoubleHole

SRCDIR = ./Source
BINDIR = ./Bin


CPPOBJ      = $(BINDIR)/main.o $(BINDIR)/Metropolis.o $(BINDIR)/Ran2.o $(BINDIR)/LoadSetup.o $(BINDIR)/Output.o $(BINDIR)/SimpleIni/ConvertUTF.o $(BINDIR)/diffs.o

OBJ = $(CPPOBJ) $(COBJ)

BIN      = DoubleHole

INCS     = 

FLAGS   = $(INCS) -D__DEBUG__
ifdef $(VERBOSE)
	FLAGS = $(FLAGS) -DVERBOSE
endif
ifdef $(PROGRESS)
	FLAGS = $(FLAGS) -DPROGRESS
endif

CPP= g++
C = gcc

PYTHON = python3
JUPYTER = jupyter

RM = rm -f
MV = mv
RMDIR = $(RM) -r
MKDIR = mkdir -p

.PHONY: all clean bindir

all: $(BIN)

clean:
	$(RMDIR) $(BINDIR)

$(BINDIR):
	$(MKDIR) $(BINDIR)
	

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(FLAGS)

# compile c and c++ code

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR) $(@D)
	$(CPP) -c $< -o $@ $(FLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(MKDIR) $(@D)
	$(CPP) -c $< -o $@ $(FLAGS)
	
# convert notebooks to .py

$(BINDIR)/%.py: %.ipynb
	$(MKDIR) $(@D)
	$(JUPYTER) nbconvert --to python $< --output $@

# run notebooks

$(SRCDIR)/diffs.c $(SRCDIR)/diffs.h: $(BINDIR)/create_diffs.c.py
	env PYTHONPYCACHEPREFIX=$(BINDIR) $(PYTHON) $<
	$(MV) diffs.c $(SRCDIR)/diffs.c
	$(MV) diffs.h $(SRCDIR)/diffs.h
	
	




