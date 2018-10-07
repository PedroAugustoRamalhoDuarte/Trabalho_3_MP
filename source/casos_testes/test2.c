#include<stdio.h>

int maior(int a, int b){
  if(a > b){
    return a;
  }else{
    return b;
  }
}

int main(){
  int a, b, maior;
  a = 3;
  b = 6;
  maior = maior(a, b);
  printf("%d", maior)
  return 0;
}
