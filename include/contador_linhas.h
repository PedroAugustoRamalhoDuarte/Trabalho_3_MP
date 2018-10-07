/* Função Conta Linhas
*	A cada linhas do arquivo a função acrecenta um contador se as funções
*verifica_linhas_branca e verifica_linha_comentario não retornarem 1
*	Entrada:	
*	Nome do arquivo: nome do arquivo no qual sera contadas as linahs
*
*	Retorno:
*	Se o arquivo for válido retorna a quantidade de linhas do arquivo com exeção
*das linhas brancas e as de só comentario
*	Se não for possível ler o arquivo retorna -1
*
*	Requisitos:
*	Nome do arquivo ser válido
*/
int conta_linhas(const char *nome_arquivo);

int verifica_linha_branca(const char *string);

int verifica_linha_comentarios(const char *string);