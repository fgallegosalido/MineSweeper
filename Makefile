# ************Archivo Makefile************

SRC = source
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g  -I$(INC)
AR = ar
LDFLAGS= -L./$(LIB)/

all : $(BIN)/buscaminas

# ************ Compilación de Programas Principales ************
$(BIN)/buscaminas : $(OBJ)/buscaminas.o $(OBJ)/campominas.o $(OBJ)/tablero.o
	$(CXX) -o $(BIN)/buscaminas $(OBJ)/buscaminas.o $(OBJ)/campominas.o $(OBJ)/tablero.o

# *********** Compilación de Módulos **************
$(OBJ)/buscaminas.o : $(SRC)/buscaminas.cpp $(INC)/campominas.h $(INC)/tablero.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/buscaminas.cpp -o $(OBJ)/buscaminas.o

$(OBJ)/campominas.o : $(SRC)/campominas.cpp $(INC)/campominas.h $(INC)/tablero.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/campominas.cpp -o $(OBJ)/campominas.o

$(OBJ)/tablero.o : $(SRC)/tablero.cpp $(INC)/tablero.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/tablero.cpp -o $(OBJ)/tablero.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ $(LIB)/* ./*~

mrproper : clean
	-rm $(BIN)/*
