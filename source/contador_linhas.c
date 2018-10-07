#include <stdio.h>
// #include "../include/contador_linhas.h>"

int conta_linhas(const char *contador_linhas) {
  FILE* file = fopen(contador_linhas, "r");
  if (file) { /* Se o arquivo for válido*/
    unsigned int cont_linhas = 0;
    char *linhas;
    while (feof(file) == 0) { /* Enquanto não chegar no final do arquivo */
      fscanf(file, "%[^\n]s", linhas); 
      fgetc(file);
      cont_linhas++;
    }
    fclose(file);
    return cont_linhas;
  } else {
    fclose(file);
    return -1; /* Código de erro */
  } /*else (file) */
}
