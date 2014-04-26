export SRCDIR = src
export OBJDIR = obj
export BINDIR = bin

export CC = g++
export LIBS = -lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -llua

export CFLAGS = -std=gnu++0x -Wall -I$(SRCDIR)

# All buildable source files
SRC = $(wildcard $(SRCDIR)/*cxx)
HEADERS = $(wildcard $(SRCDIR)/*hxx)

# Place object files in an object dir
OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.cxx=.o))

.PHONY: all game clean remake

EXE = $(BINDIR)/startme

all: $(EXE)

$(EXE): .depend $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

$(OBJDIR)/%.o: %.cxx
	@(mkdir -p $(@D))
	$(CC) -c -o $@ $< $(CFLAGS)

# Dependency information for files
.depend: $(SRC)
	@(rm -f ./.depend)
	@($(CC) $(CFLAGS) -MM $^ >> ./.depend)
	@(sed -i 's|\(^.*:\)|$(OBJDIR)/$(SRCDIR)/\1|g' ./.depend)

include .depend

clean:
	rm $(EXE) $(OBJDIR)/* .depend -rf

remake: clean all
