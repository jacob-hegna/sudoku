BUILDDIR    = ./bin/
SOURCEDIR   = ./src/

SDIRS       = $(wildcard $(SOURCEDIR)*/)
VPATH       = $(SOURCEDIR):$(SDIRS):$(foreach dir, $(SDIRS), $(wildcard $(dir)*/))

IFILES      = $(shell find $(SOURCEDIR) -name '*.cpp')
IFILES     := $(IFILES)

OFILES      = $(subst $(SOURCEDIR),  $(BUILDDIR), $(addsuffix .o, $(notdir $(shell find $(SOURCEDIR)  -name '*.cpp'))))
OFILES     := $(OFILES)

CC          = clang++
CCFLAGS     = -c -O3 -std=c++11
LINKFLAGS   =


TARGET = sudoku

all: $(TARGET)

$(TARGET): $(foreach file, $(OFILES), $(BUILDDIR)$(file))
	$(CC) $^ $(LINKFLAGS) -o $(BUILDDIR)$@

$(BUILDDIR)%.cpp.o: %.cpp
	$(CC) $(foreach def, $(DEFINES), -D $(def)) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(BUILDDIR)*