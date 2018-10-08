#include <stdio.h>
#include <string.h>
// #include "../include/contador_linhas.h>"
int verifica_linha_branca(const char *string) {
  for (int i = 0; i < strlen(string); i++){
    return 0;
  }/* for */
  return 1;
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

