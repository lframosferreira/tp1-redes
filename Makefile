#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: Compilação do Trabalho Prático 1 - Disciplina de Redes de Computadores
# Autor		: Luís Felipe Ramos Ferreira - Matrícula: 2019022553
#---------------------------------------------------------------------
# Opções	: make - compila tudo e gera os binários executáveis 'server' e 'client'
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
HDRS = $(INC)/common.h $(INC)/server.h $(INC)/client.h
CFLAGS = -Wall -c -I$(INC)

SERVER = $(BIN)/server
CLIENT = $(BIN)/client

$(BIN)/server: $(OBJ)/server.o
	$(CC) -o $(BIN)/server $(OBJS) $(LIBS)

$(BIN)/client: $(OBJ)/client.o
	$(CC) -o $(BIN)/client $(OBJS) $(LIBS)

$(OBJ)/server.o: $(INC)/common.h $(INC)/server.h $(SRC)/server.c
	$(CC) $(CFLAGS) -o $(OBJ)/server.o $(SRC)/server.c

$(OBJ)/client.o: $(INC)/common.h $(INC)/client.h $(SRC)/client.c
	$(CC) $(CFLAGS) -o $(OBJ)/client.o $(SRC)/client.c

clean
    rm $(EXE) $(OBJ)