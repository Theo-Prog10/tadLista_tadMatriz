#ifndef ___T__AD_L_I_S_T__

#define ___T__AD_L_I_S_T__

typedef void *t_dado; // PUBLICO, VC PODE MENCIONAR t_dado NA APLICAÇÃO

typedef struct tipo_noh { // PRIVADO, VC NÃO PODE USAR NA APLICAÇÃO
  t_dado dado;
  struct tipo_noh *ant;
  struct tipo_noh *prox;
} * t_noh;

typedef struct tipo_cabec {  // PRIVADO, VC NÃO PODE USAR NA APLICAÇÃO
  int tam;

  int cursor_ndx;
  t_noh cursor_ptr;

  t_noh prim;
  t_noh ult;
} t_cabec;

typedef t_cabec *Lista; // PUBLICO, VC PODE MENCIONAR Lista NA APLICAÇÃO

// PUBLICO, VC PODE INVOCAR ESTAS FUNÇÕES NA APLICAÇÃO
Lista criaLista();
Lista appendLista(Lista l, t_dado dado);
int lenLista(Lista l);
t_dado dadoLista(Lista l, int pos);
Lista insereLista(Lista l, t_dado dado, int pos);
t_dado removeLista(Lista l, int pos);
Lista destroiLista(Lista l); /* destroi todos os nós e dados da lista. Retorna NULL */

#endif
