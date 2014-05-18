export SRCDIR = src
export OBJDIR = obj
export BINDIR = bin

export CC = g++
export LIBS = -lX11 -lGL -lXrandr -lfreetype -lopenal -lpthread -lsfml-graphics -lsfml-window -lsfml-system -llua

export CFLAGS = -std=gnu++0x -Wall -I$(SRCDIR)

# All buildable source files
SRC = $(wildcard $(SRCDIR)/*cxx) $(wildcard $(SRCDIR)/**/*cxx)

OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.cxx=.o))
DEPS = $(patsubst %,$(OBJDIR)/%,$(SRC:.cxx=.d))

EXE = $(BINDIR)/startme

all: debug

debug: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

$(OBJDIR)/%.o: %.cxx
	@(mkdir -p $(@D))
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm $(EXE) $(OBJDIR)/* -rf

remake: clean all

.PHONY: all clean remake debug

-include $(DEPS)

