/* 
  Nome: Arthur de Andrade Ferreira.
  Nome: Gabriel Alves Matos.
*/

#include "huffman.h"

No *criaNo(char caractere) {
  No *novo = (No*) malloc(sizeof(No)); // Cria o novo nó.

  // Caso a alocação tenha sido mal sucedida o programa é finalizado sem êxito.
  if (novo == NULL) {
    printf("ERRO: problemas com a alocacao de memoria.\n");
    exit(1);
  }

  // Atribui o caractere recebido por parâmetro ao campo caractere do nó e atribui
  // NULL aos campos prox, esq, dir e pai.
  novo->caractere = caractere;
  novo->prox = NULL;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->pai = NULL;

  // Atribui 1 ao campo freq (frequência).
  novo->freq = 1;
  return novo; // Retorno do novo nó.
}

No *buscaListaOrd(No *L, unsigned frequencia, No **pred) {
  // Criação de um ponteiro auxiliar que recebe o primeiro nó da lista
  // (desconsiderando o nó cabeça), e pred recebe o nó cabeça.
  No *aux = L->prox;
  (*pred) = L;
  // Laço responsável por percorrer toda a lista.
  while (aux != NULL) {
    // Se foi encontrado um nó com frequência menor ou igual à recebida via parâmetro
    // então o laço é finalizado.
    if (frequencia <= aux->freq) break;
    (*pred) = aux; // Atualização do predecessor para receber o nó atual.
 
    aux = aux->prox; // Atualização de aux para apontar para o próximo nó.
  }
  // Retorna o nó encontrado (ou NULL, caso a frequência seja maior que de todos nós da lista).
  return aux;
}

void insereFreqListaOrd(No *L, unsigned frequencia, No *x, No *y) {
  // Cria um nó novo fazendo com que ele receba o retorno da função criaNo para
  // um caractere "nulo".
  No *novo = criaNo('\0');

  // Atribui ao campo freq do novo nó o valor de frequência recebido via parâmetro
  // e faz x e y serem filhos à esquerda e à direita do novo nó, respectivamente.
  novo->freq = frequencia;
  novo->esq = x;
  novo->dir = y;

  // Faz o pai de x e y ser novo nó.
  x->pai = novo;
  y->pai = novo;

  // Cria um ponteiro pred e inicializa ele como NULL (predecessor de aux).
  No *pred = NULL;
  // Faz com que aux receba o nó que será buscado a partir da frequência recebida
  // como parâmetro utilizando a função buscaListaOrd.
  No *aux = buscaListaOrd(L, frequencia, &pred);

  // São efetuados os apontamentos para a inserção ordenada, o nó é inserido entre
  // pred e o "nó" (pode ser NULL) resultado da busca.
  novo->prox = aux;
  pred->prox = novo;
}

No *buscaCaractere(No *L, char caractere, No **pred) {
  // Criação de ponteiro auxiliar que aponta para o primeiro nó da lista.
  No *aux = L->prox;

  // Laço responsável por percorrer toda a lista.
  while(aux) {
    // Se o caractere do nó atual é igual ao buscado, o nó é retornado.
    if (aux && caractere == aux->caractere) return aux;
    (*pred) = aux; // Atualiza o ponteiro predecessor para apontar para o nó atual.

    aux = aux->prox; // Atualização de aux para apontar para o próximo nó.
  }

  // Se o nó não for retornado, é retornado NULL.
  return NULL;
}

void insereCaractereListaOrd(No *L, char caractere) {
  // São criados dois ponteiros auxiliares, um para o resultado da busca pelo caractere
  // e outro para seu predecessor.
  No *predResultado = L;
  No *resultadoBusca = buscaCaractere(L, caractere, &predResultado);

  /**
   * Caso já exista um nó com o caractere recebido por parâmetro, sua posição na
   * lista é ajustada caso seja necessário.Caso contrário, basta inserir um novo
   * nó no início da lista com o novo caractere (a frequência mínima é 1). 
  */
  if (resultadoBusca) {
    resultadoBusca->freq += 1;

    /**
     * Criação de dois ponteiros auxiliares: um para a posição para a qual o nó
     * será movido (nó com frequência menor que o em questão), caso haja necessidade
     * (sua frequência foi alterada) e outro para o predecessor deste nó.
    */ 
    No *aux = resultadoBusca->prox;
    No *predAux = NULL;

    // Laço para encontrar a posição para a qual o nó deve ser movido.
    while (aux && resultadoBusca->freq > aux->freq) {
      predAux = aux;
      aux = aux->prox;
    }

    // Houve iteração do laço (predAux foi atualizado), portanto é necessário alterar
    // a posição do nó na lista. Caso contrário, o nó já está em sua posição correta.
    if (predAux) {
      predResultado->prox = resultadoBusca->prox;
      resultadoBusca->prox = aux;
      predAux->prox = resultadoBusca;
    }

  } else {
    // É inserido no início da lista um nó com o caractere informado via parâmetro.
    No *novo = criaNo(caractere); // Criação de novo nó.

    // Verifica a existência de um nó além do nó cabeça na árvore e caso não exista
    // o novo nó é inserido como primeiro nó.
    if (!(L->prox)) {
      L->prox = novo;
    } else { // Se existir, o novo nó é inserido no início da lista.
      novo->prox = L->prox;
      L->prox = novo;
    }

    L->freq += 1; // É atualizado o número de nós na lista (campo "freq" do nó cabeça).
  }
}

No *retiraMin(No *L) {
  // Criação de nó auxiliar que aponta para o primeiro nó da lista.
  No *aux = L->prox;
  
  // Se existe um nó além do nó cabeça, este é retirado da lista, uma vez que ele
  // será o nó com menor frequência. 
  if (aux != NULL) {
    L->prox = aux->prox;
  }

  // Retorna o nó mínimo que foi retirado.
  return aux;
}

No *huffman(No *lista) {
  No *x, *y; // Ponteiros auxiliares para guardar o nó mínimo da lista.
  int soma = 0; // Auxiliar para guardar a soma das frequências de x e y.
  int tamanho = lista->freq; // Auxiliar para guardar a quantidade de nós na lista.

  // Tratativa que aborda o caso de o arquivo possuir apenas um caractere (repetido uma ou n vezes).
  if (tamanho == 1) {
    // É criado um nó para a raiz da árvore e o único nó da lista se torna seu filho à esquerda.
    // Assim garantimos que o código do caractere será 0.
    No *raiz = criaNo('\0');
    raiz->freq = lista->prox->freq;
    lista->prox->pai = raiz;
    raiz->esq = lista->prox;

    // Retorna a raiz da árvore de Huffman gerada.
    return raiz;
  }

  // Laço para gerar a árvore de huffman.
  for(int i=0; i<tamanho-1; i++) {
    // São retirados os dois nós mínimos da lista.
    x = retiraMin(lista);
    y = retiraMin(lista);
    // Faz-se a soma das frequências desses dois nós mínimos
    soma = x->freq + y->freq;
    // É inserido na lista de forma ordenada um nó interno com frequência igual à soma das frequências
    // dos nós mínimos retirados, sendo que estes se tornarão seus filhos.
    insereFreqListaOrd(lista, soma, x, y);
  }
  // Retorna o nó que restou na lista, que será a raiz da árvore.
  return retiraMin(lista);
}

void encontraFolha(No *arvore, No **noFolha, char caractere, int *encontrado) {
  // Nó folha não encontrado.
  if (*encontrado == 0) {
    // Procura na subárvore à esquerda.
    if (arvore->esq) {
      encontraFolha(arvore->esq, noFolha, caractere, encontrado);
    }

    // Procura na subárvore à direita.
    if (arvore->dir) {
      encontraFolha(arvore->dir, noFolha, caractere, encontrado);
    }

    // Foi encontrado um nó folha.
    if (!(arvore->esq) && !(arvore->dir)) {
      // O nó folha encontrado é o buscado (o campo "caractere" é igual ao recebido via parâmetro).
      if (arvore->caractere == caractere) {
        // A variável de controle recebe 1 (foi encontrado o nó folha).
        *encontrado = 1;
        // Atribuímos o nó atual ao nó da referência recebida via parâmetro para o nó folha.
        *noFolha = arvore;
      }
    }
  }
}

void geraCodigo(No *noFolha, char *codigo, int *posicao) {
  // Percorre da folha à raiz para encontrar o código binário do
  // caractere correspondente ao nó folha passado via parâmetro
  if (noFolha->pai) {
    geraCodigo(noFolha->pai, codigo, posicao);
    
    // Se o nó é filho à esquerda de seu pai a string é concatenada com '0'.
    if (noFolha == noFolha->pai->esq) {
      codigo[*posicao] = '0';
    // Se o nó é filho à direita de seu pai a string é concatenada com '1'.
    } else {
      codigo[*posicao] = '1';
    }
    // Atualiza a variável posicao.
    (*posicao) += 1;

    // Se não houver nó nem à esquerda nem à direita a string é concatenada com '\0'
    // indicando o fim do código que estava sendo gerado.
    if (!(noFolha->esq) && !(noFolha->dir)) {
      codigo[*posicao] = '\0';
    }

  } else {
    return; // O código já foi encontrado, a função é encerrada.
  }
}

void geraStringDeBits(unsigned char byte, char *stringGerada) {
  // Variável auxiliar para a posição da string.
  int i = 0;

  /**
   * É realizado um laço "for" que irá ser decrementado para percorrer o tamanho de um byte.
   * Usando operadores bitwise, é armazenado o bit em questão em formato de char na respectiva
   * posição da string "stringGerada".
  */
  for (int j = 7; 0 <= j; j--){
    stringGerada[i] = ((byte >> j) & (0x01)) + '0';
    i++;
  }
}

void liberaArvore(No *arvore) {
  // Se o nó é diferente de NULL, é necessário liberar a memória alocada para ele
  // e suas subárvores.
  if (arvore) {
    
    /**
     * Chama a função recursivamente para as subárvores à esquerda e à direita,
     * para liberar primeiro a memória alocada para estas antes de liberar a memória
     * alocada para o nó atual.
    */
    liberaArvore(arvore->esq);
    liberaArvore(arvore->dir);
    // Libera a memória alocada para o nó atual.
    free(arvore);
  }
}

void comprime(char *arquivoEntrada, char *arquivoSaida) {
  // Bloco de variáveos que serão responsáveis por mostrar o tempo que a compressão leva.
  clock_t inicio, final;
  double tempoGasto;
  inicio = clock();
  
  // Listas caractere-frequência.
  No *L = (No*) calloc (1, sizeof(No));
  No *G = (No*) calloc (1, sizeof(No));

  // Atribuição das aberturas dos arquivos aos ponteiros "entrada" e "saida", respectivamente.
  FILE *entrada = fopen(arquivoEntrada, "r");
  FILE *saida = fopen(arquivoSaida, "wb");
  
  // Erro na abertura do arquivo de entrada.
  if (!entrada) {
    printf("Arquivo de entrada inexistente!\n\n");
    return;
  }

  // Erro na abertura do arquivo de saída.
  if (!saida) {
    printf("Arquivo de saida inexistente!\n\n");
    return;
  }

  char caractereAtual = '\0'; // Auxiliar para ler os caracteres do arquivo de texto.
  
  // Laço que percorre o arquivo de entrada preenchendo as lista caractere-frequência.
  while((caractereAtual=fgetc(entrada)) != EOF) {
    insereCaractereListaOrd(L, caractereAtual);
    insereCaractereListaOrd(G, caractereAtual);
  }

  // "Rebobinação" do arquivo de entrada.
  rewind(entrada);
  
  // O ponteiro do stream 'saida' é movido para a posição posterior ao tamanho da
  // struct Cabecalho.
  fseek(saida, sizeof(Cabecalho), SEEK_SET);

  // Ponteiro auxiliar para percorrer a lista caractere-frequência que recebe inicialmente
  // o primeiro nó da lista.
  No *auxiliarListaFrequencias = L->prox;
  
  // Percorre toda a lista L gravando cada nó no arquivo de saída.
  while(auxiliarListaFrequencias) {
    // Escreve o nó apontado por "auxiliarListaFrequencias" no arquivo de saída.
    fwrite(auxiliarListaFrequencias, sizeof(No), 1, saida);
    // Atualiza "auxiliarListaFrequencias" para apontar para o próximo nó da lista.
    auxiliarListaFrequencias = auxiliarListaFrequencias->prox;
  }

  // Criação da árvore de Huffman para a lista caractere-frequência montada.
  No *arvore = huffman(L);

  // Criação do cabeçalho.
  Cabecalho cabecalho;
  cabecalho.tamanhoLista = L->freq;
  cabecalho.excedentes = 0;
  cabecalho.numBytes = 0;

  /**
   * Criação de variáveis que serão importantes para controlar a posição utilizada
   * na função "geraCodigo", o byte que será armazenado no arquivo de saída e a
   * quantidade de bits ocupados no byte que será gravado.
  */
  unsigned char armazenar = 0;
  int posicao = 0;
  int bitsOcupados = 0;

  /**
   * Criação de variávies que serão importantes para controlar o número de bytes
   * gravados no arquivo de saída, o números de bits excedentes no último byte gravado
   * e para verificar se o nó folha do caractere foi encontrado.
  */
  int numBytes = 0;
  int numExcedentes = 0;
  int encontrado = 0;
  
  // Ponteiro auxiliar que aponta para o nó folha na árvore de Huffman para o
  // caractere de interesse.
  No *noFolha = NULL;

  // Laço que percorre o arquivo de entrada e é responsável por fazer sua compressão.
  while((caractereAtual=fgetc(entrada)) != EOF) {
    posicao = 0; // Posição deve zerar para gerar a string do novo caractere.
    encontrado = 0; // O nó folha do caractere ainda não foi encontrado.
    char codigo[1024]; // String que guardará o código de Huffman gerado para o caractere.

    /**
     * É encontrado o nó folha na árvore para o caractere atual e gerada a string
     * com o código de Huffman para o mesmo utilizando as funções "encontraFolha"
     * e "geraCodigo", respectivamente.
    */
    encontraFolha(arvore, &noFolha, caractereAtual, &encontrado);
    geraCodigo(noFolha, codigo, &posicao);

    // Laço para percorrer a string com o código de Huffman do caractere.
    for (char *i = codigo; *i; i++) {
      /**
       * Caso a posição atual contenha o caractere 1 é inserido um bit 1 na
       * extremidade direita do byte. Caso contrário um bit 0 é inserido na
       * extremidade direita do byte.
      */
      if (*i == '1') {
        armazenar = (armazenar << 1) + 1;
      } else if (*i == '0') {
        armazenar = armazenar << 1;
      }

      bitsOcupados++; // É acrescida em um unidade a quantidade de bits ocupados no byte.

      // Caso um byte tenha sido completamente ocupado ele é escrito no arquivo de saída.
      if (bitsOcupados == 8) {
        // Escreve o conteúdo de "armazenar" no arquivo de saída.
        fwrite(&armazenar, sizeof(unsigned char), 1, saida);
        // São zeradas as variável de quantidade de bits ocupados (bitsOcupados) e do
        // byte a ser escrito (armazenar).
        armazenar = 0;
        bitsOcupados = 0;
        
        // É acrescida em uma unidade a quantidade de bytes gravados no arquivo de saída.
        numBytes++;
      }
    }
  }

  // Caso tenha sobrado bits não escritos no arquivo de saída, é escrito um byt
  // com bits excedentes.
  if (bitsOcupados != 0) {
    // Os bits que interessam são movidos para a extremidade esquerda do byte.
    numExcedentes = 8 - bitsOcupados;
    armazenar = armazenar << numExcedentes;

    // É armazenado no cabeçalho a nova quantidade de bits excedentes.
    cabecalho.excedentes = numExcedentes;
    // É acrescida em uma unidade a quantidade de bytes gravados no arquivo de saída.
    numBytes++;

    // Escreve o conteúdo de "armazenar" no arquivo de saída.
    fwrite(&armazenar, sizeof(char), 1, saida);
  }

  // O campo "numBytes" recebe a variável "numBytes" que foi devidamente preenchida.
  cabecalho.numBytes = numBytes;

  // "Rebobina" o arquivo de saída.
  rewind(saida);

  // Escreve o conteúdo do cabeçalho no arquivo de saída.
  fwrite(&cabecalho, sizeof(Cabecalho), 1, saida);

  // É encerrada a contagem do tempo de execução.
  final = clock();
  tempoGasto = (double)(final - inicio) / CLOCKS_PER_SEC;

  auxiliarListaFrequencias = G->prox;
  char codigo[1024] = "";
  encontrado = 0;

  // É utilizado um laço para percorrer a lista G mostrando na tela cada caractere
  // do arquivo de entrada com seu número de ocorrências e seu código de Huffman.
  printf("\tCodigo de Huffman gerado:\n\n");
  while(auxiliarListaFrequencias) {
    encontrado = 0;
    strcpy(codigo, "");
    posicao = 0;
    printf("%c [%d] : ", auxiliarListaFrequencias->caractere, auxiliarListaFrequencias->freq);

    encontraFolha(arvore, &noFolha, auxiliarListaFrequencias->caractere, &encontrado);
    geraCodigo(noFolha, codigo, &posicao);

    printf("%s\n", codigo);
    auxiliarListaFrequencias = auxiliarListaFrequencias->prox;
  }

  // É utilizado um laço para liberar a memória alocada para os nós da lista G.
  No *liberar = NULL;
  auxiliarListaFrequencias = G;
  while (auxiliarListaFrequencias->prox) {
    liberar = auxiliarListaFrequencias;
    auxiliarListaFrequencias = auxiliarListaFrequencias->prox;
    free(liberar);
  }

  fclose(saida); // Fecha o arquivo de saída.
  fclose(entrada); // Fecha o arquivo de entrada.
  free(L); // Limpa a memória alocada para o nó cabeça da lista L.
  liberaArvore(arvore); // Limpa a memória alocada para a árvore gerada pelo código de Huffman.
  
  printf("\nTempo gasto na compressao: %gs\n\n", tempoGasto);
}

void descomprime(char *arquivoEntrada, char *arquivoSaida) {
  // Bloco de variáveos que serão responsáveis por mostrar o tempo que a compressão leva.
  clock_t inicio, final;
  double tempoGasto;
  inicio = clock();
  
  // Criação do cabeçalho, da lista caractere-frequência e de um ponteiro auxiliar
  // para percorrê-la.
  Cabecalho cabecalho;
  No *listaFrequencias = (No *) calloc(1, sizeof(No));
  No *auxiliarLista = listaFrequencias;

  // Atribuição das aberturas dos arquivos aos ponteiros "entrada" e "saida", respectivamente.
  FILE *entrada = fopen(arquivoEntrada, "rb");
  FILE *saida = fopen(arquivoSaida, "w");

  // Erro na abertura do arquivo de entrada.
  if (!entrada) {
    printf("Arquivo de entrada inexistente!\n\n");
    return;
  }

  // Erro na abertura do arquivo de saída.
  if (!saida) {
    printf("Arquivo de saida inexistente!\n\n");
    return;
  }

  // Atribuição da leitura do cabeçalho gravado no arquivo binário à variável "cabecalho".
  fread(&cabecalho, sizeof(Cabecalho), 1, entrada);

  // Atualiza a quantidade de nós na lista de caractere-frequências com o valor
  // guardado no cabeçalho.
  listaFrequencias->freq = cabecalho.tamanhoLista;

  // Criação de ponteiro auxiliar para receber os nós guardados no arquivo comprimido.
  No *aux = NULL;
  // Laço responsável por ler os nós guardados no arquivo comprimido e realizar o
  // encadeamento desses nós com a lista caractere-frequência local (listaFrequencias).
  for (int i=0; i<cabecalho.tamanhoLista; i++) {
    aux = (No *) malloc(sizeof(No));
    fread(aux, sizeof(No), 1, entrada); // Leitura de nó armazenado no arquivo binário.

    // Encadeamento do nó lido à lista "listaFrequencias".
    auxiliarLista->prox = aux;
    // Atualização do ponteiro auxiliar da lista "listaFrequencias".
    auxiliarLista = auxiliarLista->prox;
  }

  // Criação da árvore de Huffman para a lista lida do arquivo binário.
  No *arvore = huffman(listaFrequencias);

  // Criação de variáveis auxiliares para guardar o byte lido do arquivo binário
  // "byte" e o código em string do byte "codigoByte".
  unsigned char byte = 0;
  char codigoByte[9] = "";

  /**
   * Criação de variáveis para controlar qual é o bit atual do byte lido "bitAtual",
   * a quantidade de bits que devem ser lidos do código do byte "limite" e o número
   * do byte lido comparado à quantidade de bytes gravados "byteAtual".
  */
  char bitAtual = '\0';
  unsigned limite = 8; // Inicializada com 8 (quantidade de bits em um byte).
  unsigned byteAtual = 1;
  
  // Criação de ponteiro auxiliar para percorrer a árvore de Huffman em busca de
  // um nó folha (que guarda um caractere).
  No *noAtual = arvore;

  // Laço que percorre o arquivo de entrada e é resposável por fazer sua descompressão.
  while(fread(&byte, sizeof(unsigned char), 1, entrada)) {
    // Atribuição da string gerada para a sequência de bits do byte lido à string "codigoByte".
    geraStringDeBits(byte, codigoByte);

    // Caso o byte atual seja o último gravado no arquivo, o limite é ajustado para
    // que não sejam descomprimidos os bits excedentes.
    if (byteAtual == cabecalho.numBytes) limite = 8 - cabecalho.excedentes;
    
    /**
     * Laço responsável por percorrer a string da sequência de bits gerada e percorrer
     * a árvore a depender do conteúdo de cada posição até encontrar um nó folha na
     * árvore (um caractere foi encontrado).
    */
    for(int i=0; i<limite;  i++) {
      // A variável "bitAtual" recebe o char da posição "i" da string "codigoByte".
      bitAtual = codigoByte[i];
       
      // Caso o bit atual tenha valor 1 o ponteiro auxiliar "noAtual" recebe seu
      // filho à direita e caso contrário recebe seu filho à esquerda.
      noAtual = bitAtual == '1' ? noAtual->dir : noAtual->esq;
    
      // Caso tenha sido atingido um nó folha (sem filhos) então foi encontrado um
      // caractere na árvore de Huffman.
      if (!(noAtual->esq) && !(noAtual->dir)) {
        // O caractere encontrado é escrito no arquivo de saída.
        fwrite(&(noAtual->caractere), sizeof(char), 1, saida);
        
        // O ponteiro auxiliar para percorrer a árvore "noAtual" é atualizado para
        // apontar para a raiz da árvore novamente.
        noAtual = arvore;
      }
    }
    
    byteAtual++; // A contagem do byte lido do arquivo comprimido é acrescida em uma unidade. 
  }

  // É encerrada a contagem do tempo de execução.
  final = clock();
  tempoGasto = (double)(final - inicio) / CLOCKS_PER_SEC;
  printf("Tempo gasto na descompressao: %gs\n\n", tempoGasto);
  
  fclose(entrada); // Fecha o arquivo de entrada.
  fclose(saida); // Fecha o arquivo de saida.

  // Libera a memória alocada para o nó cabeça da lista "listaFrequencias".
  free(listaFrequencias);
  // É liberada a memória alocada para os nós da árvore de Huffman gerada.
  liberaArvore(arvore);
}