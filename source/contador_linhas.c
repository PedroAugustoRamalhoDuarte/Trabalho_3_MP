#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/contador_linhas.h"

// "Copyright [2018] <Pedro Augusto Ramalho Duarte>"


/******************************************************************
* Função: Verifica Linhas Branca
* Descrição: 
*   A função recebe de parâmetro uma string que representa uma linha de arquivo .c,
*   verifica se existe algum caracter sem ser espaços ou tabs, e com essa informação
*   retorna 1 ou 0 caso seja uma linha em branco ou não.
*
* Parâmetros:
*   string - linha de um arquivo em .c, na qual será analisada.
*
* Valor Retornado:
*   0 - Não é linha em branco.
*   1 - É linha em branco.
*
* Assertiva de entrada
*   string != NULL
*   linhas menores que 120 caracteres
*
* Assertiva de saída
*   valor retornado 0 ou 1
*
*******************************************************************/
int verifica_linha_branca(const char *string) {
  /* Para todos os char da string */
  for (int i = 0; i < strlen(string); i++) {
    /* Se a linha conter algo diferente de espaços e tabs*/
    if (string[i] != ' ' && string[i] != '\t')
      return 0; /* Não é linha em branco */
  }
  return 1; /* É linha em branco*/
}

/***************************************************************************
* Função: Verfica linha comentários
* Descrição
*   A função recebe de parâmetro uma linha de um código em .c e verifica se ela
*   é um comentário.
*   Se tiver dentro de aspas, não ocorre a verificação.
*   Logo depois é verificado se ja houve algum char sem ser espaço ou tab na linha,
*   caso exista a flag recebe 0, que indica que a linha não é um comentário
*   Caso exista // seguidos e flag == 1 -> é ComentarioDoTipo1
*   Caso exista /* -> abre o escopo do comentario, igualando coment == 1
*   Caso exista /* e flag == 1 -> é ComentarioDoTipo2
*   Caso exista /* e flag == 0 -> Não é comentario e nchecar == 1
*   Caso exista o comentário de fechar -> é ComentarioDoTipo2
* 
* Parâmetros:  
*   string - linha de um arquivo .c, na qual será avaliada
*   coment - váriavel que serve para analisar o escopo do comentário
*              0 - fechado
*              1 - aberto
*   nchecar - váriavel que serve como flag para fazer ou não a verificação escopo do comentário
*              0 - checar escopo
*              1 - não checar escopo
*
* Valor retornado:
*   0 - Não é linha inicial de comentário, há a necessidade de verificar depois 
*       se algum escopo de comentário está aberto
*   1 - É linha de comentário
*
* Assertiva de Entrada:
*   *coment != NULL
*   *nchecar != NULL
*   linhas menores que 120 caracteres
*
* Assertiva de saída:
*   0 <= coment <= 1
*   0 <= nchecar <= 1
*   Retorno 0 ou 1
********************************************************************************/

int verifica_linha_comentarios(const char *string, int *coment, int *nchecar) {
  /* Flag que verifica se ja houve algum char sem ser espaco ou tab na linha */
  int flag = 1;
  /* Flag que verifica se há um comentário do tipo 2 */
  int flagComentarioTipo2 = 0;
  /* Flag que verifica se há codigo válido antes de um comentário*/
  int flagComentDepoisDeCodigo = 0;
  /* Flag que verifica se há um comentario do tipo 1 */
  int flagComentarioTipo1 = 0;
  /* Flag que verifica se o texto esta dentro de uma string "" */
  int flagString = 0;

  /* Para todos os char da string */
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == '"') {
      if (string[i + 1] != 39 && string[i - 1] != 39) {/* ASCII aspa simples*/
        flagString += 1;
      }/* if */
    }/* if */
    /* A cada 2, zera o escopo das aspas */
    flagString = flagString % 2;

    /* Se tiver fora do escopo aspas */
    if (flagString == 0) {
      if (string[i] == '/' && string[i + 1] == '/' && flag)
        flagComentarioTipo1 = 1;  /* É comentário do tipo 1 */
      /* Se abrir o comentario */
      if (string[i] == '/' && string[i + 1] == '*') {
        if (*coment == 0) /* Se o comentário ja não estiver aberto */
          *coment += 1; /* Abre o escopo do comentario */
        if (!flag) { /* Se tem comentario depois do código */
          flagComentDepoisDeCodigo = 1; /* Não é comentário */
          *nchecar = 1;
        } else {
           flagComentarioTipo2 = 1; /* É comentário do tipo 2 */
        } /* else */
      }/* if */
      if (string[i] == '*' && string[i + 1] == '/') {
        *coment += -1;
        flagComentarioTipo2 = 1; /* É comentário do tipo 2 */
      }/* if */
      if (string[i] != ' ' && string[i] != '\t') /* Se tem código */
        flag = 0;
    }/* if */
  }/* for */
  if (flagComentarioTipo1) /* Se é comentario do tipo 1 */
    return 1; /* É comentário*/
  if (flagComentDepoisDeCodigo) /* Se o comentario é depois de um código */
    return 0; /* Não é comentário */
  if (flagComentarioTipo2)
    return 1; /* É comentário */

  return 0;/* Não é comentário */
}


/***************************************************************************
* Função: Conta Linhas
* Descrição
*   A cada linhas do arquivo a função acrescenta um contador se as funções
*   verifica_linhas_branca e verifica_linha_comentario não retornarem 1 e
*   se a linha não esteja no escopo de um comentario no qual se caracteiza
*   a variável comentário == 1.
* 
* Parâmetros:  
*   Nome do arquivo: nome do arquivo no qual sera contadas as linahs
*
* Valor retornado:
*   cont_linhas- quantidade de linahs, caso o arquivo seja válido
*   -1 - caso não seja possível acessar o arquivo
*
* Assertiva de Entrada:
*   Nome do arquivo ser válido
*   Ser um código .c compilável
*   linhas menores que 120 caracteres
*
* Assertiva de saída:
*   cont_linhas >= 0, caso o arquivo seja válido
*   retorno -1 - caso não seja possível acessar o arquivo
********************************************************************************/

int conta_linhas(const char *nome_arquivo) {
  FILE* file = fopen(nome_arquivo, "r");
  if (file) { /* Se o arquivo for válido*/
    unsigned int cont_linhas = 0;
    char *linha = reinterpret_cast<char*> (malloc(sizeof(char ) * 120));
    /* Váriavel que armazena se a linha esta dentro de um comentario
    0 - Fora de comentario 
    1 - Dentro de comentario */
    int *comentario = reinterpret_cast<int*> (malloc(sizeof(int)));
    /* Variavel que armazena se naquela linha especifica há uma abertura 
       de comentario depois de um código válido em c, porem a variavel
       comentario tem o valor == 1, mas na verdade era para considerar a 
       não sendo um comentario*/
    int *nchecar = reinterpret_cast<int*> (malloc(sizeof(int)));
    *comentario = 0;
    while (feof(file) == 0) { /* Enquanto não chegar no final do arquivo */
      *nchecar = 0;
      fscanf(file, "%[^\n]s", linha); /* Pega a String ate achar um \n */
      fgetc(file); /* Pegar o \n que sobra */
      /* Se a linha não for toda branca */
      if (!verifica_linha_branca(linha)) {
        /* e se a linha nao é comentario */
        if (!verifica_linha_comentarios(linha, comentario, nchecar)) {
          /* Não checar se for depois de codigo */
          if (*nchecar == 1) {
            cont_linhas++;
          } else {
            /* Se a linha está fora do escopo de um comentário */
            if (*comentario == 0)
              cont_linhas++;
          }/* else */
        } /* if linha_comentario */
      } /* if linha_branca */
      *linha = 0;/* Remove a info da linha */
    }/* while */
    fclose(file);
    return cont_linhas; /* Retorna a quantidade de linhas válidas */
  } else {
    return -1; /* Código de erro */
  } /* else (file) */
}/* func conta_linhas */
