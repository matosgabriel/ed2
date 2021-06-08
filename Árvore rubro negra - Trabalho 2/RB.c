/* 
  Nome: Arthur de Andrade Ferreira.
  Nome: Gabriel Alves Matos.
*/

#include "RB.h"

Node *criaNode(void *chave) {
  Node *novo = (Node *) calloc(1, sizeof(Node));

  // Caso a alocação tenha sido mal sucedida o programa é finalizado sem êxito.
  if (!novo) exit(1);

  // Atribui a chave recebida por parâmetro ao campo chave do nó e atribui a cor negra ao nó.
  novo->chave = chave;
  novo->cor = 0;

  // Atribui o nó externo aos campos de pai, subárvore à esquerda e subárvore à direita do nó.
  novo->dir = externo;
  novo->esq = externo;
  novo->pai = externo;

  return novo; // Retorno do novo nó.
}

Node *busca(Node *T, void *chave, int (*compara) (void *, void *)) {
  // Nó não existe na árvore.
  if (T == externo) return NULL;
  // Se existe está na subárvore à esquerda.
  else if (compara(T->chave, chave) > 0) return busca(T->esq, chave, compara);
  // Se existe está na subárvore à direita.
  else if (compara(T->chave, chave) < 0) return busca(T->dir, chave, compara);
  // Nó encontrado.
  else return T;
}

void rotacaoEsquerda(Node **T, Node *w) {
  Node *v = w->dir; // v recebe o filho à direita de w.

  w->dir = v->esq; // O filho à esquerda de v se torna o filho à direita de w.

  // Caso o filho à esquerda de v seja diferente do nó externo, seu pai agora é w.
  if (v->esq != externo) {
    v->esq->pai = w;
  }

  v->pai = w->pai; // O pai de v recebe o pai de w.

  // Caso o pai de w seja o no externo (então w é raiz da árvore), v se torna a raiz da árvore.
  if (w->pai == externo) {
    (*T) = v;
  } else { // Caso w não seja raiz, é preciso atualizar o pai de w para que este aponte para v.
    if (w == w->pai->esq) { // w é filho à esquerda de seu pai, então v se torna filho à esquerda do pai de w.
      w->pai->esq = v;
    } else { // w é filho à direita de seu pai, então v se torna filho à direita do pai de w.
      w->pai->dir = v;
    }
  }

  v->esq = w; // w se torna o filho à esquerda de v.
  w->pai = v; // O pai de w se torna v.
}

void rotacaoDireita(Node **T, Node *w) {
  Node *v = w->esq; // v recebe o filho à esquerda de w.

  w->esq = v->dir; // O filho à direita de v se torna o filho à esquerda de w.

  // Caso o filho à esquerda de v seja diferente do nó externo, seu pai agora é w.
  if (v->dir != externo) {
    v->dir->pai = w;
  }

  v->pai = w->pai; // O pai de v recebe o pai de w.

  // Caso o pai de w seja o no externo (então w é raiz da árvore), v se torna a raiz da árvore.
  if (w->pai == externo) {
    (*T) = v;
  } else { // Caso w não seja raiz, é preciso atualizar o pai de w para que este aponte para v.
    if (w == w->pai->esq) { // w é filho à esquerda de seu pai, então v se torna filho à esquerda do pai de w.
      w->pai->esq = v;
    } else { // w é filho à direita de seu pai, então v se torna filho à direita do pai de w.
      w->pai->dir = v;
    }
  }

  v->dir = w; // w se torna o filho à direita de v.
  w->pai = v; // O pai de w se torna v.
}

void RBInsertFixup(Node **T, Node *q) {
  Node *v; // Pai do nó inserido.
  Node *w; // Avô do nó inserido.
  Node *t; // Tio do nó inserido.

  while(q->pai->cor == 0) {
    v = q->pai; w = v->pai;

    if (v == w->esq) { // O pai do nó inserido é filho à esquerda do avô.
      t = w->dir;

      if (t->cor == 0) { // Caso 1.
        t->cor = 1;
        v->cor = 1;
        w->cor = 0;

        q = w; // Uma violação da propriedade de rubro seguido de rubro pode ter ocorrido.
      } else {
        if (q == v->dir) { // O nó inserido é filho à direita de seu pai (caso 2).
          q = v; // O nó inserido é trocado com seu pai, o que afetará na mudança de cor depois da condição.
          rotacaoEsquerda(T, q);
        }

        q->pai->cor = 1; // O pai recebe a com negra.
        w->cor = 0; // O avô recebe a cor rubro.
        
        rotacaoDireita(T, w); // Caso 3.
      }

    } else { // O pai do nó inserido é filho à direita do avô.
      t = w->esq;

      if (t->cor == 0) { // Caso 1.
        t->cor = 1;
        v->cor = 1;
        w->cor = 0;

        q = w; // Uma violação da propriedade de rubro seguido de rubro pode ter ocorrido.
      } else {
        if (q == v->esq) { // O nó inserido é filho à direita de seu pai (caso 4).
          q = v; // O nó inserido é trocado com seu pai, o que afetará na mudança de cor depois da condição.
          rotacaoDireita(T, v);
        }

        q->pai->cor = 1; // O antigo pai recebe a com negra.
        w->cor = 0; // O antigo avô recebe a cor rubro.
        
        rotacaoEsquerda(T, w); // Caso 5.
      }
    }
  }

  (*T)->cor = 1; // A raiz recebe a cor negra.
}

void RBInsercao(Node **T, Node *q, int (*compara) (void *, void *)) {
  Node *x = (*T); // Nó auxiliar para percorrer a árvore.
  Node *v = externo; // O pai do nó a ser inserido.

  // Laço responsável por encontrar posição de inserção do nó na árvore.
  while(x != externo) {
    // Já existe nó com a chave procurada, portanto não é inserida novamente.
    if (compara(x->chave, q->chave) == 0) return;
    
    v = x; // Atualiza o nó auxiliar que será pai do nó inserido.

    // A chave é "menor" que a chave atual, então o nó deve ser inserido na subárvore à esquerda.
    if (compara(q->chave, x->chave) < 0) x = x->esq;
    // A chave é "maior" que a chave atual, então o nó deve ser inserido na subárvore à direita.
    else x = x->dir;
  }

  q->pai = v; // O pai do nó inserido será v.

  if (v == externo) { // A árvore é vazia.
    (*T) = q; // A nova raiz será o nó inserido.
  } else {
    if (compara(q->chave, v->chave) < 0) v->esq = q; // Nó inserido à esquerda.
    else v->dir = q; // Nó inserido à direita.
  }

  // Atribui o nó externo aos campos de filhos à direita e à esquerda do nó inserido.
  q->esq = externo;
  q->dir = externo;
  q->cor = 0; // O nó inserido recebe a cor rubro.
  // Chamada de função que corrige possível violação das propriedades de árvore rubro-negra.
  RBInsertFixup(T, q);
}

void imprimeArvore(Node *T, int nivel, void (*imprimeChave) (void *)) {
  // Só é impressa a chave do nó e de seus filhos caso este seja diferente de externo.
  if (T != externo) {
    imprimeArvore(T->dir, nivel+1, imprimeChave); // Impressão da subárvore à direita.
    
    // Laço para impressão da quantidade de tabulações correspondente ao nível do nó.
    for(int i=0; i<nivel-1; i++) {
      printf("\t");
    }
    
    imprimeChave(T->chave); // Impressão da chave do nó.
    T->cor == 1 ? printf(": negro]\n") : printf(": rubro]\n"); // Impressão da cor do nó.

    imprimeArvore(T->esq, nivel+1, imprimeChave); // Impressão da subárvore à esquerda.
  }
}

void RBTransferePai(Node **T, Node *u, Node *v) {
  if (u->pai == externo) { // u é a raiz.
    (*T) = v; // A nova raiz é v.
  } else {
    if (u == u->pai->dir) { // u é filho à direita de seu pai.
      u->pai->dir = v; // Faz v ser fiho à direita do pai de u.
    } else { // u é filho à esquerda de seu pai.
      u->pai->esq = v; // Faz v ser fiho à esquerda do pai de u.
    }
  }

  // Faz o pai de v ser o pai de u.
  v->pai = u->pai;
}

Node *RBSucessor(Node *z) {
  Node *sucessor = z->dir; // O sucessor no início é o filho à direita de z.
  
  // Laço responsável por alcançar o sucessor na subárvore à esquerda.
  while(sucessor->esq != externo) {
    sucessor = sucessor->esq; // Atualiza o sucessor para seu filho à esquerda.
  }

  return sucessor; // Retorno do sucessor.
}

void RBDeleteFixup(Node **T, Node *x) {
  Node *w; // Irmão de x.
  
  // Laço responsável por tratar a violação da propriedade de altura negra (no laço, x é sempre um nó duplo negro).
  while(x != (*T) && x->cor == 1) {
    
    if (x == x->pai->esq) { // x é filho à esquerda.
      w = x->pai->dir; // O irmão x é o filho à direita de seu pai.

      if (w->cor == 0) { // Caso 1 (obrigatoriamente os filhos de w são negros).
        w->cor = 1;
        x->pai->cor = 0;
        rotacaoEsquerda(T, x->pai);
        w = x->pai->dir;
      }

      if (w->dir->cor == 1 && w->esq->cor == 1) { // Caso 2 (w é negro e os dois filhos são negros).
        w->cor = 0;
        x = x->pai;
      } else {

        if (w->dir->cor == 1) { // Caso 3 (w é negro e somente o filho à direita é negro).
          // Fazemos se tornar o caso 4.
          w->esq->cor = 1;
          w->cor = 0;
          rotacaoDireita(T, w);
          w = x->pai->dir;
        }

        // Caso 4 (w é negro e o filho à direita é rubro).
        w->cor = x->pai->cor;
        x->pai->cor = 1;
        w->dir->cor = 1;
        rotacaoEsquerda(T, x->pai);
        x = (*T);
      }
    } else {

      w = x->pai->esq; // O irmão de x é o filho à esquerda de seu pai.

      if (w->cor == 0) { // Caso 1 (obrigatoriamente os filhos de w são negros).
        w->cor = 1;
        x->pai->cor = 0;
        rotacaoDireita(T, x->pai);
        w = x->pai->esq;
      }

      if (w->dir->cor == 1 && w->esq->cor == 1) { // Caso 2 (w é negro e os dois filhos são negros).
        w->cor = 0;
        x = x->pai;
      } else {

        if (w->esq->cor == 1) { // Caso 3 (w é negro e somente o filho à direita é negro).
          // Fazemos se tornar o caso 4
          w->dir->cor = 1;
          w->cor = 0;
          rotacaoEsquerda(T, w);
          w = x->pai->esq;
        }

        // Caso 4 (w é negro e o filho à direita é rubro).
        w->cor = x->pai->cor;
        x->pai->cor = 1;
        w->esq->cor = 1;
        rotacaoDireita(T, x->pai);
        x = (*T);
      }
    }
  }

  x->cor = 1; // O nó x é pintado de negro.
}

void RBRemocao(Node **T, Node *z, void (*liberaInfo) (void *)) {
  Node *x; // Nó que possivelmente será corrigido.
  Node *y; // Nó que irá ocupar o vértice z.
  int corDeY;

  y = z;
  corDeY = y->cor;

  if (z->esq == externo) { // Caso A.
    x = z->dir;
    RBTransferePai(T, z, z->dir);
  } else {
    if (z->dir == externo) { // Caso B.
      x = z->esq;
      RBTransferePai(T, z, z->esq);
    } else { // Casos C e D (dois filhos).
      y = RBSucessor(z);
      corDeY = y->cor;
      x = y->dir;

      if (y->pai == z) { // y é filho a direita de z.
        x->pai = y;
      } else { // y tem um pai diferente de z.
        RBTransferePai(T, y, y->dir);
        y->dir = z->dir;
        y->dir->pai = y;
      }

      // Troca o pai de y por z.
      RBTransferePai(T, z, y);
      y->esq = z->esq;
      y->esq->pai = y;
      y->cor = z->cor;
    }
  }

  if (corDeY == 1) { // Caso a cor do nó removido era negra.
    // Correção de violação da propriedade de altura negra, pois foi removido um nó negro.
    RBDeleteFixup(T, x);
  }

  liberaNode(z, liberaInfo); // Liberação da memória alocada para o nó removido.
}

void imprimeNode(Node *T, void *valor, int (*compara)(void *, void *), void (*imprimeDados)(void *)) {
  // Ponteiro "resultado" receberá o resultado da busca de "valor" na árvore "T".
  Node *resultado = busca(T, valor, compara);

  /*
    Se o resultado da busca for diferente de NULL será utilizada a função
    imprimeDados para imprimir o valor genérico armazenado no campo "chave" do nó.
  */
  if (resultado)
    imprimeDados(resultado->chave);
}

void liberaNode(Node *node, void (*liberaInfo) (void *)) {
  // Liberação da memória alocada para o campo "chave".
  liberaInfo(node->chave);
  free(node); // Liberação da memória alocada para o nó.
}

void liberaArvore(Node *T, void (*liberaInfo) (void *)) {
  if (T != externo) { // Nó não externo.
    // Chamada recursiva da função para a liberação das subárvores do nó atual.
    liberaArvore(T->dir, liberaInfo);
    liberaArvore(T->esq, liberaInfo);
    liberaNode(T, liberaInfo); // Liberação da memória alocada para o nó atual.
  }
}