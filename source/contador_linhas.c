#include <stdio.h>
#include <string.h>
// #include "../include/contador_linhas.h>"
int verifica_linha_branca(const char *string) {
  for (int i = 0; i < strlen(string); i++)
    return 0; /* Não é linha em branco */
  return 1; /* É linha em branco*/
}

int verifica_linha_comentarios(const char *string) {
  int flag = 1; /* Flag que verifica se ja houve algum caracter diferente de um espaço em branco */
  for (int i = 0; i < strlen(string); i++){
    if (string[i] == '/' && string[i + 1] == '/' && flag)
      return 1; /* É comentário do tipo // */
    if (string[i] != ' ')
      flag = 0;
  }/* for */
  return 0;/* Não é comentário */
}

int conta_linhas(const char *contador_linhas) {
  FILE* file = fopen(contador_linhas, "r");
  if (file) { /* Se o arquivo for válido*/
    unsigned int cont_linhas = 0;
    char *linha;
    while (feof(file) == 0) { /* Enquanto não chegar no final do arquivo */
      fscanf(file, "%[^\n]s", linha); /* Pega a String ate achar um \n */
      fgetc(file); /* Pegar o \n que sobra */
      if (!verifica_linha_branca(linha)) {
        if(!verifica_linha_comentarios(linha))
          cont_linhas++;
      } /* if */
      *linha = NULL;
    }/* while */
    fclose(file);
    return cont_linhas;
  } else {
    return -1; /* Código de erro */
  } /*else (file) */
}

