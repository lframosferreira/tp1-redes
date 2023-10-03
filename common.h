#ifndef COMMON_H
#define COMMON_H

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Action types
#define START 0
#define REVEAL 1
#define FLAG 2
#define STATE 3
#define REMOVE_FLAG 4
#define RESET 5
#define WIN 6
#define EXIT 7
#define GAME_OVER 8

// Cell types
#define BOMB -1
#define HIDDEN -2
#define FLAGGED -3

#define BOARD_SIZE 4
#define MAX_BUFFER_SIZE 1024
#define MAX_CLIENTS 10

struct action {
  int type;
  int coordinates[2];
  int board[BOARD_SIZE][BOARD_SIZE];
};

/**
 * @brief Imprime na tela o tabuleiro do jogo conforme as especificações de
 * mapeamento presentes na especificação do trabalho.
 *
 * @param board Matriz de inteiros que representa o campo minado
 * @return void
 */
void print_board(const int board[BOARD_SIZE][BOARD_SIZE]);

/**
 * @brief Reseta o tabuleiro do jogo, isto é, marca todas as coordenadas como
 * 'escondidas'
 *
 * @param board Matriz de inteiros que representa o campo minado
 * @return void
 */
void reset_board_state(int board[BOARD_SIZE][BOARD_SIZE]);

/**
 * @brief Lê o tabuleiro de um arquivo e armazena em uma matriz de inteiros que
 * será utilizada no jogo
 *
 * @param input_file_path Caminho para o arquivo de entrada que contêm o
 * tabuleiro do jogo
 * @param board Matriz de inteiros na qual o tabuleiro deverá ser armazenado
 * @return void
 */
void parse_input(const char *input_file_path,
                 int board[BOARD_SIZE][BOARD_SIZE]);

/**
 * @brief Imprime na tela o modo de uso do servidor
 *
 * @param fp Ponteiro para o arquivo onde o modo de uso deve ser escrito
 * @param path Caminho para o arquivo binário que contêm o executável do
 * servidor
 * @return void
 */
void server_usage(FILE *fp, const char *path);

/**
 * @brief Imprime na tela o modo de uso do cliente
 *
 * @param fp Ponteiro para o arquivo onde o modo de uso deve ser escrito
 * @param path Caminho para o arquivo binário que contêm o executável do cliente
 * @return void
 */
void client_usage(FILE *fp, const char *path);

/**
 * @brief Imprime um erro e sai da execução com status de falha
 *
 * @param msg Mensagem de erro a ser impressa
 * @return void
 */
void err_n_die(const char *msg);

/**
 * @brief Checa se as coordenadas estão dentro dos limites permitidos
 *
 * @param coordinates Par de inteiros que representam as coordenadas
 * @return bool: true se as coordenadas forem válidas, falso caso contrário
 */
bool is_out_of_bounds(const int coordinates[2]);

// As funções abaixo foram baseadas nas implementações disponibilizadas na
// playlist do professor Ítalo Cunha
// https://www.youtube.com/watch?v=tJ3qNtv0HVs&t=2s

/**
 * @brief Realiza o 'parse' do endereço do servidor passado como parâmetro para
 * o cliente
 *
 * @param addrstr String que representa o endereço do servidor
 * @param portstr String que representa a porta onde o servidor está rodando
 * @param storage Struct em que o endereço será armazenado
 * @return int: -1 em caso de erro, 0 caso contrário
 */
int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage);

/**
 * @brief Inicializa o servidor
 *
 * @param addr_family String que representa a familia do endereço, isto é, 'v4'
 * ou 'v6'
 * @param portstr String que representa a porta onde o servidor deve rodar
 * @param storage Struct em que o endereço será armazenado
 * @return int: -1 em caso de erro, 0 caso contrário
 */
int server_sockaddr_init(const char *addr_family, const char *porstr,
                         struct sockaddr_storage *storage);

#endif