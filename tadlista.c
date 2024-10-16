#include "tadlista.h"
#include <stdlib.h>

Lista criaLista(){
    Lista lst = (Lista) malloc(sizeof(t_cabec));
    lst->prim = NULL;
    lst->ult  = NULL;
    lst->tam = 0;
    lst->cursor_ndx = -1;
    lst->cursor_ptr = NULL;

    return lst;
}

Lista appendLista(Lista lst, t_dado dado){
    t_noh no;
    no = (t_noh )malloc(sizeof(struct tipo_noh));
    no->dado = dado;
    no->prox = NULL;
    no->ant = NULL;

    if(lst->prim == NULL){
        lst->prim = no;
        lst->ult = no;
        lst->tam++;
    }
    else{
        no->ant = lst->ult;
        lst->ult->prox = no;
        lst->ult = no;
        lst->ult->prox = NULL;
        lst->tam++;
    }
    lst->cursor_ndx = lst->tam-1;
    lst->cursor_ptr = lst->ult;

    return lst;
}

int lenLista(Lista lst){
    return lst->tam;
}

Lista localiza(Lista lst, int pos){
    if((pos < 0) || (pos >= lenLista(lst)))
        return NULL;

    if(pos > lst->cursor_ndx){

        for (int i = lst->cursor_ndx; i < pos; i++){
            lst->cursor_ptr = lst->cursor_ptr->prox;

        }
        lst->cursor_ndx = pos;
    }
    else{
        if(pos < lst->cursor_ndx){
            for(int i = pos; i  < lst->cursor_ndx; i++){
                lst->cursor_ptr = lst->cursor_ptr->ant;
            }
            lst->cursor_ndx = pos;
        }
        else/*se for igual*/
            return lst;
    }
    return lst;
}

Lista insereLista(Lista lst,t_dado dado,int pos){

    t_noh no;
    no = (t_noh )malloc(sizeof(struct tipo_noh));
    no->dado = dado;
    no->prox = NULL;
    no->ant = NULL;

    if(lst->prim == NULL ){
        if(pos == 0){
            appendLista(lst,dado);
            return lst;
        }
        else
            return lst;
    }
    else{

        /*ultima posição*/
        if(pos == lst->tam){
            appendLista(lst,dado);
            return lst;

        }

        else{
            if(localiza(lst, pos)==NULL)
                return NULL;
            /* posição 0 */
            if(pos == 0){
                no->prox = lst->prim;
                lst->prim->ant = no;
                lst->prim = no;
                lst->tam++;

            }
            else{
                /* qualquer posição */

                /* achei mais facil para a visualização e o entendimento utilizar um aux para o cursor, mesmo nao sendo necessário */
                t_noh aux = lst->cursor_ptr;
                no->ant = aux->ant;
                no->prox = aux;
                aux->ant = no;
                no->ant->prox = no;
                lst->tam++;
            }
            lst->cursor_ptr = no;
        }
    }

    return lst;
}


t_dado removeLista(Lista lst, int pos){

    if ((pos < 0) || (pos >= lenLista(lst)))
        return NULL;
    if(localiza(lst, pos)==NULL)
        return NULL;

    t_dado dadosalvo;
    /* somente um elemento na lista */
    if(lenLista(lst) == 1){
        dadosalvo = lst->prim->dado;
        free(lst->prim);
        lst->prim = NULL;
        lst->ult = NULL;
        lst->tam--;
        lst->cursor_ndx = lst->tam-1;
        lst->cursor_ptr = lst->ult;
        return dadosalvo;
    }

    /* prim elemento */
    if(pos == 0){
        t_noh aux = lst->prim->prox;
        dadosalvo = lst->prim->dado;
        free(lst->prim);
        lst->prim = aux;
        lst->prim->ant = NULL;
        lst->tam--;
        lst->cursor_ndx = lst->tam-1;
        lst->cursor_ptr = lst->ult;
        return dadosalvo;
    }

    /* ult elemento */
    if(pos == lenLista(lst)-1){
        t_noh aux = lst->ult->ant;
        dadosalvo = lst->ult->dado;
        free(lst->ult);
        lst->ult = aux;
        lst->ult->prox = NULL;
        lst->tam--;
        lst->cursor_ndx = lst->tam-1;
        lst->cursor_ptr = lst->ult;
        return dadosalvo;
    }

    /* qualquer elemento */

    /* achei mais facil para a visualização e o entendimento utilizar um aux para o cursor, mesmo nao sendo necessário */
    t_noh aux = lst->cursor_ptr;
    aux->ant->prox = aux->prox;
    aux->prox->ant = aux->ant;
    dadosalvo = aux->dado;
    free(aux);
    lst->tam--;
    lst->cursor_ndx = lst->tam-1;
    lst->cursor_ptr = lst->ult;
    return dadosalvo;
}

t_dado dadoLista(Lista lst, int pos){
    if(localiza(lst,pos) != NULL)
        return lst->cursor_ptr->dado;
    else
        return NULL;
}

Lista destroiLista(Lista l){
    for (int i = lenLista(l); i > 0; i--)
        free(removeLista(l, i));
    free(l);
    return NULL;
}