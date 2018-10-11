#ifndef INCLUDE_CONTADOR_LINHAS_H_
#define INCLUDE_CONTADOR_LINHAS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string>

// "Copyright [2018] <Pedro Augusto Ramalho Duarte>"

/**
 * @file contador_linhas.h
 * 
 * @brief Header que contém a função principal conta_linhas e suas auxiliares
 * 
 * @author Pedro Augusto Ramalho Duarte, matrícula 17/0163717
 * 
 */

/** @brief Conta linhas de um arquivo .c
 *	\nA função recebe de parâmetro um nome de um arquivo .c, abre-o, se o
 *arquivo for válido a cada linha do arquivo até o final é passada para
 *duas funções auxiliar que verificam se aquela linha é um comentário ou
 *uma linha em branco e se não for nenhum dos 2 é acrescido um contador
 *que no final é retornado informando o número de linhas válidas no 
 *arquivo .c
 *
 * @param nome_arquivo - O nome do arquivo no qual vai ser contadas as linhas
 *
 * @return -1 - Caso não seja possível acessar o arquivo
 * @return cont_linhas - Retorna o numero de linhas caso seja um .c compilavel
 */
int conta_linhas(const char *nome_arquivo);

/** @brief Verifica se uma string é espaço em branco
 *\nA função recebe de parâmetro uma string que representa uma linha de arquivo .c
 *, a função verifica se da posição 0 da string ate a ultima se existe algum caracter
 *sem ser espaços ou tabs, caso exista retorna 0(Linha não em branco), caso não exista 
 *retorna 1(Linha em branco)
 *
 * @param string -Uma string que representa uma linha de um arquivo .c
 *
 * @return 0 - Caso não seja uma linha em branco
 * @return 1 - Caso seja uma linha em branco
 */
int verifica_linha_branca(const char *string);

/** @brief Verifica se uma string é um comentário
 *	\n A função recebe de parâmetro uma string que representa uma linha de arquivo .c\n
 *De char em char da string a função verifica primeiramente se é umas aspas, se for, até
 *achar outra aspas os próximos passou não são checados\n
 *	Depois a função analisa se tem algum char sem ser espaços ou tabs antes de um comentário,
 *se não tiver e tiver // ou /* a função iguala as flags respectivamente que repesentam o 
 *primeiro comentário e segundo comentário a 1, indicando que aquela linha é um comentario,
 *caso haja outros char sem ser espaços ou tabs antes do comentário aquela linha é uma linha
 *válida\n
 *	Quando é encontrado um /* a variável coment é acrescida de um para indicar que abriu
 *o escopo do comentário para função principal 
 *
 * 
 *
 *
 * @param string -Uma string que representa uma linha de um arquivo .c
 * @param coment - Varável que indica o escopo do comentario\n
 *					1 - dentro do escopo\n
 *					2 - fora do escopo\n
 * @param string - variáel que indica para não checar o escopo do comentario\n
 *					1 - Não Checar Escopo\n
 *					0 - Checar Escopo\n
 *
 * @return 0 - Caso não seja um comentário
 * @return 1 - Caso seja um comentário
 */
int verifica_linha_comentarios(const char *string, int *coment, int *nchecar);

#endif  // INCLUDE_CONTADOR_LINHAS_H_
