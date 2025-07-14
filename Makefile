# Compilador e flags
CC = g++
CXFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wformat-security -Werror
CXDEBUG = -g
CXVER = -std=c++17

# Diretórios
SRC_DIR = src
INC_DIR = include
EXEC = tp3.out

# Arquivos fonte e cabeçalhos
SRCS = $(SRC_DIR)/solucao_exata.cpp $(SRC_DIR)/solucao_aproximada.cpp $(SRC_DIR)/tabuleiro.cpp $(SRC_DIR)/main.cpp
HDRS = $(INC_DIR)/solucao_exata.hpp $(INC_DIR)/solucao_aproximada.hpp $(INC_DIR)/tabuleiro.hpp 

# Regra padrão
all: compile

# Compilação normal
compile: $(SRCS) $(HDRS)
	$(CC) $(CXFLAGS) $(CXVER) -I$(INC_DIR) $(SRCS) -o $(EXEC)

# Compilação em modo de depuração
debug: $(SRCS) $(HDRS)
	$(CC) $(CXFLAGS) $(CXVER) $(CXDEBUG) -I$(INC_DIR) $(SRCS) -o $(EXEC)

# Limpeza de arquivos compilados
clean:
	rm -f $(EXEC)

.PHONY: all clean debug compile
