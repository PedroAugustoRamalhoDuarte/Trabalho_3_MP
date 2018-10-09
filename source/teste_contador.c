#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/contador_linhas.h"

TEST_CASE("Conta todas as linhas") {
  const char* nome_arquivo = "casos_testes/test1.c";
  REQUIRE(conta_linhas(nome_arquivo) == 8);
}

TEST_CASE("Arquivo nao existente") {
  const char* nome_arquivo = "casos_testes/test100.c";
  REQUIRE(conta_linhas(nome_arquivo) == -1);
}

TEST_CASE("Arquivo com espaços") {
  const char* nome_arquivo = "casos_testes/test2.c";
  REQUIRE(conta_linhas(nome_arquivo) == 16);
}

TEST_CASE("Arquivo com comentarios do tipo //") {
  const char* nome_arquivo = "casos_testes/test3.c";
  REQUIRE(conta_linhas(nome_arquivo) == 3);
}

TEST_CASE("Arquivo com comentarios do tipo /* */") {
  const char* nome_arquivo = "casos_testes/test4.c";
  REQUIRE(conta_linhas(nome_arquivo) == 4);
}

TEST_CASE("Arquivo com todos os casos juntos") {
  const char* nome_arquivo = "casos_testes/test5.c";
  REQUIRE(conta_linhas(nome_arquivo) == 6);
}

TEST_CASE("Arquivo com /* */ depois de codigo valido") {
  const char* nome_arquivo = "casos_testes/test6.c";
  REQUIRE(conta_linhas(nome_arquivo) == 6);
}

TEST_CASE("Arquivo com comentario que comeca em uma linha valida e termina em outra") {
  const char* nome_arquivo = "casos_testes/test7.c";
  REQUIRE(conta_linhas(nome_arquivo) == 6);
}

TEST_CASE("Arquivo com /* dentro de outro comentario ") {
  const char* nome_arquivo = "casos_testes/test8.c";
  REQUIRE(conta_linhas(nome_arquivo) == 6);
}

TEST_CASE("Arquivo com /* dentro de aspas ") {
  const char* nome_arquivo = "casos_testes/test9.c";
  REQUIRE(conta_linhas(nome_arquivo) == 4);
}