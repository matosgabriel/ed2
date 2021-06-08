/* 
  Nome: Arthur de Andrade Ferreira.
  Nome: Gabriel Alves Matos.
*/

#include "RB.h"
#include <string.h>

// Criação da estrutura Artigo.
typedef struct artigo {
  int id;
  int ano;
  char autor[200];
  char titulo[200];
  char revista[200];
  char DOI[20];
  char palavraChave[200];
} Artigo;

// Função para a comparação do id de dois artigos.
int comparaId(void *info1, void *info2) {
  // Criação dos ponteiros do tipo Artigo que recebem o casting dos parâmetros.
  Artigo *aux1 = (Artigo *) info1;
  Artigo *aux2 = (Artigo *) info2;

  if (aux1->id > aux2->id) return 1; // Id do primeiro artigo maior que do segundo.
  else if (aux1->id < aux2->id) return -1; // Id do primeiro artigo menor que do segundo.
  else return 0; // Ids iguais.
}

// Função para a impressão do id de um artigo.
void imprimeArtigo(void *info) {
  // Criação do ponteiro do tipo Artigo que recebe o casting do ponteiro do parâmetro.
  Artigo *aux = (Artigo *) info;
  
  printf("[id %d", aux->id);
}

// Função para a impressão dos dados de um artigo.
void imprimeDadosArtigo(void *artigo) {
  // Criação do ponteiro do tipo Artigo que recebe o casting do parâmetro.
  Artigo *artigoResultado = (Artigo *) artigo;

  printf("\n\tDados: ");
  printf("\nId: %d", artigoResultado->id);
  printf("\nAno: %d", artigoResultado->ano);
  printf("\nAutor: %s", artigoResultado->autor);
  printf("\nTitulo: %s", artigoResultado->titulo);
  printf("\nRevista: %s", artigoResultado->revista);
  printf("\nDOI: %s", artigoResultado->DOI);
  printf("\nPalavra chave: %s\n", artigoResultado->palavraChave);
}

// Função para a liberação da memória alocada para um artigo.
void liberaArtigo(void *info) {
  // Criação do ponteiro do tipo Artigo que recebe o casting do parâmetro.
  Artigo *artigo = (Artigo *) info;
  free(artigo); // Liberação da memória alocada para o nó.
}

int main() {
  externo = criaNode(0);
  externo->cor = 1;
  Node *T = externo;
  int op;

  // Node *aux;
  char enter;
  int id=0, ano=0;
  char autor[200], titulo[200], revista[200], DOI[20], palavraChave[200];

  // Laço de repetição responsável por repetir o menu até o usuário escolher sair.
  do {
    printf("\tMenu\n");
    printf("1 - Inserir um artigo.\n");
    printf("2 - Buscar um artigo.\n");
    printf("3 - Excluir um artigo.\n");
    printf("4 - Imprimir a arvore.\n");
    printf("5 - Sair.\n\n");
    printf("Escolha: ");
    scanf("%d", &op);

    // Estrutura condicional para realizar a operação de acordo com a escolha do usuário.
    switch (op) {
      case 1:
        printf("Informe o id do novo artigo: ");
        scanf("%d", &id);

        // Criação de novo nó do tipo Artigo.
        Artigo *novoArtigo = (Artigo *) calloc(1, sizeof(Artigo));
        novoArtigo->id = id;

        /*
          Se existe um artigo na árvore com id informado é liberada a memória alocada para
          o nó e impressa uma mensagem de erro.
          Se não é inserido o novo nó na árvore e impressa uma mensagem de informação.
        */
        if (busca(T, novoArtigo, comparaId)) {
          free(novoArtigo);
          printf("\nJa existe um artigo cadastrado com este id!\n");
        } else {
          printf("Informe o ano de publicacao do artigo: ");
          scanf("%d", &ano);
          printf("Informe o nome o autor: ");
          scanf("%c", &enter);
          scanf("%[^\n]", autor);
          printf("Informe o nome o titulo do artigo: ");
          scanf("%c", &enter);
          scanf("%[^\n]", titulo);
          printf("Informe o nome da revista de publicacao: ");
          scanf("%c", &enter);
          scanf("%[^\n]", revista);
          printf("Informe o DOI do artigo: ");
          scanf("%c", &enter);
          scanf("%[^\n]", DOI);
          printf("Informe a palavra chave do artigo: ");
          scanf("%c", &enter);
          scanf("%[^\n]", palavraChave);

          // Atribuição dos valores lidos aos campos do novo artigo.
          novoArtigo->ano = ano;
          strcpy(novoArtigo->autor, autor);
          strcpy(novoArtigo->titulo, titulo);
          strcpy(novoArtigo->revista, revista);
          strcpy(novoArtigo->DOI, DOI);
          strcpy(novoArtigo->palavraChave, palavraChave);

          Node *novoNo = criaNode(novoArtigo);

          // Inserção de novo artigo utilizando a função RBInsercao.
          RBInsercao(&T, novoNo, comparaId);

          // Impressão das informações do artigo utilizando a função imprimeDadosArtigo.
          printf("\nArtigo inserido na arvore: \n");
          imprimeDadosArtigo(novoArtigo);
        }
        printf("\n");
        break;
      case 2:
        printf("Informe o id do artigo a ser buscado: ");
        scanf("%d", &id);

        Artigo artigo1; // Criação de uma nova variável do tipo artigo.
        artigo1.id = id; // Atribuição do id lido ao campo "id" da novo artigo.
        
        /*
          Se existe um artigo na árvore com id igual ao lido são impressas as informações
          deste. Se não, é impressa uma mensagem de erro.
        */
        if (busca(T, &artigo1, comparaId)) {
          // Impressão das informações do artigo utilizando a função imprimeNode.
          imprimeNode(T, &artigo1, comparaId, imprimeDadosArtigo);
        } else {
          printf("\nNao existe um artigo com este id na arvore!\n");
        }
        printf("\n");
        break;
      case 3:
        printf("Informe o id do artigo a ser removido: ");
        scanf("%d", &id);

        Artigo artigo2; // Criação de uma nova variável do tipo artigo.
        artigo2.id = id; // Atribuição do id lido ao campo "id" do novo artigo.

        Node *resultadoBusca = busca(T, &artigo2, comparaId);

        /*
          Se existe um artigo na árvore com id igual ao id lido o nó é removido.
          Se não, é impressa uma mensagem de erro.
        */
        if (resultadoBusca) {          
          // Impressão das informações do artigo utilizando a função imprimeNode.
          printf("\nArtigo removido: \n");
          imprimeNode(T, &artigo2, comparaId, imprimeDadosArtigo);

          // Remoção do nó da árvore utilizando a função RBRemocao.
          RBRemocao(&T, resultadoBusca, liberaArtigo);

        } else {
          printf("\nNao existe um artigo com este id na arvore!\n");
        }
        
        printf("\n");
        break;
      case 4:
        printf("\n\tArvore:\n");
        
        /*
          Se "T" for NULL é impressa uma mensagem informando que a árvore é vazia.
          Se não, é impressa a árvore.
        */
        if (T == externo) printf("\n\tVazia!\n");
        // Impressão da árvore utilizando a função imprimeArvore.
        else imprimeArvore(T, 1, imprimeArtigo);
        printf("\n");
        break;
      case 5: break; // Usuário escolheu sair. Nada é feito.
      default: break;
    }
  } while(op != 5);
  
  // Liberação da memória alocada para os nós da árvore.
  liberaArvore(T, liberaArtigo);
  liberaNode(externo, liberaArtigo);

  return 0; // Retorno de 0 indicando o fim do programa com êxito.
}