/* 
  Nome: Arthur de Andrade Ferreira.
  Nome: Gabriel Alves Matos.
*/

#include "huffman.h"

int main () {
  // Variáveis auxiliares.
  int escolha = 0;
  char arquivoEntrada[100] = "";
  char arquivoSaida[100] = "";
  char enter = 0;

  // Laço de repetição responsável por repetir o menu até o usuário escolher sair.
  do {
    printf("\tMenu\n");
    printf("1 - Comprimir arquivo.\n");
    printf("2 - Descomprimir arquivo.\n");
    printf("3 - Sair.\n\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    // Estrutura condicional para realizar a operação de acordo com a escolha do usuário.
    switch (escolha) {
      case 1:
        printf("Informe o nome do arquivo de entrada (.txt): ");
        scanf("%c", &enter);
        scanf("%[^\n]", arquivoEntrada);
        printf("Informe o nome do arquivo de saida (.bin): ");
        scanf("%c", &enter);
        scanf("%[^\n]", arquivoSaida);
        printf("\n");

        // Utilizada a função comprime para comprimir o arquivo de entrada (.txt) gerando o arquivo de saída (.bin).
        comprime(arquivoEntrada, arquivoSaida);
        break;
      case 2:
        printf("Informe o nome do arquivo de entrada (.bin): ");
        scanf("%c", &enter);
        scanf("%[^\n]", arquivoEntrada);
        printf("Informe o nome do arquivo de saida (.txt): ");
        scanf("%c", &enter);
        scanf("%[^\n]", arquivoSaida);
        printf("\n");

        // Utilizada a função descomprime para descomprimir o arquivo de entrada (.bin) gerando o arquivo de saída (.txt).
        descomprime(arquivoEntrada, arquivoSaida);
        break;
      case 3: break; // Usuário escolheu sair. Nada é feito.
      default: // Usuário escolheu uma opção inválida, é mostrada uma mensagem de erro.
        printf("\nOpcao invalida!\n\n");
        break;
    }
  } while(escolha != 3);

  return 0; // Programa encerrado com sucesso.
}