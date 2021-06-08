/* 
  Nome: Arthur de Andrade Ferreira.
  Nome: Gabriel Alves Matos.
*/

#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

// Inclusão de outras interfaces necessárias para entender esta interface.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Estrutura do nó que será utilizado na lista caractere-frequência e na árvore gerada pelo código de Huffman.
 */
typedef struct no {
  char caractere;
  unsigned freq; // Frequência do caractere no arquivo ou, caso seja nó interno na árvore, soma das frequências de seus filhos.
  struct no *prox;
  struct no *esq, *dir, *pai;
} No;

/**
 * @brief Estrutura que faz a implementação do cabeçalho, que será importante para, principalmente,
 * verificar os bits excedentes do arquivo e não os descomprimir.
 */
typedef struct cabecalho {
  unsigned excedentes; // Número de bits excedentes no último byte escrito.
  unsigned tamanhoLista; // Tamanho da lista caractere-frequência.
  unsigned numBytes; // Número de bytes (que contêm códigos para caracteres) escritos no arquivo.
} Cabecalho;

// Protótipos das funções implementadas

/**
 * @brief Função para criação de um novo nó com campo chave igual a "chave".
 * 
 * @param caractere Caractere que será criado na lista.
 * @return Retorna o respectivo nó que foi criado.
 */
No *criaNo(char caractere);

/**
 * @brief Função que busca um nó na lista caractere-frequência pela frquência.
 * 
 * @param L Nó cabeça da árvore.
 * @param frequencia Frequência a ser buscada.
 * @param pred Referência do nó predecessor ao nó que contém a frequência buscada 
 * (precisamos deste após realizar a busca).
 * @return Retorna o nó buscado a partir da frequência dele.
 */
No *buscaListaOrd(No *L, unsigned frequencia, No **pred);

/**
 * @brief Função que insere um nó da árvore gerada no código de Huffman na fila 
 * (lista caractere-frequência ordenada pela frequência).
 * 
 * @param L Nó cabeça da fila.
 * @param frequencia Soma das frequências dos filhos do nó na árvore.
 * @param x Nó que deve se tornar filho à esquerda na árvore.
 * @param y Nó que deve se tornar filho à direita na árvore.
 * @return Não há retorno.
 */
void insereFreqListaOrd(No *L, unsigned frequencia, No *x, No *y);

/**
 * @brief Função que busca um nó na lista caractere-frequência pelo caractere.
 * 
 * @param L Nó cabeça da árvore.
 * @param caractere Caractere a ser buscado.
 * @param pred Referência do nó predecessor ao nó que contém o caractere buscado 
 * (precisamos deste após realizar a busca).
 * @return Retorna o nó buscado se ele existir, se não é retornado NULL.
 */
No *buscaCaractere(No *L, char caractere, No **pred);

/**
 * @brief Função que insere um caractere na lista caractere-frequência mantendo a ordenação por frequência.
 * 
 * @param L  Referência a lista de nós.
 * @param caractere Caractere a ser inserido na lista.
 * @return Não há retorno.
 */
void insereCaractereListaOrd(No *L, char caractere);

/**
 * @brief Função que retira, da lista, o nó com menor frequência.
 * 
 * @param L Referência a lista de nós.
 * @return Retorna o respectivo nó retirado da lista. 
 */
No *retiraMin(No *L);

/**
 * @brief Função que constrói a árvore de huffman
 * 
 * @param fila Fila de prioridade.
 * @return Não há retorno.
 */
No *huffman(No *fila);

/**
 * @brief Função que encontra o nó folha do caractere na árvore gerada no código de Huffman.
 * 
 * @param arvore Nó raiz da árvore do código de Huffman.
 * @param noFolha Referência do ponteiro que irá apontar para o nó folha encontrado.
 * @param caractere Caractere que deve ser encontrado o nó folha correspondente.
 * @param encontrado Variável de controle para determinar se o nó folha foi encontrado (0 = não encontrado, 1 = encontrado).
 * @return Não há retorno. 
 */
void encontraFolha(No *arvore, No **noFolha, char caractere, int *encontrado);

/**
 * @brief Função que percorre da folha à raiz para gerar o código de Huffman do caractere correspondente.
 * 
 * @param noFolha Nó folha do caractere.
 * @param codigo String do código de Huffman para o caractere.
 * @param posicao Posição da string que deve ser atualizada no passo recursivo.
 * @return Não há retorno. 
 */
void geraCodigo(No *noFolha, char *codigo, int *posicao);

/**
 * @brief Função que gera uma cadeia de string de cada bit do arquivo.
 * 
 * @param bits Bit a ser lido pela função.
 * @param stringGerada String gerada a partir da leitura dos bits.
 * @return Não há retorno.
 */
void geraStringDeBits(unsigned char bits, char *stringGerada);

/**
 * @brief Função que libera a memória alocada para os nós da árvore.
 * 
 * @param arvore árvore a qual deve ser liberada a memória alocada.
 * @return Não há retorno.
 */
void liberaArvore(No *arvore);

/**
 * @brief Função que comprime um arquivo de texto.
 * 
 * @param arquivoEntrada Nome do arquivo de texto a ser comprimido.
 * @param arquivoSaida Nome do arquivo binário gerado. 
 * @return Não há retorno. 
 */
void comprime(char *arquivoEntrada, char *arquivoSaida);

/**
 * @brief Função de descompressão de um arquivo binário
 * 
 * @param arquivoEntrada nome do arquivo binário a ser descompresso
 * @param arquivoSaida nome do arquivo de texto gerado
 * @return Não há retorno.
 */
void descomprime(char *arquivoEntrada, char *arquivoSaida);

#endif