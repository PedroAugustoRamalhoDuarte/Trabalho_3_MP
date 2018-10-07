#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/contador_linhas.h"

TEST_CASE("Conta todas as linhas") {
  char* const nome_arquivo = "..\\casos_testes\\test1.c";
  REQUIRE(conta_linhas(nome_arquivo) == 8);
}
