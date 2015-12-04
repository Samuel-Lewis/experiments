# Compilation
CXX = g++
INCLUDES =
CXXFLAGS = $(INCLUDES) -pedantic -Wall -Wextra -O2 -std=c++11 # -g
LIBS =

# Sources and file names
SOURCES = $(shell find . -type f -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)
OUTDIR = ./
EXE = main.out
all: $(OUTDIR)/$(EXE)

# Object Compilation
$(OUTDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# Final compilation and output
$(EXE): $(OBJECTS) 
	$(CXX) $(OBJECTS) $(LIBS) -o $(EXE)

# Clean all objects files and exe.
clean:
	rm -f $(OBJECTS) $(EXE)
