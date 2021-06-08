/* 
  Nome: Arthur de Andrade Ferreira
  Nome: Gabriel Alves Matos
*/

#include "AVL.h"

Node *criaNode(void *info) {
  // Ponteiro "novo" recebe a criação de um novo nó.
  Node *novo = (Node *) calloc(1, sizeof(Node));

  // Erro na alocação de memória.
  if (!novo) {
    printf("Erro ao alocar memoria!\n");
    exit(1);
  }
  
  // O campo "info" do novo nó recebe o valor genérico "info" recebido por parâmetro.
  novo->info = info;
  novo->bal = 0;
  return novo; // Retorno do endereço de memória do novo nó.
}

Node *buscaArvore(Node *T, void *valor, int (*compara) (void *, void *)) {
  if (!T) return NULL; // Não existe nó com chave "valor" na árvore.
  if (compara(T->info, valor) == 0) return T; // Foi encontrado um nó com chave "valor".
  // Se existir um nó com chave "valor" este estará na subárvore à direita.
  if (compara(T->info, valor) < 0) return buscaArvore(T->dir, valor, compara);
  // Se existir um nó com chave "valor" este estará na subárvore à esquerda.
  else return buscaArvore(T->esq, valor, compara);
}

void imprimeArvore(Node *T, int nivel, void (*imprime) (void *)) {
  // Se "T" for diferente de NULL (árvore não vazia) serão impressos os nós da árvore.
  if (T) {

    // Chamada recursiva da função para imprimir os nós da subárvore à esquerda.
    imprimeArvore(T->esq, nivel+1, imprime);
    
    // Laço responsável por imprimir uma quantidade de "tabs" correspondente ao nível do nó.
    for(int i=0; i<nivel-1; i++) {
      printf("\t");
    }
    
    /*
      Utilização da função de callback "imprime" para imprimir o identificador
      do campo "info" do nó atual.
    */
    imprime(T->info);
    printf(" (%d)\n", T->bal);
    
    // Chamada recursiva da função para imprimir os nós da subárvore à esquerda.
    imprimeArvore(T->dir, nivel+1, imprime);
  }
}

void imprimeNode(Node *T, void *valor, int (*compara)(void *, void *), void (*imprimeDados)(void *)) {
  // Ponteiro "resultado" receberá o resultado da busca de "valor" na árvore "T".
  Node *resultado = buscaArvore(T, valor, compara);

  /*
    Se o resultado da busca for diferente de NULL será utilizada a função
    imprimeDados para imprimir o valor genérico armazenado no campo "info" do nó.
  */
  if (resultado)
    imprimeDados(resultado->info);
}

void liberaNode(Node *node, void (*liberaInfo) (void *)) {
  // Liberação da memória alocada para o campo "info".
  liberaInfo(node->info);
  free(node); // Liberação da memória alocada para o nó.
}

void liberaArvore(Node *T, void (*liberaInfo) (void *)) {
  if (T) { // Árvore não vazia.
    // Chamada recursiva da função para a liberação das subárvores do nó atual.
    liberaArvore(T->dir, liberaInfo);
    liberaArvore(T->esq, liberaInfo);
    liberaNode(T, liberaInfo); // Liberação da memória alocada para o nó atual.
  }
}

void rotacoesDireitaInsercao(Node **v, int *h) {
  // Criação de nós auxiliares.
  Node *u = NULL, *z = NULL;
  u = (*v)->esq;

  // Rotação simples à direita.
  if (u->bal == 1) {
    (*v)->esq = u->dir;
    u->dir = (*v);
    (*v)->bal = 0; // Atualização do fator de balanceamento da nova raiz.
    (*v) = u;
  } else { // Rotação dupla à direita.
    z = u->dir;
    u->dir = z->esq;
    z->esq = u;
    (*v)->esq = z->dir;
    z->dir = (*v);

    // Atualização do fator de balanceamento do filho à direita da nova raiz.
    if (z->bal == 1)
      (*v)->bal = -1;
    else (*v)->bal = 0;

    // Atualização do fator de balanceamento do filho à esquerda da nova raiz.
    if (z->bal == -1)
      u->bal = 1;
    else u->bal = 0;

    (*v) = z; // Atualização do ponteiro da raiz da árvore.
  }

  // Atualização do fator de balanceamento da raiz e da variável de controle de altura.
  (*v)->bal = 0;
  (*h) = 0;
}

void rotacoesEsquerdaInsercao(Node **v, int *h) {
  // Criação de nós auxiliares.
  Node *u = NULL, *z = NULL;
  u = (*v)->dir;

  // Rotação simples à esquerda.
  if (u->bal == -1) {
    (*v)->dir = u->esq;
    u->esq = (*v);
    (*v)->bal = 0; // Atualização do fator de balanceamento da nova raiz.
    (*v) = u;
  } else { // Rotação dupla à esquerda.
    z = u->esq;
    u->esq = z->dir;
    z->dir = u;
    (*v)->dir = z->esq;
    z->esq = (*v);

    // Atualização do fator de balanceamento do filho à direita da nova raiz.
    if (z->bal == 1)
      u->bal = -1;
    else u->bal = 0;

    // Atualização do fator de balanceamento do filho à esquerda da nova raiz.
    if (z->bal == -1)
      (*v)->bal = 1;
    else (*v)->bal = 0;

    (*v) = z; // Atualização do ponteiro da raiz da árvore.
  }

  // Atualização do fator de balanceamento da raiz e da variável de controle de altura.
  (*v)->bal = 0;
  (*h) = 0;
}

void insereAVL(Node **v, int *h, void *x, int (*compara) (void *, void *)) {
  // Não existe nó com chave igual a "x" na árvore.
  if ((*v) == NULL) {
    (*v) = criaNode(x);
    (*h) = 1;
  } else { // Procura a posição ideal para a inserção do nó com chave "x" na árvore.
    if (compara(x, (*v)->info) == 0) { // Nó com chave igual a "x" encontrado.
      return;
    } else if (compara(x, (*v)->info) < 0) { // "x" é "menor" que a chave da "raiz" atual.
      // Chamada recursiva em busca da posição ideal para inserção (subárvore à esquerda).
      insereAVL(&((*v)->esq), h, x, compara); 
      
      // Ajuste dos fatores de balanceamento/rotação (caso necessário).
      if ((*h)) {
        switch((*v)->bal) {
          case -1:
            (*v)->bal = 0;
            (*h) = 0;
            break;
          case 0:
            (*v)->bal = 1;
            break;
          case 1:
            rotacoesDireitaInsercao(v, h);
            break;
          default: break;
        }
      }
    } else { // "x" é "maior" que a chave da "raiz" atual.
      // Chamada recursiva em busca da posição ideal para inserção (subárvore à direita).
      insereAVL(&((*v)->dir), h, x, compara);
      
      // Ajuste dos fatores de balanceamento/rotação (caso necessário).
      if ((*h)) {
        switch((*v)->bal) {
          case 1: 
            (*v)->bal = 0;
            (*h) = 0;
            break;
          case 0: 
            (*v)->bal = -1;
            break;
          case -1:
            rotacoesEsquerdaInsercao(v, h);
            break;
          default: break;
        }
      }
    }
  }
}

void rotacoesDireitaRemocao(Node **v, int *h) {
  // Criação de nós auxiliares.
  Node *u, *z;
  u = (*v)->esq;

  if (u->bal >= 0) { // Rotação simples à direita.
    (*v)->esq = u->dir;
    u->dir = (*v);

    /*
      Com base no fator de balanceamento antigo da nova raiz altera os fatores de
      balanceamento.
    */
    if (u->bal == 0) {
      u->dir->bal = 1;
      u->bal = -1;
      (*h) = 0; // A altura da árvore não muda.
    } else {
      u->dir->bal = 0;
      u->bal = 0;
    }

    (*v) = u;
  } else { // Rotação dupla à direita.
    z = u->dir;
    u->dir = z->esq;
    z->esq = u;
    (*v)->esq = z->dir;
    z->dir = (*v);

    /*
      Com base no fator de balanceamento antigo da nova raiz altera os fatores de
      balanceamento.
    */
    if (z->bal == 1) {
      u->bal = 0;
      z->dir->bal = -1;
    } else if (z->bal == -1) {
      u->bal = 1;
      z->dir->bal = 0;
    } else {
      u->bal = 0;
      z->dir->bal = 0;
    }

    // Atualização do fator de balanceamento da raiz e do ponteiro da raiz da árvore.
    z->bal = 0;
    (*v) = z;
  }
}

void rotacoesEsquerdaRemocao(Node **v, int *h) {
  // Criação de nós auxiliares.
  Node *u, *z;
  u = (*v)->dir;

  if (u->bal <= 0) { // Rotação simples à esquerda.
    (*v)->dir = u->esq;
    u->esq = (*v);

    /*
      Com base no fator de balanceamento antigo da nova raiz altera os fatores de
      balanceamento.
    */
    if (u->bal == 0) {
      u->esq->bal = -1;
      u->bal = 1;
      (*h) = 0; // A altura da árvore não muda.
    } else {
      u->esq->bal = 0;
      u->bal = 0;
    }

    (*v) = u;
  } else { // Rotação dupla à esquerda.
    z = u->esq;
    u->esq = z->dir;
    z->dir = u;
    (*v)->dir = z->esq;
    z->esq = (*v);

    /*
      Com base no fator de balanceamento antigo da nova raiz altera os fatores de
      balanceamento.
    */
    if (z->bal == 1) {
      (*v)->bal = 0;
      u->bal = -1;
    } else if (z->bal == -1) {
      (*v)->bal = 1;
      u->bal = 0;
    } else {
      (*v)->bal = 0;
      u->bal = 0;
    }

    // Atualização do fator de balanceamento da raiz e do ponteiro da raiz da árvore.
    z->bal = 0;
    (*v) = z;
  }
}

void trataAntecessor(Node **v, Node **remover, int *h, void (*libera) (void *)) {
  // Criação de nó auxiliar.
  Node *aux = NULL;

  if ((*v)->dir != NULL) { // Nó predecessor possui filho a direita.
    // Chamada recursiva para atualizar o predecessor caso possível.
    trataAntecessor(&((*v)->dir), remover, h, libera);

    /* 
      Como a altura mudou, deve-se alterar os fatores de balanceamento àcima ou
      realizar uma rotação caso necessário (à direita pois o predecessor estava na
      subárvore à direita).
    */
    if ((*h)) {
      switch((*v)->bal) {
        case -1: // Altura alterada.
          (*v)->bal = 0;
          break;
        case 0: // Altura não alterada.
          (*v)->bal = 1;
          (*h) = 0;
          break;
        case 1: // Altura alterada e nó desbalanceado.
          rotacoesDireitaRemocao(v, h);
          break;
        default: break;
      }
    }

  } else { // O nó não possui filho à direita, então ele é o predecessor.
    // Troca entre a chave do nó predecessor e do nó a ser removido.
    (*remover)->info = (*v)->info;
    aux = (*v);
    (*v) = (*v)->esq;

    // Liberação da memória alocada para o nó.
    free(aux);

    /*
      Tanto no caso de antecessor ser folha, quanto caso dele ter um filho à esquerda,
      a altura da subárvore irá diminuir.
    */
    (*h) = 1;
  }
}

void removeAVL(Node **v, int *h, void *x, int (*compara) (void *, void *), void (*libera) (void *)) {
  // Criação de nó auxiliar.
  Node *aux;

  if ((*v) == NULL) { // Não existe nó com chave igual a "x" (chave a ser removida).
    (*h) = 0;
  } else { // Está sendo procurada a posição em que um nó com chave "x" estaria na árvore.
    if (compara(x, (*v)->info) < 0) { // "x" é "menor" que a chave da "raiz" atual.
      // Chamada recursiva em busca da posição ideal para remoção na subárvore à esquerda.
      removeAVL(&((*v)->esq), h, x, compara, libera);

      // Ajuste dos fatores de balanceamento/rotação (caso necessário).
      if ((*h)) {
        switch((*v)->bal) {
          case 1:
            (*v)->bal = 0;
            break;
          case 0:
            (*v)->bal = -1;
            (*h) = 0;
            break;
          case -1:
            rotacoesEsquerdaRemocao(v, h);
            break;
          default: break;
        }
      }

    } else if (compara(x, (*v)->info) > 0) { // "x" é "maior" que a chave da "raiz" atual.
      // Chamada recursiva em busca da posição ideal para remoção na subárvore à direita.
      removeAVL(&((*v)->dir), h, x, compara, libera);

      // Ajuste dos fatores de balanceamento/rotação (caso necessário).
      if ((*h)) {
        switch((*v)->bal) {
          case -1:
            (*v)->bal = 0;
            break;
          case 0:
            (*v)->bal = 1;
            (*h) = 0;
            break;
          case 1:
            rotacoesDireitaRemocao(v, h);
            break;
          default: break;
        }
      }

    } else { // Nó com chave igual a "x" encontrado.
      
      if (!((*v)->dir) && !((*v)->esq)) { // É folha.
        // Liberação da memória alocada para o campo chave e para o nó.
        libera((*v)->info);
        free((*v));
        (*v) = NULL;
        (*h) = 1;
      } else if ((*v)->dir == NULL) { // Só tem filho à esquerda.
        // Liberação da memória alocada para o campo chave e para o nó.
        aux = (*v);
        (*v) = (*v)->esq; // Preservação da subárvore à esquerda do nó removido.
        libera(aux->info);
        free(aux);
        (*h) = 1;
      } else if ((*v)->esq == NULL) { // Só tem filho à direita.
        // Liberação da memória alocada para o campo chave e para o nó.
        aux = (*v);
        (*v) = (*v)->dir; // Preservação da subárvore à direita do nó removido.
        libera(aux->info);
        free(aux);
        (*h) = 1;
      } else { // Tem dois filhos.
        // Tratamento do antecessor, com mudança dos fatores de balanceamento/rotação caso necessário.
        trataAntecessor(&((*v)->esq), v, h, libera);

        /*
          Ajuste dos fatores de balanceamento/rotação (caso necessário), à esquerda pois o
          predecessor foi removido da subárvore à esquerda.
        */
        if ((*h)) {
          switch((*v)->bal) {
            case 1:
              (*v)->bal = 0;
              break;
            case 0:
              (*v)->bal = -1;
              (*h) = 0;
              break;
            case -1:
              rotacoesEsquerdaRemocao(v, h);
              break;
            default: break;
          }
        }
      }
    }
  }
}