# Project: DoubleHole

SRCDIR ?= ./Source
BUILDDIR ?= ./Build

OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/Metropolis.o $(BUILDDIR)/Ran2.o \
	$(BUILDDIR)/LoadSetup.o $(BUILDDIR)/Output.o \
	$(BUILDDIR)/SimpleIni/ConvertUTF.o \
	$(BUILDDIR)/diffs.o

BIN = DoubleHole

INCS = -I"$(BUILDDIR)" -I"$(SRCDIR)"

FLAGS   = $(INCS) -D__DEBUG__
ifdef $(VERBOSE)
	FLAGS = $(FLAGS) -DVERBOSE
endif
ifdef $(PROGRESS)
	FLAGS = $(FLAGS) -DPROGRESS
endif

CPP= g++
CC = gcc

PYTHON = python3
JUPYTERCON = jupyter nbconvert --to python

CD = cd
RMDIR = rm -rf
MKDIR = mkdir -p

.PHONY: all clean

all: $(BIN)

clean:
	$(RMDIR) $(BUILDDIR)

#directories
$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)
$(BUILDDIR)/SimpleIni: | $(BUILDDIR)
	$(MKDIR) $(BUILDDIR)/SimpleIni

#main executable
$(BIN):  $(OBJS)
	$(CPP) $(OBJS) -o $(BIN) $(FLAGS)

# compile c and c++ code
.SECONDEXPANSION:

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	$(CPP) -c $< -o $@ $(FLAGS)
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $$(@D)
	$(CC) -c $< -o $@ $(FLAGS)

$(BUILDDIR)/Metropolis.o: $(SRCDIR)/Metropolis.cpp $(BUILDDIR)/diffs.h
	$(CPP) -c $(SRCDIR)/Metropolis.cpp -o $(BUILDDIR)/Metropolis.o $(FLAGS)

$(BUILDDIR)/diffs.o: $(BUILDDIR)/diffs.c
	$(CPP) -c $(BUILDDIR)/diffs.c -o $(BUILDDIR)/diffs.o $(FLAGS)


# convert notebooks to .py

$(BUILDDIR)/create_diffs.py:  create_diffs.ipynb | $(BUILDDIR)
	$(JUPYTERCON) create_diffs.ipynb --output $(BUILDDIR)/create_diffs.py

# run notebooks

$(BUILDDIR)/diffs.c $(BUILDDIR)/diffs.h: $(BUILDDIR)/create_diffs.py
	( $(CD) $(BUILDDIR) && $(PYTHON) create_diffs.py > create_diffs.log )
