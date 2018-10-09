#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "../include/contador_linhas.h>"
int verifica_linha_branca(const char *string) {
  for (int i = 0; i < strlen(string); i++)
    return 0; /* Não é linha em branco */
  return 1; /* É linha em branco*/
}

int verifica_linha_comentarios(const char *string, int *comentario, int *nchecar) {
  /* Flag que verifica se ja houve algum caracter diferente de um espaço em branco */
  int flag = 1;
  /* Flag que verifica se abriu um comentario */
  int flagComent = 0; 
  /* Flag que verifica se há codigo válido antes de um comentário*/
  int flagComentDepoisDeCodigo = 0;
  /* Flag que verifica se há um comentario do tipo // */
  int flagComentarioTipo1 = 0;

  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == '/' && string[i + 1] == '/' && flag) {
      flagComentarioTipo1 = 1; /* É comentário do tipo // */
    }
    if (string[i] == '/' && string[i + 1] == '*') {
      flagComent = 1;
      *comentario += 1;
      if (!flag) {
        flagComentDepoisDeCodigo = 1;
        *nchecar = 1;
      }/* if */
    }
    if (string[i] == '*' && string[i + 1] == '/') {
      *comentario += -1;
      flagComent = 1;
    }
    if (string[i] != ' ')
      flag = 0;
  }/* for */
  if (flagComentarioTipo1) /* Se é comentario do tipo 1 */
    return 1; /* É comentário do tipo // */
  if (flagComentDepoisDeCodigo) /* Se o comentario é depois de um código */
    return 0; /* Não é comentário */ 
  if (flagComent)
    return 1; /* É comentário */
  
  return 0;/* Não é comentário */  
}

int conta_linhas(const char *contador_linhas) {
  FILE* file = fopen(contador_linhas, "r");
  if (file) { /* Se o arquivo for válido*/
    unsigned int cont_linhas = 0;
    char *linha;
    /* Váriavel que armazena se a linha esta dentro de um comentario
    0 - Fora de comentario
    1 - Dentro de comentario */
    int *comentario = (int*) malloc(sizeof(int));
    /* Variavel que armazena se naquela linha especifica há uma abertura 
       de comentario depois de um código válido em c, porem a variavel
       comentario tem o valor == 1, mas na verdade era para considerar a 
       não sendo um comentario*/
    int *nchecar = (int*) malloc(sizeof(int));  
    *comentario = 0;
    while (feof(file) == 0) { /* Enquanto não chegar no final do arquivo */
      *nchecar = 0;
      fscanf(file, "%[^\n]s", linha); /* Pega a String ate achar um \n */
      fgetc(file); /* Pegar o \n que sobra */
      if (!verifica_linha_branca(linha)) { /* Se a linha não for toda branca*/
        if (!verifica_linha_comentarios(linha, comentario, nchecar)) { /* e se a linha nao é comentario */
          /* Não checar caso haja um codigo depois começe um comentario e so feche em linhas abaixo */
          if (*nchecar == 1) {
            cont_linhas++;
          } else {
            if (*comentario == 0) { /* Se a linha está fora do escopo de um comentário */
              cont_linhas++;
            }
          }/* else */
        } /* if linha_comentario */
      } /* if linha_branca */
      *linha = 0;/* Remove a info da linha */
    }/* while */
    fclose(file);
    return cont_linhas; /* Retorna a quantidade de linhas válidas*/
  } else {
    return -1; /* Código de erro */
  } /*else (file) */
}/* func contra_linhas */

