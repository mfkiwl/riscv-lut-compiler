
CXXFLAGS= -I. -std=c++11 -Wall
LFLAGS=-llua

AUTOGENERATED_FILES=lex.BaseWeights.cc lex.BaseInput.cc

TARGETS= riscv-lut-compiler

OBJ=
all: make.incl $(TARGETS)

make.incl: $(AUTOGENERATED_FILES)
	./builddep.py > make.incl

%.cc: %.l
	flex $^

include make.incl


riscv-lut-compiler: $(OBJ)
	$(CXX) $^ -o$@ $(LFLAGS)



clean:
	rm -f $(OBJ) $(TARGETS) $(AUTOGENERATED_FILES) make.incl

