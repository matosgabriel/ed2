/* 
  Nome: Arthur de Andrade Ferreira.
  Nome: Gabriel Alves Matos.
*/

#ifndef __RB_H__
#define __RB_H__

// Criação da estrutura Node que é utilizada pela biblioteca para representar os nós da árvore.
typedef struct node {
  void *chave;
  int cor;

  struct node *esq;
  struct node *dir;
  struct node *pai;
} Node;

Node *externo;

// Inclusão de outras interfaces necessárias para entender esta interface.

#include <stdio.h>
#include <stdlib.h>

// Protótipos das funções da biblioteca.

// Função para criação de um novo nó com campo chave igual a "chave".
Node *criaNode(void *chave);

// Função de busca na árvore rubro-negra para uma chave igual a "chave".
Node *busca(Node *T, void *chave, int (*compara) (void *, void *));

// Função de impressão da árvore.
void imprimeArvore(Node *T, int nivel, void (*imprimeChave) (void *));

// Função que realiza uma rotação à esquerda na árvore "T" em relação ao nó w.
void rotacaoEsquerda(Node **T, Node *w);

// Função que realiza uma rotação à direita na árvore "T" em relação ao nó w.
void rotacaoDireita(Node **T, Node *w);

// Função que busca um nó com chave mínima na árvore rubro-negra.
Node *RBMinimo(Node *w);

// Função que busca o sucessor de um nó na árvore rubro-negra.
Node *RBSucessor(Node *z);

// Função que corrige as possíveis violações na árvore rubro-negra, para inserção.
void RBInsertFixup(Node **T, Node *q);

// Função de inserção em uma árvore rubro-negra.
void RBInsercao(Node **T, Node *q, int (*compara) (void *, void *));

// Função que transfere o pai de "u" (nó) para o pai de "v" (nó), na árvore rubro-negra.
void RBTransferePai(Node **T, Node *u, Node *v);

// Função que corrige as possíveis violações na árvore rubro-negra, para remoção.
void RBDeleteFixup(Node **T, Node *x);

// Função de remoção em uma árvore rubro-negra.
void RBRemocao(Node **T, Node *z, void (*liberaInfo) (void *));

// Função de impressão de uma chave da árvore.
void imprimeNode(Node *T, void *valor, int (*compara)(void *, void *), void (*imprimeDados)(void *));

// Função de liberação da memória alocada para a nó.
void liberaNode(Node *node, void (*liberaInfo) (void *));

// Função de liberação da memória alocada para a árvore.
void liberaArvore(Node *T, void (*libera) (void *));

#endif