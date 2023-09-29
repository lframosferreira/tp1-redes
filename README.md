# Trabalho Prático I da dispiclina de Redes de Computadores

## Professor: Marcos Augusto Menezes Vieira

- Para compilar tudo, é necessário ter o `gcc` e o `make` instalados em sua máquina e utilizar o comando a seguir:

  `make`

- Para inicializar o servidor:

  `./bin/server [ADDR_FAMILY] [PORT] -i [INPUT_FILE_PATH]`

- Para inicializar o cliente:

  `./bin/client [SERVER_IP] [PORT]`

## Exemplos de uso

### IPv4

`./bin/server v4 51511 -i input/jogo1.txt`
`./bin/client 127.0.0.1 51511`

### IPv6

`./bin/server v6 51511 -i input/jogo1.txt`
`./bin/client ::1 51511`
