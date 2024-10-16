#include "tadlista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef Lista tadmat;

//////////////////remover quando for entregar a prova//////////////////
tadmat printa_mat(tadmat a) { 
    for(int i = 0; i < lenLista(a); i++){
        for(int j = 0; j < lenLista(dadoLista(a, 0)); j++){
            printf("%6.0f ",*(float*)dadoLista(dadoLista(a, i),j));
        }
        printf("\n");
    }
    return a;
}
///////////////////////////////////////////////////////////////////////

tadmat subs_dado_mat(tadmat mat, int linha, int coluna, float dado){
    float *pcoef;
    pcoef = (float *)malloc(sizeof(float));
    *pcoef = dado;
    removeLista(dadoLista(mat, linha), coluna);
    insereLista(dadoLista(mat, linha), pcoef, coluna);

    return mat;
}

tadmat cria_mat(int qlinhas, int qcolunas){

    tadmat matriz = criaLista();
    Lista colunas = criaLista();
    float *pcoef;

    for ( int i = 0; i < qlinhas; i++){
        for(int j = 0; j < qcolunas; j++){
            pcoef = (float *)malloc(sizeof(float));
            *pcoef = 0;
            appendLista(colunas,pcoef);
        }
        appendLista(matriz, colunas);
        colunas = criaLista(); 
    }
    return matriz;
}

tadmat soma_mat(tadmat a, tadmat b){
    
    float n_somado;
    if(lenLista(a) == lenLista(b) && lenLista(dadoLista(a, 0)) == lenLista(dadoLista(a, 0))){
        tadmat matriz_s = cria_mat(lenLista(a), lenLista(dadoLista(a, 0)));
        for(int i = 0; i < lenLista(a); i++){
            for(int j = 0; j < lenLista(dadoLista(a, 0)); j++){
                
                n_somado = *((float *)dadoLista(dadoLista(a, i), j)) + *((float *)dadoLista(dadoLista(b, i), j));

                subs_dado_mat(matriz_s, i, j, n_somado);
            }
        }
        return matriz_s;
    }
    return NULL;
}

tadmat multi_mat(tadmat a, tadmat b){

    float n_mult = 0;
    
    if(lenLista(dadoLista(a, 0)) == lenLista(b)){
        
        tadmat matriz_m = cria_mat(lenLista(a), lenLista(dadoLista(b, 0)));
  
        for(int i = 0; i < lenLista(a); i++){
        
            for (int c = 0; c < lenLista(dadoLista(b, 0)); c++){

                for (int j = 0; j < lenLista(b); j++){
                    n_mult += *((float *)dadoLista(dadoLista(a, i), j)) * *((float *)dadoLista(dadoLista(b, j), c));

                }
                subs_dado_mat(matriz_m, i, c, n_mult);
                n_mult = 0; 
            }            
        }
        return matriz_m;
    }
    return NULL;
}

tadmat neg_mat(tadmat a){

    float n_neg;
    for( int i = 0; i < lenLista(a); i++){
        for ( int j = 0; j < lenLista(dadoLista(a, 0)); j++){
            n_neg = *(float *)dadoLista(dadoLista(a, i), j) * -1;
            subs_dado_mat(a, i, j, n_neg);
        }
    }
    return a;
}

tadmat transp_mat(tadmat a){
    tadmat mat_t = cria_mat(lenLista(dadoLista(a, 0)), lenLista(a));

    for (int i = 0; i < lenLista(mat_t); i++) {
        for (int j = 0; j < lenLista(dadoLista(mat_t, 0)); j++) {
            subs_dado_mat(mat_t, i, j, *(float *)dadoLista(dadoLista(a, j), i));
        }
    }
    return mat_t;
}

char* remove_espaco(char *linha) {
    char *aux = (char *)malloc(30 * sizeof(char));
    for (int i = 0; i < 30; i++) aux[i] = '\0';
    for (int i = 0; i < strlen(linha); i++) {
        if (linha[i] != ' ') {
            strncat(aux, &linha[i],1);
            if (i + 1 < strlen(linha) && linha[i+1] == ' ')
                strcat(aux,",");
        }
    }
    return aux;
}

tadmat carrega_mat(char *nomearq){
    FILE *arq;
    arq = fopen(nomearq, "rt");
    char linha[60];
    char aux[30];
    Lista n_mat = criaLista();

    const char s[2] = ",";
    char *token;
    
    float *pcoef;
    
    if (arq == NULL) printf("Arquivo %s não encontrado, encerrando o programa", nomearq);
    else {
        while (fgets(linha,60,arq) != NULL) {
            
            Lista l_aux = criaLista();
            
            if (linha[strlen(linha)-1] == '\n') linha[strlen(linha)-1] = '\0';
            
            strcpy(aux, remove_espaco(linha));
            
            token = strtok(aux, s);

            pcoef = (float *)malloc(sizeof(float));
            *pcoef = atof(token);
            
            appendLista(l_aux, pcoef);
            
            while ((token = strtok(NULL, s)) != NULL) {
                pcoef = (float *)malloc(sizeof(float));
                *pcoef = atof(token);
                appendLista(l_aux, pcoef);
            }
            appendLista(n_mat, l_aux);
        }
    }
    fclose(arq);
    return n_mat;
}

tadmat salva_mat(tadmat a, char *nomearq) {
    FILE *arq;
    arq = fopen(nomearq,"wt");
    int primeiro = 1;

    for(int i = 0; i < lenLista(a); i++){
        if (!primeiro) fprintf(arq,"\n");
            
        for(int j = 0; j < lenLista(dadoLista(a, 0)); j++){
            fprintf(arq,"%6.0f ",*(float*)dadoLista(dadoLista(a, i),j));
        }
        primeiro = 0;
    }
    fclose(arq);
    return a;
}