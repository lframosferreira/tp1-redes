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
INC = include
BIN = bin
HDRS = $(INC)/common.h
CFLAGS = -Wall -I$(INC)

SERVER = $(BIN)/server
CLIENT = $(BIN)/client

all: $(SERVER) $(CLIENT)

$(BIN)/server: $(SRC)/server.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/server.c -o $(BIN)/server $(LIBS)

$(BIN)/client: $(SRC)/client.c $(HDRS)
	$(CC) $(CFLAGS) $(SRC)/client.c -o $(BIN)/client $(LIBS)

clean:
	rm $(SERVER) $(CLIENT)