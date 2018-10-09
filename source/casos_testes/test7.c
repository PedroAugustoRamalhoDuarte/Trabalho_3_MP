// Caso de teste numero 6
#include<stdio.h>

/* Nesse caso de teste vamos misturar os tipos de comentarios
   e espacos ao longo do codigo */

int func(int a, int b){
  //Calcula o valor de (a + b)*10
  int c = a + b; // c soma a + b
  /*
  Agora multiplica por 10
  */
  c *=10;/* 
  			c *=10 */ 
  return c;
}
