/* 
  Nome: Arthur de Andrade Ferreira
  Nome: Gabriel Alves Matos
*/

#ifndef __AVL_H__
#define __AVL_H__

// Criação da estrutura Node que é utilizada pela biblioteca para representar os nós da árvore.
typedef struct node {
  void *info;
  int bal;
  struct node *dir, *esq;
} Node;

// Inclusão de outras interfaces necessárias para entender esta interface.

#include <stdio.h>
#include <stdlib.h>

// Protótipos das funções da biblioteca.

// Função para criação de um novo nó com campo info igual a "info".
Node *criaNode(void *info);

// Função de busca na árvore AVL para uma chave "valor".
Node *buscaArvore(Node *T, void *valor, int (*compara) (void *, void *));

// Função de impressão da árvore.
void imprimeArvore(Node *T, int nivel, void (*imprime) (void *));

// Função de impressão das informações do campo "info" de um nó.
void imprimeNode(Node *T, void *valor, int (*compara)(void *, void *), void (*imprimeDados)(void *));

// Função de liberação da memória alocada para a nó.
void liberaNode(Node *node, void (*liberaInfo) (void *));

// Função de liberação da memória alocada para a árvore.
void liberaArvore(Node *T, void (*libera) (void *));

// Função que realiza uma rotação à direita (simples ou dupla) na árvore "v" para uma inserção.
void rotacoesDireitaInsercao(Node **v, int *h);

// Função que realiza uma rotação à esquerda (simples ou dupla) na árvore "v" para uma inserção.
void rotacoesEsquerdaInsercao(Node **v, int *h);

// Função de inserção em uma árvore AVL.
void insereAVL(Node **v, int *h, void *x, int (*compara) (void *, void *));

// Função que realiza uma rotação à direita (simples ou dupla) na árvore "v" para uma remoção.
void rotacoesDireitaRemocao(Node **v, int *h);

// Função que realiza uma rotação à esquerda (simples ou dupla) na árvore "v" para uma remoção.
void rotacoesEsquerdaRemocao(Node **v, int *h);

// Função que trata o antecessor, com mudança dos fatores de balanceamento/rotação caso necessário.
void trataAntecessor(Node **v, Node **remover, int *h, void (*libera) (void *));

// Função de remoção em uma árvore AVL.
void removeAVL(Node **v, int *h, void *x, int (*compara) (void *, void *), void (*libera) (void *));

#endif